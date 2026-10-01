#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "storage.h"
#include "crypto.h"

#define VAULT_MAGIC "PVLT"
#define VAULT_VERSION 1

typedef struct
{
    char magic[4];
    uint32_t version;

    unsigned char salt[SALT_SIZE];
    unsigned char password_hash[HASH_SIZE];

    unsigned char iv[IV_SIZE];
    unsigned char tag[TAG_SIZE];

    uint32_t ciphertext_len;

} VaultFileHeader;

typedef struct
{
    Credential credentials[MAX_CREDENTIALS];
    int count;

} VaultData;


int vault_save(const Vault *vault,
               const unsigned char *key)
{
    FILE *fp;

    VaultFileHeader header;
    VaultData data;

    unsigned char ciphertext[sizeof(VaultData)];

    int ciphertext_len;


    /* Prepare data to encrypt */

    memset(&data, 0, sizeof(VaultData));

    data.count = vault->count;

    memcpy(
        data.credentials,
        vault->credentials,
        sizeof(vault->credentials)
    );


    /* Generate a new IV for every save */

    if (!generate_iv(header.iv))
    {
        printf("IV generation failed.\n");
        return -1;
    }


    /* Encrypt vault data */

    ciphertext_len = encrypt_data(
        (const unsigned char *)&data,
        sizeof(VaultData),
        key,
        header.iv,
        ciphertext,
        header.tag
    );

    if (ciphertext_len < 0)
    {
        printf("Encryption failed.\n");
        return -1;
    }


    /* Prepare file header */

    memcpy(header.magic, VAULT_MAGIC, 4);

    header.version = VAULT_VERSION;

    memcpy(
        header.salt,
        vault->salt,
        SALT_SIZE
    );

    memcpy(
        header.password_hash,
        vault->password_hash,
        HASH_SIZE
    );

    header.ciphertext_len = ciphertext_len;


    /* Open file */

    fp = fopen("vault.dat", "wb");

    if (fp == NULL)
    {
        printf("Error in opening file.\n");
        return -1;
    }


    /* Write header */

    if (fwrite(&header, sizeof(header), 1, fp) != 1)
    {
        printf("Error writing vault header.\n");
        fclose(fp);
        return -1;
    }


    /* Write encrypted data */

    if (fwrite(ciphertext, ciphertext_len, 1, fp) != 1)
    {
        printf("Error writing encrypted vault data.\n");
        fclose(fp);
        return -1;
    }


    fclose(fp);

    return 0;
}


int vault_load(Vault *vault,
               const unsigned char *key)
{
    FILE *fp;

    VaultFileHeader header;
    VaultData data;

    unsigned char ciphertext[sizeof(VaultData)];

    int decrypted_len;


    /* Open file */

    fp = fopen("vault.dat", "rb");

    if (fp == NULL)
    {
        return -1;
    }


    /* Read header */

    if (fread(&header, sizeof(header), 1, fp) != 1)
    {
        printf("Error reading vault header.\n");
        fclose(fp);
        return -1;
    }


    /* Verify file format */

    if (memcmp(header.magic, VAULT_MAGIC, 4) != 0)
    {
        printf("Invalid vault file.\n");
        fclose(fp);
        return -1;
    }

    if (header.version != VAULT_VERSION)
    {
        printf("Unsupported vault version.\n");
        fclose(fp);
        return -1;
    }


    /* Check ciphertext size */

    if (header.ciphertext_len != sizeof(VaultData))
    {
        printf("Invalid encrypted data size.\n");
        fclose(fp);
        return -1;
    }


    /* Read encrypted data */

    if (fread(ciphertext, header.ciphertext_len, 1, fp) != 1)
    {
        printf("Error reading encrypted vault data.\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);


    /* Decrypt */

    decrypted_len = decrypt_data(
        ciphertext,
        header.ciphertext_len,
        key,
        header.iv,
        header.tag,
        (unsigned char *)&data
    );

    if (decrypted_len < 0)
    {
        printf("Vault decryption failed.\n");
        return -1;
    }


    /* Restore vault data */

    memset(vault->credentials, 0,
           sizeof(vault->credentials));

    memcpy(
        vault->credentials,
        data.credentials,
        sizeof(data.credentials)
    );

    vault->count = data.count;

    memcpy(
        vault->salt,
        header.salt,
        SALT_SIZE
    );

    memcpy(
        vault->password_hash,
        header.password_hash,
        HASH_SIZE
    );

    vault->password_set = 1;

    return 0;
}

int vault_read_metadata(Vault *vault)
{
    FILE *fp;
    VaultFileHeader header;

    fp = fopen("vault.dat", "rb");

    if (fp == NULL)
    {
        return -1;
    }

    if (fread(&header, sizeof(header), 1, fp) != 1)
    {
        printf("Error reading vault header.\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);

    if (memcmp(header.magic, VAULT_MAGIC, 4) != 0)
    {
        printf("Invalid vault file.\n");
        return -1;
    }

    if (header.version != VAULT_VERSION)
    {
        printf("Unsupported vault version.\n");
        return -1;
    }

    memcpy(
        vault->salt,
        header.salt,
        SALT_SIZE
    );

    memcpy(
        vault->password_hash,
        header.password_hash,
        HASH_SIZE
    );

    vault->password_set = 1;

    return 0;
}