#include<stdio.h>
#include "vault.h"
#include "ui.h"
#include "storage.h"
#include "password.h"

int main(void)
{
    Vault vault;

    vault_init(&vault);
    vault_load(&vault);

    if (!vault.password_set)
    {
        char password[MAX_PASSWORD_LENGTH];
        printf("Create master password: ");
        scanf("%99s", password);
        if (password_setup(&vault, password) != 0)
        {
            printf("Password setup failed.\n");
            return 1;
        }
        printf("Master password created successfully.\n");
    }
    else
    {
        char password[MAX_PASSWORD_LENGTH];

        printf("Enter master password: ");
        scanf("%99s", password);

        if (!password_check(&vault, password))
        {
            printf("Incorrect master password.\n");
            return 1;
        }

        printf("Access granted.\n");
    }

    ui_run(&vault);
    vault_save(&vault);

    return 0;
}