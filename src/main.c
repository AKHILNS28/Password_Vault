#include <stdio.h>
#include "vault.h"

int main(void)
{
    int ch = 0;
    Vault vault;

    vault_init(&vault);

    printf("================================\n");
    printf("        PASSWORD VAULT\n");
    printf("================================\n\n");

    while (1)
    {
        printf("\n");
        printf("1. Add credential\n");
        printf("2. List credentials\n");
        printf("3. Find credential\n");
        printf("4. Delete credential\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
            {
                char service[100];
                char username[100];
                char password[100];

                printf("Enter service: ");
                scanf("%99s", service);

                printf("Enter username: ");
                scanf("%99s", username);

                printf("Enter password: ");
                scanf("%99s", password);

                int result = vault_add(
                    &vault,
                    service,
                    username,
                    password
                );

                if (result == 0)
                    printf("Credential added successfully.\n");
                else
                    printf("Vault is full.\n");

                break;
            }

            case 2:
            {
                vault_list(&vault);
                break;
            }

            case 3:
            {
                char service[100];

                printf("Enter service to find: ");
                scanf("%99s", service);

                int i = vault_find(&vault, service);

                if (i == -1)
                {
                    printf("Credential not found.\n");
                }
                else
                {
                    printf("Credential found at index %d.\n", i);
                }

                break;
            }

            case 4:
            {
                int i;

                printf("Enter credential index to delete: ");
                scanf("%d", &i);

                int result = vault_delete(&vault, i);

                if (result == 0)
                    printf("Credential deleted successfully.\n");
                else
                    printf("Invalid index.\n");

                break;
            }

            case 5:
            {
                printf("Goodbye!\n");
                return 0;
            }

            default:
            {
                printf("Invalid choice.\n");
                break;
            }
        }
    }
}