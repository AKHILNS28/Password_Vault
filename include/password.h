#ifndef PASSWORD_H
#define PASSWORD_H
#include "vault.h"

int password_verify(const char *input, const char *stored);
int password_setup(Vault *vault, const char *password);
int password_check(const Vault *vault, const char *password);

#endif