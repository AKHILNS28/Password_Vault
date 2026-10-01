#ifndef STORAGE_H
#define STORAGE_H

#include "vault.h"

int vault_read_metadata(Vault *vault);

int vault_save(const Vault *vault,
               const unsigned char *key);

int vault_load(Vault *vault,
               const unsigned char *key);

#endif