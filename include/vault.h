#ifndef VAULT_H
#define VAULT_H

#define MAX_SERVICE_LENGTH 100
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MAX_CREDENTIALS 100

typedef struct{
    char service[MAX_SERVICE_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
}Credential;

typedef struct{
    Credential credentials[MAX_CREDENTIALS];
    int count;
}Vault;

void vault_init(Vault *vault);
int vault_add(Vault *vault, const char *service,const char *username, const char *password);
int vault_delete(Vault *vault,int index);
int vault_find(const Vault *vault, const char *service);
void vault_list(const Vault *vault);

#endif
