# Libman

Console application for Library manager writen in C. It can store books with a title, an author and a category.

## Technologies

During the development of this application I use different technologies:

- **C**: To write the application
- **Git**: Control version system

## Modules

**libman**  
Here, I declare the `book_t` and `library_t` types. Moreover, I declare all function headers related to the library.

**utils**  
I decided to write a separate module to put some functions I use, but that don't belong to the library.

## Data persistence

I decided to persist data using a binary file.

The binary file is structured as follows:

- 4 bytes for `book_count`
- 256 bytes for `library_name`
- 768 bytes for every book
  - 256 bytes for `title`
  - 256 bytes for `author`
  - 256 bytes for `category`

I suppose the `int` type has a size of 4 bytes and the `char` type has a size of 1 byte.

## How to compile

You will need gcc to compile this program, or you can use another C compiler if you prefer.

To compile the application, you can use the following command:

```bash
$ gcc -o app main.c libman.c utils.c
```

This will generate an executable file named `app`.

To run this application, you can use:

```bash
$ ./app
```

## License

[MIT](https://choosealicense.com/licenses/mit/)
