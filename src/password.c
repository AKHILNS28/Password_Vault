#include <string.h>
#include "password.h"
#include "crypto.h"

int password_verify(const char *input, const char *stored)
{
    return strcmp(input, stored) == 0;
}

int password_setup(Vault *vault,const char *password)
{
    if (!generate_salt(vault->salt))
    {
        return -1;
    }

    if (!hash_password(password, vault->salt, vault->password_hash))
    {
        return -1;
    }

    vault->password_set = 1;

    return 0;
}

int password_check(const Vault *vault, const char *password)
{
    unsigned char hash[HASH_SIZE];

    if (!vault->password_set)
    {
        return 0;
    }

    if (!hash_password(password, vault->salt, hash))
    {
        return 0;
    }

    return memcmp(hash, vault->password_hash, HASH_SIZE) == 0;
}