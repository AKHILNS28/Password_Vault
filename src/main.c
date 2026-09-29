#include<stdio.h>
#include "vault.h"

int main()
{
    Vault vault;
    vault_init(&vault);
    printf("Count value is %d",vault.count);
    return 0;
}