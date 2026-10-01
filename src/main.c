#include <stdio.h>
#include "vault.h"
#include "ui.h"
#include "storage.h"
#include "password.h"
#include "crypto.h"

int main(void)
{
    Vault vault;
    unsigned char key[KEY_SIZE];
    char password[MAX_PASSWORD_LENGTH];

    vault_init(&vault);

    if (vault_read_metadata(&vault) != 0)
    {
        printf("Create master password: ");
        scanf("%99s", password);

        if (password_setup(&vault, password) != 0)
        {
            printf("Password setup failed.\n");
            return 1;
        }

        if (!derive_key(password, vault.salt, key))
        {
            printf("Key derivation failed.\n");
            return 1;
        }

        printf("Master password created successfully.\n");
    }
    else
    {
        printf("Enter master password: ");
        scanf("%99s", password);

        if (!password_check(&vault, password))
        {
            printf("Incorrect master password.\n");
            return 1;
        }

        if (!derive_key(password, vault.salt, key))
        {
            printf("Key derivation failed.\n");
            return 1;
        }

        printf("Access granted.\n");

        if (vault_load(&vault, key) != 0)
        {
            printf("Failed to load vault.\n");
            return 1;
        }
    }

    ui_run(&vault);

    if (vault_save(&vault, key) != 0)
    {
        printf("Failed to save vault.\n");
        return 1;
    }

    return 0;
}