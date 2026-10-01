#include <string.h>
#include "password.h"

int password_verify(const char *input, const char *stored)
{
    return strcmp(input, stored) == 0;
}