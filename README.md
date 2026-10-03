# C Password Vault

A command-line password vault written in C that securely stores credentials using password-based key derivation and AES-256-GCM authenticated encryption.

## Features

* Master password authentication
* Add credentials
* List stored credentials
* Find credentials by service
* Delete credentials
* Persistent encrypted storage
* PBKDF2-HMAC-SHA256 password hashing
* Random salt generation
* Password-based AES key derivation
* AES-256-GCM encryption
* Random IV generation
* Authentication tag for tamper detection
* Modular C architecture
* Separate tests for core components
* Git-based development workflow

## Project Structure

```text
password-vault/
│
├── src/
│   ├── main.c
│   ├── vault.c
│   ├── storage.c
│   ├── crypto.c
│   ├── password.c
│   └── ui.c
│
├── include/
│   ├── vault.h
│   ├── storage.h
│   ├── crypto.h
│   ├── password.h
│   └── ui.h
│
├── test/
│   ├── storage_test.c
│   ├── password_test.c
│   └── crypto_test.c
│
├── Makefile
├── README.md
└── .gitignore
```

## How It Works

The vault uses a master password for authentication and derives an encryption key from the password and a randomly generated salt.

```text
                 Master Password
                        │
              ┌─────────┴─────────┐
              │                   │
              ▼                   ▼
            PBKDF2              PBKDF2
              │                   │
              ▼                   ▼
       Password Hash          AES-256 Key
              │                   │
              ▼                   ▼
       Authentication       AES-256-GCM
                                  │
                                  ▼
                         Encrypted Vault Data
```

The password hash is stored in the vault file for password verification.

The AES encryption key is derived from the entered master password and salt when the vault is opened. The encryption key itself is never stored in the vault file.

## Encryption

Credential data is encrypted using **AES-256-GCM**.

AES-GCM provides both:

* Confidentiality
* Authentication

A new random IV is generated whenever the vault is saved.

If the encrypted data or authentication tag is modified, decryption fails.

## Password Security

The master password is processed using **PBKDF2-HMAC-SHA256**.

A random salt is generated when the master password is created.

The password hash is used to verify the master password, while a separately derived key is used for AES encryption.

The password hash is not used directly as the encryption key.

## Vault Storage

The encrypted vault is stored locally as:

```text
vault.dat
```

The file contains a header containing:

* File magic
* File version
* Salt
* Password hash
* Initialization vector
* Authentication tag
* Ciphertext length

The credential data is stored inside the encrypted ciphertext.

## Requirements

* GCC
* GNU Make
* OpenSSL development libraries

On Ubuntu:

```bash
sudo apt install gcc make libssl-dev
```

## Build

Build the project using:

```bash
make
```

This produces:

```text
password_vault
```

## Run

Run the application with:

```bash
make run
```

or:

```bash
./password_vault
```

## Clean

Remove the compiled executable with:

```bash
make clean
```

## Testing

The project contains separate tests for the main components.

### Crypto Test

The crypto test verifies:

* Salt generation
* Password hashing
* Password-based key derivation
* AES-256-GCM encryption
* AES-256-GCM decryption
* Authentication tag verification
* Detection of tampered ciphertext

Example:

```bash
gcc -Wall -Wextra -Wpedantic -Iinclude \
test/crypto_test.c src/crypto.c \
-lcrypto -o crypto_test
```

Run:

```bash
./crypto_test
```

### Password Test

The password tests verify master password setup and password verification.

### Storage Test

The storage tests verify saving and loading vault data.

## Application Flow

When the application is run for the first time:

```text
Create master password
        │
        ▼
Generate random salt
        │
        ▼
Hash master password
        │
        ▼
Derive encryption key
        │
        ▼
Use vault
        │
        ▼
Encrypt and save vault
```

When an existing vault is opened:

```text
Enter master password
        │
        ▼
Read vault metadata
        │
        ▼
Verify password
        │
        ▼
Derive encryption key
        │
        ▼
Decrypt vault
        │
        ▼
Use vault
        │
        ▼
Encrypt and save vault
```

## Security Design

The project intentionally separates authentication and encryption.

The stored password hash is not used as the encryption key.

Instead:

```text
Master Password + Salt
          │
          ▼
        PBKDF2
          │
          ▼
     AES-256 Key
          │
          ▼
      AES-256-GCM
          │
          ▼
    Encrypted Data
```

This means that obtaining the vault file does not directly reveal the AES encryption key.

## Technologies

* C
* GCC
* OpenSSL
* AES-256-GCM
* PBKDF2-HMAC-SHA256
* GNU Make
* Git

## Learning Objectives

This project was developed to gain practical experience with:

* C programming
* Structures
* Modular programming
* File I/O
* Memory handling
* Error handling
* Cryptography APIs
* Password-based key derivation
* Authenticated encryption
* Data serialization
* Testing
* Git and version control

## Project Status

**Status: Complete**

The current version supports credential management, master password authentication, encrypted persistent storage, and tamper detection.
