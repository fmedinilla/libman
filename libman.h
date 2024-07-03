#ifndef LIBMAN_HEADER_
#define LIBMAN_HEADER_

#define STR_LEN 256
#define MAX_BOOKS 100

typedef struct {
    char title[STR_LEN];
    char author[STR_LEN];
    char category[STR_LEN];
} book_t;

typedef struct {
    book_t books[MAX_BOOKS];
    int current;
    char title[STR_LEN];
} library_t;

/* HEADERS */
library_t *library_create(const char *);
void library_destroy(library_t *);
void library_rename(library_t *library, const char *name);

void library_store(library_t *library, book_t book);
void library_delete(library_t *library, int pos);
void library_edit(library_t *library, int pos, book_t book);

void library_load(library_t *library);
void library_save(library_t *library);

int library_is_empty(library_t *library);

#endif