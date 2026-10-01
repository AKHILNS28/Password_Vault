#include "vault.h"
#include "ui.h"
#include "storage.h"

int main(void)
{
    Vault vault;

    vault_init(&vault);
    vault_load(&vault);

    ui_run(&vault);
    vault_save(&vault);

    return 0;
}