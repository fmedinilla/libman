#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "libman.h"

library_t *library_create(const char *title)
{
    library_t *lib = calloc(1, sizeof(library_t));
    lib->current = 0;
    strcpy(lib->title, title);
    return lib;
}

void library_destroy(library_t *library)
{
    free(library);
}

void library_rename(library_t *library, const char *name)
{
    strcpy(library->title, name);
}

void library_store(library_t *library, book_t book)
{
    library->books[library->current] = book;
    library->current++;
}

void library_delete(library_t *library, int pos)
{
    for (int i = pos; i < (library->current)-1; i++) {
        library->books[i] = library->books[i+1];
    }
    library->current--;
}

void library_edit(library_t *library, int pos, book_t new_data)
{
     book_t *book = &library->books[pos];

     if (strcmp(new_data.title, "") != 0)
        strcpy(book->title, new_data.title);

    if (strcmp(new_data.author, "") != 0)
        strcpy(book->author, new_data.author);

    if (strcmp(new_data.category, "") != 0)
        strcpy(book->category, new_data.category);
}

void library_load(library_t *library)
{
    FILE *fh;
    fh = fopen("data.bin", "rb");
    if (fh == NULL) {
        strcpy(library->title, "library manager");
        return;
    }

    int num  = 0;
    char buffer[STR_LEN];

    fread(&num, sizeof(int), 1, fh);
    fread(buffer, sizeof(char), STR_LEN, fh);
    strcpy(library->title, buffer);

    for (int i = 0; i < num; i++) {
        fread(&library->books[i], sizeof(book_t), 1, fh);
        library->current++;
    }
    fclose(fh);
}

void library_save(library_t *library)
{
    FILE *fh;
    fh = fopen("data.bin", "wb");
    fwrite((void*)&library->current, sizeof(int), 1, fh);
    fwrite(library->title, sizeof(char), STR_LEN, fh);
    for (int i = 0; i < library->current; i++) {
        fwrite((void*)&library->books[i], sizeof(book_t), 1, fh);
    }
    fclose(fh);
}

int library_is_empty(library_t *library)
{
    return library->current == 0;
}