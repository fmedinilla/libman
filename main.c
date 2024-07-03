#include <stdio.h>
#include <string.h>
#include "libman.h"
#include "utils.h"

/* Helpers */
void print_title(library_t *library);
void show_menu(library_t *library, int *option);
void print_header(library_t *library, const char *title);
void book_print(book_t book);

/* Options */
void opt_store_book(library_t *library);
void opt_view_books(library_t *library);
void opt_delete_book(library_t *library);
void opt_edit_book(library_t *library);
void opt_search_book(library_t *library);
void opt_create_fake_data(library_t *library);
void opt_change_name(library_t *library);


/* Entry point */
int main(void)
{
    library_t *library;
    library = library_create("Library manager");

    int option = 0;
    char buffer[STR_LEN]; 

    library_load(library);

    while (1) {
        screen_clear();
        show_menu(library, &option);
        if (option == 0) break;

        fflush(stdin);

        switch (option)
        {
        case 1:
            opt_store_book(library);
            break;
        case 2:
            opt_view_books(library);
            break;
        case 3:
            opt_delete_book(library);
            break;
        case 4:
            opt_edit_book(library);
            break;
        case 5:
            opt_search_book(library);
            break;
        case 8:
            opt_change_name(library);
            break;
        case 9:
            opt_create_fake_data(library);
            break;
        }
    }

    library_save(library);
    library_destroy(library);

    return 0;
}


/* Helpers */
void print_title(library_t *library)
{
    int len = strlen(library->title);
    int total_len = len + 4;
    char border[total_len];
    for (int i = 0; i < total_len; i++) {
        border[i] = '-';
    }

    border[0] = '+';
    border[total_len-1] = '+';
    border[total_len] = '\0';

    to_uppercase(library->title, library->title);

    printf("%s\n", border);
    printf("| %s |\n", library->title);
    printf("%s\n\n", border);
}
void show_menu(library_t *library, int *option)
{
    print_title(library);
    
    puts("1. Store new book");
    puts("2. View all books");
    puts("3. Delete book");
    puts("4. Edit book");
    puts("5. Search for books");
    puts("8. Change name");
    puts("9. Create fake data");
    puts("0. Exit");

    printf("\nOption: ");
    scanf("%d", option);
}
void print_header(library_t *library, const char *title)
{
    screen_clear();
    print_title(library);
    printf("%s\n\n", title);
}
void book_print(book_t book)
{
    printf("[%s] '%s' de %s\n", book.category, book.title, book.author);
}

/* Options */
void opt_store_book(library_t *library)
{
    print_header(library, "STORE NEW BOOK");

    book_t book;
    char buffer[STR_LEN];

    puts("Empty to cancel\n");

    // ask for title
    printf("Title: ");
    read_str(buffer, STR_LEN);
    strcpy(book.title, buffer);

    if (strcmp(buffer, "") == 0) return;

    // ask for author
    printf("Author: ");
    read_str(buffer, STR_LEN);
    strcpy(book.author, buffer);

    // ask for category
    printf("Category: ");
    read_str(buffer, STR_LEN);
    strcpy(book.category, buffer);

    // store
    library_store(library, book);
}
void opt_view_books(library_t *library)
{
    print_header(library, "ALL BOOKS");
    
    if (library_is_empty(library)) {
        printf("There are not any book\n");
        getchar();
        return;
    }

    for (int i = 0; i < library->current; i++) {
        book_print(library->books[i]);
    }

    getchar();
}
void opt_delete_book(library_t *library)
{
    print_header(library, "DELETE A BOOK");

    if (library_is_empty(library)) {
        printf("There are not any book\n");
        getchar();
        return;
    }

    for (int i = 0; i < library->current; i++) {
        printf("%d - ", i+1);
        book_print(library->books[i]);
    }
    printf("0 - Cancel\n");

    int id = 0;
    printf("\nBook id: ");
    scanf("%d", &id);

    fflush(stdin);

    if (id == 0) {
        return;
    }
    id--;

    library_delete(library, id);
}
void opt_edit_book(library_t *library)
{
    print_header(library, "EDIT A BOOK");

    if (library_is_empty(library)) {
        printf("There are not any book\n");
        getchar();
        return;
    }

    for (int i = 0; i < library->current; i++) {
        printf("%d - ", i+1);
        book_print(library->books[i]);
    }
    printf("0 - Cancel\n");

    int id = 0;
    printf("\nBook id: ");
    scanf("%d", &id);

    fflush(stdin);

    if (id == 0) {
        return;
    }
    id--;

    book_t book = {"", "", ""};
    char buffer[STR_LEN];

    // ask for title
    printf("Title: ");
    read_str(buffer, STR_LEN);
    if (strcmp(buffer, "") != 0) {
        strcpy(book.title, buffer);
    }

    // ask for author
    printf("Author: ");
    read_str(buffer, STR_LEN);
    if (strcmp(buffer, "") != 0) {
        strcpy(book.author, buffer);
    }

    // ask for category
    printf("Category: ");
    read_str(buffer, STR_LEN);
    if (strcmp(buffer, "") != 0) {
        strcpy(book.category, buffer);
    }

    library_edit(library,  id, book);
}
void opt_search_book(library_t *library)
{
    print_header(library, "SEARCH FOR BOOKS");
    if (library_is_empty(library)) {
        printf("There are not any book\n");
        getchar();
        return;
    }

    char buffer[STR_LEN];
    char upper_search_value[STR_LEN];
    int flag_search = 0;

    // search bu title
    printf("Search: ");
    read_str(buffer, STR_LEN);
    to_uppercase(upper_search_value, buffer);

    printf("\n");

    // search
    for (int i = 0; i < library->current; i++) {
        book_t book = library->books[i];

        char title[STR_LEN];
        to_uppercase(title, book.title);

        char author[STR_LEN];
        to_uppercase(author, book.author);

        char category[STR_LEN];
        to_uppercase(category, book.category);

        int title_search = strstr(title, upper_search_value) != NULL;
        int author_search = strstr(author, upper_search_value) != NULL;
        int category_search = strstr(category, upper_search_value) != NULL;

        if (title_search || author_search || category_search) {
            book_print(book);
            flag_search = 1;
        }
    }

    if (!flag_search) {
        printf("There are not results\n");
    }

    getchar();
}
void opt_create_fake_data(library_t *library)
{
    book_t books[6] = {
        {"1984", "George Orwell", "Ciencia ficcion"},
        {"Sapiens: de animalesa a dioses", "Yuval Noah Harari", "No ficcion"},
        {"Orgullo y prejuicio", "Jane Austen", "Novela romantica"},
        {"El hombre de la rosa", "Umberto Eco", "Misterio historico"},
        {"Rebelion en la granja", "George Orwell", "Novela"},
        {"La rosa de los vientos", "Manuel Alfonseca", "Novela"}
    };

    for (int i = 0; i < 6; i++) {
        library_store(library, books[i]);
    }
}
void opt_change_name(library_t *library)
{
    print_header(library, "CHANGE LIBRARY'S NAME");
    puts("Empty to cancel\n");

    char buffer[STR_LEN];
    printf("Name: ");
    read_str(buffer, STR_LEN);

    if (strcmp(buffer, "") == 0) return;

    library_rename(library, buffer);
}
