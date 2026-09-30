#include "vault.h"
#include<string.h>
void vault_init(Vault *vault)
{
    vault->count=0;
}

int vault_add(Vault *vault,const char *service,const char *username,const char *password)
{
    if(vault->count >= MAX_CREDENTIALS)
    {
        return -1;
    }
    strcpy(vault->credentials[vault->count].service,service);
    strcpy(vault->credentials[vault->count].username,username);
    strcpy(vault->credentials[vault->count].password,password);
    vault->count++;

    return 0;
}

int vault_find(const Vault *vault,const char *service)
{
    for(int i=0;i<vault->count;i++)
    {
        if(strcmp(vault->credentials[i].service,service)==0)
        {
            return i;
        }
    }
    return -1;
}