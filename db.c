#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "db.h"

/*
 * static struct nlist *hashtab[HASHSIZE];
 */

/*
 * static struct hash_entry *hashtab[HASHSIZE];
 static struct hash_entry **hashtab;
 */

static int      HASHSIZE = 100;
static int      record_count = 1;
static int      bucket = -1;
static struct nlist *last_np = NULL;

void            pre_allocate_records();

int hash( struct database *db, char *s) {
    int             hashval;

    for (hashval = 0; *s != '\0';) {
        hashval += *s++;
    }

    return (hashval % db->hashsize);
}

struct nlist   *lookup(char *s, struct database *db) {
    struct nlist   *np;
    int             hashval;

    hashval = hash(db, s);

    if (db->hash_table[hashval] != NULL) {

        for (np = db->hash_table[hashval]->hash_head; np != NULL; np = np->next) {
            if (db->flags & FIXED) {
                /*
                 * sscanf(np->name,"%s",scratch);
                 */
                if (strcmp(s, np->name) == 0) {
                    db->hash_table[hashval]->ref_count++;
                    bucket = hashval;
                    last_np = np;
                    return (np);
                }
            } else {

                if (strcmp(s, np->name) == 0) {
                    db->hash_table[hashval]->ref_count++;
                    bucket = hashval;
                    last_np = np;
                    return (np);
                }
            }
        }
    }
    return (NULL);
}

/*
 * Wild card lookup Return first record with the key field that contains the
 * given string
 */

struct nlist *wild_key_lookup( char *s, int instance, struct database *db) {
    struct nlist   *np;
    int             i;
    char           *tmp;

    if (instance == 1) {
        bucket = 0;
    }

    for (i = bucket; i < HASHSIZE; i++) {

        if (db->hash_table[i]) {

            if (instance != 1) {
                np = last_np->next;
                instance = 1;
            } else {
                np = db->hash_table[i]->hash_head;
            }

            while (np != NULL) {
                tmp = strstr(np->name, s);

                if (tmp != NULL) {
                    db->hash_table[i]->ref_count++;
                    bucket = i;
                    last_np = np;
                    return (np);
                }
                np = np->next;
            }

        }
    }
    return (NULL);
}

/* similar to wild_key_lookup, but looks in the definition field instaead */

struct nlist *wild_def_lookup(char *s, int instance, struct database *db) {
    struct nlist   *np;
    char           *tmp;
    int             i;
    static int      bucket = -1;

    if (instance == 0) {
        bucket = 0;
    }

    for (i = bucket; i < HASHSIZE; i++) {

        if (db->hash_table[i]) {
            np = db->hash_table[i]->hash_head;

            do {
                tmp = strstr(np->def, s);

                if (tmp != NULL) {
                    if (--instance < 0) {
                        db->hash_table[i]->ref_count++;
                        return (np);
                    }
                }
                np = np->next;
            }
            while (np != NULL);
        }
    }
    return (NULL);
}

struct nlist *find_first_def( char *s, struct database *db) {
    struct nlist   *np;
    struct nlist   *wild_def_lookup();
    extern int      record_count;

    record_count = 0;

    np = wild_def_lookup(s, record_count, db);
    return (np);
}

struct nlist   *find_next_def( char *s, struct database *db) {
    struct nlist   *np;
    struct nlist   *wild_def_lookup();
    extern int      record_count;

    record_count++;

    np = wild_def_lookup(s, record_count, db);
    return (np);
}

struct nlist   *find_first( char           *s, struct database *db) {

    struct nlist   *np= (struct nlist *)NULL;
    struct nlist   *lookup();
    struct nlist   *wild_key_lookup();
    static int      record_count = 1;

    np = lookup(s, db);

    if (np) {
        return (np);
    }

    if(!(db->flags & MATCH)) {
        np = wild_key_lookup(s, record_count, db);
    }

    return (np);
}

struct nlist   *find_next( char *s, struct database *db) {
    struct nlist   *np;
    struct nlist   *wild_key_lookup();
    extern int      record_count;

    record_count++;

    np = wild_key_lookup(s, record_count, db);
    return (np);
}

