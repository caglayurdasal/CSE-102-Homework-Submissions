#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct table
{
    char **field; /* Name of the field */
    char **type;  /* Data type of the field */
    bool *isNull; /* Indicates whether the field is empty */
    bool *isKey;  /* Indicates whether a value is present in the key */
} table;

typedef struct tables
{
    table *t;     /* One table in the database */
    tables *next; /* Pointer to the next table */
} tables;

typedef struct database
{
    tables *tList; /* Tables to be implemented as a linked list */
    int n;         /* Number of entries */
    char *name;    /* Name of the table */
} database;

/* Creates and returns a new database */
database *create_database(char *name)
{
    database *newDatabase = (database *)malloc(sizeof(database)); // Initializing a new database
    newDatabase->name = name;
    newDatabase->n = 0; // Initially database is empty
    return newDatabase;
}

void show_table(database *d)
{
    database *temp = (database *)malloc(sizeof(database));
    temp = d;
    printf("+-----------------+\n");
    printf("| Tables in %s \n", temp->name);
    printf("+-----------------+\n");
    for (int i = 0; i < d->n; i++)
    {
        printf("| %s           \n", temp->tList->t);
        printf("+-----------------+\n");
        temp = temp->tList->next;
    }
}

void insert_table(database *d, table *t)
{
}

void desc_table(database *d, table *t)
{
}

void remove_table(database *d, char *name)
{
}

void insert_key(database *d, table *t, int key_value)
{
}
