#ifndef STORAGE_H
#define STORAGE_H
#include "vault.h"

int vault_save(Vault *vault);
int vault_load(Vault *vault);

#endif