#include "vault.h"
#include "ui.h"
int main(void)
{
    Vault vault;

    vault_init(&vault);
    ui_run(&vault);

    return 0;
    
}