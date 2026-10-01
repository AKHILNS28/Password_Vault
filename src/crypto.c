#include <openssl/rand.h>
#include <openssl/evp.h>
#include "crypto.h"

#define ITERATIONS 100000

int generate_salt(unsigned char *salt)
{
    return RAND_bytes(salt, SALT_SIZE) == 1;
}

int generate_iv(unsigned char *iv)
{
    return RAND_bytes(iv, IV_SIZE) == 1;
}

int hash_password(const char *password,const unsigned char *salt,unsigned char *hash)
{
    return PKCS5_PBKDF2_HMAC(password,-1,salt,SALT_SIZE,ITERATIONS,EVP_sha256(),HASH_SIZE,hash);
}

int derive_key(const char *password,const unsigned char *salt,unsigned char *key)
{
    return PKCS5_PBKDF2_HMAC(
        password,
        -1,
        salt,
        SALT_SIZE,
        ITERATIONS,
        EVP_sha256(),
        KEY_SIZE,
        key
    );
}

int encrypt_data(const unsigned char *plaintext,int plaintext_len,const unsigned char *key,const unsigned char *iv,unsigned char *ciphertext,unsigned char *tag)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    ctx = EVP_CIPHER_CTX_new();

    if (ctx == NULL)
    {
        return -1;
    }
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN,IV_SIZE, NULL) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_EncryptUpdate(ctx, ciphertext, &len,plaintext, plaintext_len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    ciphertext_len = len;
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    ciphertext_len += len;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG,TAG_SIZE, tag) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int decrypt_data(const unsigned char *ciphertext,int ciphertext_len,const unsigned char *key,const unsigned char *iv,const unsigned char *tag,unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL)
    {
        return -1;
    }
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN,
                            IV_SIZE, NULL) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_DecryptUpdate(ctx, plaintext, &len,
                          ciphertext, ciphertext_len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len = len;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG,TAG_SIZE, (void *)tag) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) <= 0)
    {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}