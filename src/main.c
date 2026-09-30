#include <stdio.h>
#include "vault.h"

int main(void)
{
    Vault vault;

    vault_init(&vault);

    vault_add(&vault, "GitHub", "akhil", "githubpass");
    vault_add(&vault, "Gmail", "akhil@gmail.com", "gmailpass");
    vault_add(&vault, "Facebook", "akhil", "facebookpass");

    printf("Before delete: %d credentials\n", vault.count);

    int result = vault_delete(&vault, 1);

    printf("Delete result: %d\n", result);
    printf("After delete: %d credentials\n", vault.count);

    printf("Remaining:\n");

    for (int i = 0; i < vault.count; i++)
    {
        printf("%d: %s\n", i, vault.credentials[i].service);
    }

    vault_list(&vault);

    return 0;
}