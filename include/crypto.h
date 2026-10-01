#ifndef CRYPTO_H
#define CRYPTO_H

#define SALT_SIZE 16
#define HASH_SIZE 32
#define KEY_SIZE 32
#define IV_SIZE 12
#define TAG_SIZE 16

int generate_salt(unsigned char *salt);
int generate_iv(unsigned char *iv);
int hash_password(const char *password,const unsigned char *salt,unsigned char *hash);
int encrypt_data(const unsigned char *plaintext,int plaintext_len,const unsigned char *key,const unsigned char *iv,unsigned char *ciphertext,unsigned char *tag);
int decrypt_data(const unsigned char *ciphertext,int ciphertext_len,const unsigned char *key,const unsigned char *iv,const unsigned char *tag,unsigned char *plaintext);
int derive_key(const char *password,const unsigned char *salt,unsigned char *key);
#endif