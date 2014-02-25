// standard input/output libraries
#include <stdio.h>

// assert - abort the program if assertion is false
#include <assert.h>

// library includes dynamic memory management, random number generation
// integer arithmetics, searching, sorting and converting
#include <stdlib.h>

// number of last error
#include <errno.h>

// library with string functions that perfom string operations
// on null-terminated strings
#include <string.h>

// part of "C Pre-Processor" to create constant settings reliably
#define MAX_DATA 512
#define MAX_ROWS 100

// a struct named Address with two integer properties 
// and two fixed sized string properties
struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

// a struct named Database with a struct property of
// type Address with fixed length
struct Database {
    struct Address rows[MAX_ROWS];
};

// a struct named Connection that takes a FILE *file
// and a struct type Database
struct Connection {
    // FILE is a struct defined in stdlib
    // functions like fopen, fread, fclose and rewind wonrk on this
    FILE *file;
    struct Database *db;
};

// a function to kill the program with an error.
// used after any failed function of bad input to exit an error
// using exit
void die(const char *message)
{   
    // errno is just a number
    if (errno) {
        // using perror (print error) to print and explain the error message
        perror(message);
    } else {
        printf("Error: %s\n", message);
    }
    exit(1);
}

// function to print an Address's id, name, and email
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

// function to load the database from file into connection
void Database_load(struct Connection *conn)
{
    // using fread to read 1 element of data, with the size of Database struct
    // from struct Connection's "conn->file" storing them
    // in "conn->db"
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

    // integer "rc" should be 1 for a successful loading, '1' meaning the number
    // of successful read elements, in our case only one element is read
    if(rc != 1) die("Failed to load database.");
}

//function 
struct Connection *Database_open(const char *filename, char mode)
{
    // allocating memory for pointer *conn with size of struct Connection
    struct Connection *conn = malloc(sizeof(struct Connection));
    // if pointer is NULL
    if(!conn) die("Memory error");

    // conn->db is also a struct that needs memory allocation
    conn->db = malloc(sizeof(struct Database));
    // same as if(!conn), if conn->db fails to allocate memory,
    // which gives a null pointer then 
    // print error message
    if(!conn->db) die("Memory error");

    // if character "mode" argument is 'c' than open filename's path
    // with 'w' mode enabled and returns a FILE pointer, otherwise open
    // file with 'r+' mode
    if (mode == 'c') {
        // 'w' mode means truncate file to 0 length or create text file
        // for writing. stream at beginning
        conn->file = fopen(filename, "w");
    } else {
        // 'r+' means open for reading and writing. stream at beginning
        conn->file = fopen(filename, "r+");
        
        // if pointer conn->file is created successfully call 
        // Database_load function
        if (conn->file) {
            Database_load(conn);
        }
    }
    // if pointer conn->file fails print error message
    if (!conn->file) die("Failed to open the file");

    // return connection ?
    return conn;
}

// function to close database
void Database_close(struct Connection *conn)
{
    // if connection is close file conn->file and free memory conn->db and conn
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}

// function to write in database
void Database_write(struct Connection *conn)
{
    // sets the file position indicator for conn->file to the beginning of file
    // equivalent to seeking at the beginning of file
    rewind(conn->file);

    // function fwrite to write 1 element of size struct Database to conn->file,
    // from conn->db
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.");

    // function fflush does flush on conn->file
    // For input streams, fflush() discards any buffered data that has been 
    // fetched from the underlying file, but has not been consumed by the 
    // application. 
    // 0 is returned for success 1 for failure
    rc = fflush(conn->file);
    if (rc == 1) die("Cannot flush database");
}

// function to create rows in database
void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        // prototype row with first initial values
        // rows are type struct Address
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

// function to set 
void Database_set(struct Connection *conn, int id, const char *name\
        , const char *email)
{
    // create a pointer addr and assign to the value at the address of 
    // 'id' element of 'rows' from 'db' from 'conn'
    struct Address *addr = &conn->db->rows[id];
    // if addr->set is already set than print error message
    if (addr->set) die("Already set, delete it first");

    // set addr's set to one
    addr->set = 1;
    
    // WARNING: bug, read the "How to break it" and fix this
    // strncpy - copies the string from 'addr->name' in 'name'
    // with maximum size in bytes of MAX_DATA and returns a pointer
    char *res = strncpy(addr->name, name, MAX_DATA);
    
    // demonstrate the strncpy bug
    if (!res) die("Name copy failed");

    //reuse the 'res' for copying the email aswell
    res = strncpy(addr->email, email, MAX_DATA);
    if (!res) die("Email copy failed");
}

// function to print a row from database by given id
void Database_get(struct Connection *conn, int id)
{
    // create a pointer addr and assign to the value at the address of 
    // 'id' element of 'rows' from 'db' from 'conn'
    struct Address *addr = &conn->db->rows[id];
    // if address has been set to 1 than print addr's items
    // else print error message for wrong given ID or
    // wrong set ID
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

// function to delete a row from database by given id
void Database_delete(struct Connection *conn, int id)
{
    // create a prototype of the row with id id and set it to 0
    struct Address addr = {.id = id, .set = 0};
    // that rows id wil be set to 0 
    conn->db->rows[id] = addr;
}

// function to list the whole database
void Database_list(struct Connection *conn)
{
    int i = 0;
    // put the database in a Database structure
    struct Database *db = conn->db;

    // looping through the maximum length permitted
    for (i = 0; i<MAX_ROWS; i++) {
        // creating Address struct for each row
        struct Address *cur = &db->rows[i];

        // if that address's id is set then it's going to be printed
        if (cur->set) {
            Address_print(cur);
        }
    }
}


int main(int argc, char *argv[])
{
    // application must have at least 3 arguments including the program's name
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    // openning the database with the given filename
    // action is the mode, c for create, or anything else for
    // doing stuff on already created database
    struct Connection *conn = Database_open(filename, action);
    
    // start with id at zero
    int id = 0;

    // if argc is larger than 3 arguments, 4th argument will be the id
    // atoi() function converts string to integer
    if (argc > 3) id = atoi(argv[3]);
    // if id exceeds the permitted size of number of rows in database
    // print error message
    if (id >= MAX_ROWS) die("There's not that many records");

    switch(action) {
        // if action is 'c', create Database and write to file
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;
        
        // if action is 'g' argc must be 4 to include an id
        // using this mode with a given id will print that
        // row in database
        case 'g':
            if (argc != 4) die ("Need an id to get");
            
            Database_get(conn, id);
            break;

        // if action is s we need 6 arguments:
        // 4th is 'id', 5th is 'name' and 6th is 'email'
        // this will set a row in database for that id
        // with the given name and email and write to file
        case 's':
            if (argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        
        // if action is 'd' deletes a row with given id and then writes 
        // to database
        case 'd':
            if (argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        // if l is given list whole database
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}