char *strsave(char *s) {
    char           *p;

    if ((p = (char *) malloc(strlen(s) + 1)) != NULL)
        strcpy(p, s);
    return (p);
}


struct nlist *db_install( char *name, char *def, struct database *db) {
    struct nlist   *np, *lookup();
    struct hash_entry *ent;

    char           *strsave();
    int             hashval;

    if ((db->flags & FIXED_DB_SIZE) && (db->free_rec_count == 0))
        return (NULL);

    if (((np = lookup(name, db)) == NULL) || (db->flags & DUPLICATE)) {
        hashval = hash(db, name);

        if (!db->hash_table[hashval]) {
            ent = (struct hash_entry *) malloc(sizeof(*ent));
            if (!ent)
                return (NULL);

            ent->hash_head = 0;
            ent->ref_count = 0;
            ent->rec_count = 0;
            db->hash_table[hashval] = ent;
        }

        if ((db->flags & FIXED) && (db->free_rec_list != 0)) {

            np = db->free_rec_list;
            db->free_rec_list = np->next;
            db->free_rec_count--;
        } else {
            np = (struct nlist *) malloc(sizeof(*np));
            if (np == NULL)
                return (NULL);
        }
        np->bucket_number = hashval;

        if (db->flags & FIXED) {
            if (!(db->flags & (FIXED_DB_SIZE | NEVER_SHRINK)))
            {
                np->name = (char *) malloc(db->name_size);
                np->def = (char *) malloc(db->def_size);
                bzero(np->name, db->name_size);
                bzero(np->def, db->def_size);
            }
            {
                int             name_len;
                int             def_len;

                name_len = strlen(name);
                def_len = strlen(def);

                (void) memcpy(np->name, name, name_len);
                /*
                 *(np->name+db->name_size)=(char)NULL;
                 */
                *(np->name+name_len)=(char)0x00;

                (void) memcpy(np->def, def, def_len);
                /*
                 *(np->def+db->def_size)=(char)NULL;
                 */
                *((char *)np->def+def_len)=(char)0x00;

                if (db->flags && STAMP) {
                    np->updateTime = time(NULL);
                } else {
                    np->updateTime = 0;
                }
            }
        } else {
            if (((np->name = strsave(name)) == NULL) && ((np->def = strsave(def)) == NULL)) {
                db->hash_table[hashval]->ref_count++;
                return (NULL);
            }
        }
        /* hashval = hash(np->name); */
        np->next = db->hash_table[hashval]->hash_head;
        db->hash_table[hashval]->hash_head = np;
        db->hash_table[hashval]->ref_count = 0;
        db->hash_table[hashval]->rec_count++;
        np->prev = (struct nlist *) NULL;

        if (db->hash_table[hashval]->rec_count > 1) {
            np->next->prev = np;
        }
    } else {
        free(np->def);
        np->def=(char *)strsave(def);
    }
    return (np);
}


void db_update(struct nlist *np, char *def, struct database *db) {

    if (db->flags & FIXED) {
        (void)memset(np->def, (int) ' ', db->def_size);
        strncpy(np->def, def, strlen(def));
    } else {
        if (strlen(np->def) <= strlen(def)) {
            strcpy(np->def, def);
        } else {
            np->def = (char *) realloc(np->def,strlen(def));
            if (np->def)
                strcpy(np->def, def);
        }
    }
    if (db->flags && STAMP)
        np->updateTime = time(NULL);
    else
        np->updateTime = 0;
}


void db_dump( FILE           *fp, struct database *db) {
    int             i;
    struct nlist   *np;

    fprintf(fp, "# flags:name_size:def_size:number_of_records\n");
    fprintf(fp, "%d:%d:%d:%d\n", db->flags, db->name_size, db->def_size, db->max_num_records);
    for (i = 0; i < HASHSIZE; i++) {
        if (db->hash_table[i]) {
            np = db->hash_table[i]->hash_head;

            do {
                fprintf(fp, "%s\t%s\t%d\n", np->name, np->def,(int)np->updateTime);

                np = np->next;
            }
            while (np != NULL);

        }
    }

}

int db_count_records(struct database *db) {

    int             i;
    int             sum = 0;

    for (i = 0; i < db->hashsize; i++) {
        if (db->hash_table[i])
            sum += db->hash_table[i]->rec_count;
    }

    return (sum);
}


