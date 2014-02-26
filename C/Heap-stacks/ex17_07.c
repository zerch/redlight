/*
Try reworking the program to use a single global for the database connection. How does this new version of the program compare to the other one?
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    char *name;
    char *email;
    char *prof;
    char *phone;
    int id;
    int set;
};

struct Database {
    struct Address *rows;
    int max_data;
    int max_rows;
};

struct Connection {
    struct Database *db;
    FILE *file;
};

struct Connection *conn;

void Database_close();

void die(const char *message)
{   
    if (errno) {
        perror(message);
    } else {
        printf("Fucking Error: %s\n", message);
    }
    Database_close();
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s %s %s\n", 
            addr->id, addr->name, addr->email, addr->prof, addr->phone);
}

void Database_load()
{
    if (fread(&conn->db->max_rows, sizeof(int), 1, conn->file) != 1)
        die("Failed to load database.");
    if (fread(&conn->db->max_data, sizeof(int), 1, conn->file) != 1)
        die("Failed to load database.");
 
    conn->db->rows = malloc((sizeof(int) * 2) 
            + (sizeof(char) * conn->db->max_data * 2) 
            * conn->db->max_rows);
   
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];

        if (fread(&addr->id, sizeof(int), 1, conn->file) != 1)
            die("Failed to load Database");
        if (fread(&addr->set, sizeof(int), 1, conn->file) != 1)
            die("Failed to load Database");

        addr->name = malloc(sizeof(char) * conn->db->max_data);
        if (fread(addr->name, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to load Database");
        addr->email = malloc(sizeof(char) * conn->db->max_data);
        if (fread(addr->email, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to load Database");
        addr->prof = malloc(sizeof(char) * conn->db->max_data);
        if (fread(addr->prof, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to load Database");
         addr->phone = malloc(sizeof(char) * conn->db->max_data);
        if (fread(addr->phone, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to load Database");
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error");
    
    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        
        if (conn->file) {
            Database_load(conn);
        }
    }
    if (!conn->file) die("Failed to open the file");

    return conn;
}

void Database_close()
{
    if (conn) {
        int i = 0;
        for (i = 0; i<conn->db->max_rows; i++) {
            free(conn->db->rows[i].name);
            free(conn->db->rows[i].email);
            free(conn->db->rows[i].prof);
            free(conn->db->rows[i].phone);
        }
        if (conn->db->rows) free(conn->db->rows);
        if (conn->db) free(conn->db);
        if (conn->file) fclose(conn->file);
        free(conn);
    }
}

void Database_write()
{
    rewind(conn->file);
    if (fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file) != 1)
        die("Failed to write database.");
    if (fwrite(&conn->db->max_data, sizeof(int), 1, conn->file) != 1)
        die("Failed to write database.");
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];

        if (fwrite(&addr->id, sizeof(int), 1, conn->file) != 1)
            die("Failed to write database");
        if (fwrite(&addr->set, sizeof(int), 1, conn->file) != 1)
            die("Failed to write database");

        if (fwrite(addr->name, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to write database");
        if (fwrite(addr->email, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to write database");
        if (fwrite(addr->prof, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to write database");
        if (fwrite(addr->phone, sizeof(char) * conn->db->max_data
                    , 1, conn->file) != 1)
            die("Failed to write database");
    }
    if (fflush(conn->file) == 1) die("Cannot flush database");
}

void Database_create()
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
        addr.prof = malloc(sizeof(char) * max_data);
        addr.phone = malloc(sizeof(char) * max_data);
        conn->db->rows[i] = addr;
    }
}

void Database_set(int id, const char *name
        , const char *email, const char *prof, const char *phone)
{
    int max_data = conn->db->max_data;
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first");

    addr->set = 1;
    
    addr->name = malloc(sizeof(char) * max_data);
    addr->email = malloc(sizeof(char) * max_data);
    addr->prof = malloc(sizeof(char) * max_data);
    addr->phone = malloc(sizeof(char) * max_data);

    if (!strncpy(addr->name, name, conn->db->max_data)) 
        die("Name copy failed");
    addr->name[max_data-1] = '\0';
    if (!strncpy(addr->email, email, conn->db->max_data)) 
        die("Email copy failed");
    addr->email[max_data-1] = '\0';
    if (!strncpy(addr->prof, prof, conn->db->max_data)) 
        die("Profession copy failed");
    addr->prof[max_data-1] = '\0';
    if (!strncpy(addr->phone, phone, conn->db->max_data)) 
        die("Phone copy failed");
    addr->phone[max_data-1] = '\0';

}

void Database_get(int id)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(int id)
{
    struct Address addr = {.id = id, .set = 0};

    addr.name = malloc(sizeof(char) * conn->db->max_data);
    addr.email = malloc(sizeof(char) * conn->db->max_data);
    addr.prof = malloc(sizeof(char) * conn->db->max_data);
    addr.phone = malloc(sizeof(char) * conn->db->max_data);
    conn->db->rows[id] = addr;
}

void Database_list()
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

void Database_findbyName(char *name)
{
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];
        if (strstr(addr->name, name) || strstr(addr->email, name))
                    Database_get(addr->id);
    }
}

void Database_findbyProf(char *name)
{
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];
        if (strstr(addr->prof, name))
                    Database_get(addr->id);
    }
}

void Database_findbyNumb(char *numb)
{
    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];
        if (strstr(addr->phone, numb))
                    Database_get(addr->id);
    }
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    char action = argv[2][0];
    
    conn = Database_open(filename, action);
    
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
   
    int id = 0;

    if (action != 'c' && action != 'f' && action != 'p' && action != 'n' 
            && argc > 3) {
        id = atoi(argv[3]);
        if (id >= conn->db->max_rows)
            die("There are not that many records.");
    }

    switch(action) {
        case 'c':
            if (argc < 5 ) 
                die("Usage: ex17 <dbfile> c <max_data> <max_rows>");
            conn->db->max_rows = atol(argv[4]);
            conn->db->max_data = atol(argv[3]);
            Database_create();
            Database_write();
            break;
        
        case 'g':
            if (argc != 4) die ("Need an id to get");
            
            Database_get(id);
            break;

        case 's':
            if (argc != 8) die("Need id, name, email to set");

            Database_set(id, argv[4], argv[5], argv[6], argv[7]);
            Database_write();
            break;
        
        case 'd':
            if (argc != 4) die("Need id to delete");

            Database_delete(id);
            Database_write();
            break;

        case 'l':
            Database_list();
            break;

        case 'f':
            if (argc != 4) die("Need a search token");
            Database_findbyName(argv[3]);
            break;

        case 'p':
            if (argc != 4) die("Need a search token");
            Database_findbyProf(argv[3]);
            break;
        case 'n':
            if (argc != 4) die("Need a search token");
            Database_findbyNumb(argv[3]);
            break;
       
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del\
                    , l=list");
    }

    Database_close();

    return 0;
}

