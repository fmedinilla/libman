#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void screen_clear()
{
    printf("\e[1;1H\e[2J");
}

void read_str(char *buffer, const int LEN)
{
    fgets(buffer, LEN, stdin);
    buffer[strlen(buffer)-1] = '\0';
    fflush(stdin);
}

void to_uppercase(char dest[], char source[])
{
    int len = strlen(source);
    for (int i = 0; i < len; i++) {
        dest[i] = toupper(source[i]);
    }
    dest[len] = '\0';
}