void db_status( struct database *db) {

    printf("\n\t\tDatabase status\n");
    printf("\n\nHash value is %d\n", db->hashsize);
    if (db->flags & DUPLICATE)
        printf("Duplicate keys\n");
    else
        printf("Unique keys\n");

    if (db->flags & FIXED_DB_SIZE)
        printf("Database size fixed\n");
    else
        printf("Database size variable\n");

    if (db->flags & FIXED) {
        printf("Fixed Length Records\n");
        printf("\tName length = %d\n", db->name_size);
        printf("\tDef  length = %d\n", db->def_size);

        if (db->flags & FIXED_DB_SIZE)
            printf("\tMax Number of Records = %d\n", db->max_num_records);

        printf("\tNumber of records on free list = %d\n", db->free_rec_count);
    } else
        printf("\nVariable length records\n");

    printf("\t%d records in database\n", db_count_records(db));

    printf("\n\n");
}


void fixed_width_print(char *s, int width) {
    int             i;
    int             len;

    len = strlen(s);

    (void)memset(scratch_buffer, 0, MAX_REC_SIZE);

    if (len == width) {
        strcpy(scratch_buffer, s);
    } else {
        sprintf(scratch_buffer, "%s", s);
        for (i = len; i < width; i++) {
            scratch_buffer[i] = ' ';
        }
    }
}


void debug_dump(struct database *db) {
    int             i;
    struct nlist   *np;

    db_status(db);

    for (i = 0; i < db->hashsize; i++) {

        if (!db->hash_table[i]) {
            printf("Bucket %d empty\n", i);
        } else {
            printf("Bucket %d\n", i);
            printf("\tReferenced\t:%d times\n", db->hash_table[i]->ref_count);
            printf("\tContains\t:%d records\n", db->hash_table[i]->rec_count);
            np = db->hash_table[i]->hash_head;

            do {
                fixed_width_print(np->name, db->name_size);
                printf("\tName\t\t:%s:\n", scratch_buffer);

                fixed_width_print(np->def, db->def_size);
                printf("\tDefinition\t:%s:\n", scratch_buffer);
                printf("\tBucket Number\t:%d\n", np->bucket_number);
                printf("\n");
                np = np->next;
            }
            while (np != NULL);
        }
    }
}



void bucket_stats( struct database *db) {
    int             i;

    for (i = 0; i < db->hashsize; i++) {

        if (!db->hash_table[i]) {
            printf("Bucket %d empty\n", i);
        } else {
            printf("Bucket %d\n", i);
            printf("\tReferenced\t:%d times\n", db->hash_table[i]->ref_count);
            printf("\tContains\t:%d records\n", db->hash_table[i]->rec_count);
        }
    }
}


void db_setattr(struct database *db, int flags, int max_num_recs, int name_size, int def_size) {
    db->flags = flags;
    db->max_num_records = max_num_recs;
    db->name_size = name_size;
    db->def_size = def_size;
}

int db_load(char *filename,struct database *db) {
    FILE           *fp;
    struct nlist *np;
    char           *rec;
    char           *name;
    char           *def;
    char           *tmp;
    time_t stamp;

    char            buffer[MAX_REC_SIZE];

    fp = fopen(filename, "r");
    if (!fp) {
        return (0);
    }


    do {
        rec = fgets(buffer, MAX_REC_SIZE, fp);
    } while (*rec == '#');

    tmp = strtok(buffer, ":");
    db->flags = atoi(tmp);

    if (db->flags == 0)
        db->flags = 1;

    tmp = strtok(NULL, ":");
    db->name_size = atoi(tmp);
    tmp = strtok(NULL, ":");
    db->def_size = atoi(tmp);
    tmp = strtok(NULL, ":");
    db->max_num_records = atoi(tmp);

    if (db->flags & FIXED_DB_SIZE) {
        pre_allocate_records(db);
    }

    while (rec = fgets(buffer, MAX_REC_SIZE, fp)) {
        if (rec) {
            name = strtok(buffer, "\t");
            def = strtok(NULL, "\t");
            tmp = (char *)strtok(NULL,"\t\n");
            if(!tmp) 
                stamp = 0;
            else
                stamp = atoi(tmp);
        }

        if ((name != NULL) & (def != NULL)) {
            np= db_install(name, def, db);
            if(db->flags && STAMP)
            {
                if(stamp<=0)
                    np->updateTime=time(NULL);
                else
                    np->updateTime=stamp;
            } else {
                np->updateTime=0;
            }
        }
    }
    fclose(fp);

    return (-1);
}

