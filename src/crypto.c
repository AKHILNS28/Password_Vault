#include <openssl/rand.h>
#include <openssl/evp.h>
#include "crypto.h"

#define ITERATIONS 100000

int generate_salt(unsigned char *salt)
{
    return RAND_bytes(salt, SALT_SIZE) == 1;
}

int hash_password(const char *password,const unsigned char *salt,unsigned char *hash)
{
    return PKCS5_PBKDF2_HMAC(password,-1,salt,SALT_SIZE,ITERATIONS,EVP_sha256(),HASH_SIZE,hash);
}