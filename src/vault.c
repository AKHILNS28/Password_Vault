#include<string.h>
#include<stdio.h>
#include "vault.h"

void vault_init(Vault *vault)
{
    vault->count=0;
    vault->password_set=0;
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

int vault_delete(Vault *vault,int index)
{
    if(index<0 || index>=vault->count)
    {
        return -1;
    }
    for(int i=index;i<vault->count;i++)
    {
        vault->credentials[i]=vault->credentials[i+1];
    }
    vault->count--;
    return 0;
}

void vault_list(const Vault *vault)
{
    for(int i=0;i<vault->count;i++)
    {
        printf("%d. %s - %s\n",i+1,vault->credentials[i].username,vault->credentials[i].service);
    }
}