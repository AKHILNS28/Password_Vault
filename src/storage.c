#include<stdio.h>
#include "storage.h"

int vault_save(Vault *vault)
{
    FILE *fp=fopen("vault.dat","wb");
    if(fp==NULL)
    {
        printf("Error opening file");
        return -1;
    }
    if (fwrite(vault, sizeof(Vault), 1, fp) != 1)
    {
        printf("Error writing to file.\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}

int vault_load(Vault *vault)
{
    FILE *fp = fopen("vault.dat", "rb");

    if (fp==NULL)
    {
        printf("Error in opening file.\n");
        return -1;
    }

    if (fread(vault,sizeof(Vault),1,fp)!=1)
    {
        printf("Error in reading file.\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}