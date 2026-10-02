CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude
LIBS = -lcrypto

TARGET = password_vault

SRC = src/main.c \
      src/vault.c \
      src/ui.c \
      src/storage.c \
      src/password.c \
      src/crypto.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)