void pre_allocate_records(struct database *db) {
    int             i;
    int             numrec;
    struct nlist   *np;

    numrec = db->max_num_records;

    for (i = 0; i < numrec; i++) {
        np = (struct nlist *) malloc(sizeof(struct nlist));

        if (!np) {
            fprintf(stderr, "pre_allocate_records: Failed to allocate space for record %d\n", i);
            exit(-1);
        }
        np->name = (char *) malloc(db->name_size);
        np->def = (char *) malloc(db->def_size);

        if ((!np->name) || (!np->def)) {
            fprintf(stderr, "pre_allocate_records: Failed to allocate space for date for entry %d\n", i);
            exit(-1);
        }
        np->next = db->free_rec_list;
        db->free_rec_list = np;
    }
    db->free_rec_count = numrec;
}

void mv_to_free(struct nlist *np, struct database *db) {
    np->next = db->free_rec_list;
    db->free_rec_list = np;
    db->free_rec_count++;
}

int add_to_free(struct database *db, int count) {
    int added=0;		
    int exit_flag=0;
    struct nlist *np;

    for(added=0;((added < count) & !exit_flag);added++) {
        np = (struct nlist *) malloc(sizeof(struct nlist));

        if(!np) {
            exit_flag=1;
        } else {

            np->name = (char *) malloc(db->name_size);
            np->def = (char *) malloc(db->def_size);

            if ((!np->name) || (!np->def)) {
                free(np);
                exit_flag=1;
            } else {
                /* 
                 * Alocations all OK, so add to free list.
                 */
                np->next = db->free_rec_list;
                db->free_rec_list = np;
                db->free_rec_count++;
                db->max_num_records++;
            }
        }
    }
    return(added);
}			


void db_delete(struct nlist   *np, struct database *db) {

    int             hashval;
    int             rec_count;

    if (!np)
        return;

    hashval = np->bucket_number;
    rec_count = db->hash_table[hashval]->rec_count;

    switch (rec_count) {
        case 0:
            fprintf(stderr, "Fatal error: Record found by lookup, bucket reports no records\n");
            exit(1);
            break;
        case 1:

            if (db->flags & FIXED) {
                bzero(np->name, db->name_size);
                bzero(np->def, db->def_size);
                mv_to_free(np,db);
                /*
                   np->next = db->free_rec_list;
                   db->free_rec_list = np;
                   db->free_rec_count++;
                   */
            } else {
                free(np);
                free(db->hash_table[hashval]);
            }
            db->hash_table[hashval] = (struct hash_entry *) NULL;
            break;
        default:
            if (np->next)
                np->next->prev = np->prev;

            if (np->prev)
                np->prev->next = np->next;

            db->hash_table[hashval]->rec_count--;

            if (db->flags & (FIXED)) {
                np->next = db->free_rec_list;
                db->free_rec_list = np;
                db->free_rec_count++;
            }
            break;
    }
}


struct database *db_create(unsigned int    hashsize) {
    struct database *table;
    int             i;

    table = (struct database *) malloc(sizeof(struct database));

    if (table) {
        table->hashsize = hashsize;
        table->name_size = -1;
        table->def_size = -1;
        table->free_rec_list = (struct nlist *) NULL;
        table->free_rec_count = 0;
        table->max_num_records = 0;
        table->alarm_level=100; /* Default is alarm when full */
        table->hash_table = (struct hash_entry **) malloc(table->hashsize * (sizeof(struct hash_entry)));

        if (table->hash_table) {
            for (i = 0; i < hashsize; i++) {
                table->hash_table[i] = (struct hash_entry *) NULL;
            }
        }
    }
    return (table);
}

void db_set_key_len(int len, struct database *db) {
    db->name_size = len;
}

void db_set_def_len(int len, struct database *db) {
    db->def_size = len;
}
