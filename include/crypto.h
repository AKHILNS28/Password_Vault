#ifndef CRYPTO_H
#define CRYPTO_H

#define SALT_SIZE 16
#define HASH_SIZE 32

int generate_salt(unsigned char *salt);
int hash_password(const char *password,const unsigned char *salt,unsigned char *hash);

#endif