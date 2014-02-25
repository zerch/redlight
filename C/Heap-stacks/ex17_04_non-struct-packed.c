/*
 *Read about how C does it's struct packing, and then try to see why your 
 file is the size it is. See if you can calculate a new size after adding 
 more fields.

 The simplest way to eliminate slop is to reorder the structure members by 
 decreasing alignment. That is: make all the pointer-aligned subfields come 
 first, because on a 64-bit machine they will be 8 bytes. Then the 4-byte 
 ints; then the 2-byte shorts; then the character fields.

 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int max_data;
    int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{   
    if (errno) {
        perror(message);
    } else {
        printf("Fucking Error: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    if (fread(&conn->db->max_rows, sizeof(int), 1, conn->file) != 1)
        die("Failed to load database.", conn);
    if (fread(&conn->db->max_data, sizeof(int), 1, conn->file) != 1)
        die("Failed to load database.", conn);
 
    conn->db->rows = malloc((sizeof(int) * 2) 
            + (sizeof(char) * conn->db->max_data * 2) 
            * conn->db->max_rows);
   
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];

        if (fread(&addr->id, sizeof(int), 1, conn->file) != 1)
            die("Failed to load Database", conn);
        if (fread(&addr->set, sizeof(int), 1, conn->file) != 1)
            die("Failed to load Database", conn);

        addr->name = malloc(sizeof(char) * conn->db->max_data);
        if (fread(addr->name, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to load Database", conn);
        addr->email = malloc(sizeof(char) * conn->db->max_data);
        if (fread(addr->email, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to load Database", conn);
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error", conn);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error", conn);
    
    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        
        if (conn->file) {
            Database_load(conn);
        }
    }
    if (!conn->file) die("Failed to open the file", conn);

    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        int i = 0;
        for (i = 0; i<conn->db->max_rows; i++) {
            free(conn->db->rows[i].name);
            free(conn->db->rows[i].email);
        }
        if (conn->db->rows) free(conn->db->rows);
        if (conn->db) free(conn->db);
        if (conn->file) fclose(conn->file);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
    if (fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file) != 1)
        die("Failed to write database.", conn);
    if (fwrite(&conn->db->max_data, sizeof(int), 1, conn->file) != 1)
        die("Failed to write database.", conn);
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];

        if (fwrite(&addr->id, sizeof(int), 1, conn->file) != 1)
            die("Failed to write database", conn);
        if (fwrite(&addr->set, sizeof(int), 1, conn->file) != 1)
            die("Failed to write database", conn);

        if (fwrite(addr->name, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to write database", conn);
        if (fwrite(addr->email, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to write database", conn);
    }
    if (fflush(conn->file) == 1) die("Cannot flush database", conn);
}

void Database_create(struct Connection *conn)
{
    int max_data = conn->db->max_data;
    int max_rows = conn->db->max_rows;   
    int i = 0;

    conn->db->rows = malloc((sizeof(int) * 2) 
            + (sizeof(char) * max_data * 2) * max_rows);

    for (i = 0; i < max_rows; i++) {
        struct Address addr = {.id = i, .set = 0};
        addr.name = malloc(sizeof(char) * max_data);
        addr.email = malloc(sizeof(char) * max_data);
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name
        , const char *email)
{
    int max_data = conn->db->max_data;
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;
    
    addr->name = malloc(sizeof(char) * max_data);
    addr->email = malloc(sizeof(char) * max_data);

    if (!strncpy(addr->name, name, conn->db->max_data)) 
        die("Name copy failed", conn);
    addr->name[max_data-1] = '\0';
    if (!strncpy(addr->email, email, conn->db->max_data)) 
        die("Email copy failed", conn);
    addr->email[max_data-1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};

    addr.name = malloc(sizeof(char) * conn->db->max_data);
    addr.email = malloc(sizeof(char) * conn->db->max_data);
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{   
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i<conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];
        if (cur->set) {
            Address_print(cur);
        }
    }
}

void Database_find(struct Connection *conn, char *name)
{
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];
        if (strstr(addr->name, name) || strstr(addr->email, name))
                    Database_get(conn, addr->id);
    }
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    char action = argv[2][0];
    
    struct Connection *conn = Database_open(filename, action);
    
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", conn);
   
    int id = 0;

    if (action != 'c' && action != 'f' && argc > 3) {
        id = atoi(argv[3]);
        if (id >= conn->db->max_rows)
            die("There are not that many records.", conn);
    }

    switch(action) {
        case 'c':
            if (argc < 5 ) 
                die("Usage: ex17 <dbfile> c <max_data> <max_rows>", conn);
            conn->db->max_rows = atol(argv[4]);
            conn->db->max_data = atol(argv[3]);
            Database_create(conn);
            Database_write(conn);
            break;
        
        case 'g':
            if (argc != 4) die ("Need an id to get", conn);
            
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        
        case 'd':
            if (argc != 4) die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        case 'f':
            if (argc != 4) die("Need a search token", conn);
            Database_find(conn, argv[3]);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del\
                    , l=list", conn);
    }

    Database_close(conn);

    return 0;
}

