#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "db.h"
#include "set.h"

void updateCallback(char *key, char *value,int id) {
    printf("Over load me\n");
}
/*
 * static struct nlist *hashtab[HASHSIZE];
 *
 * static struct hash_entry *hashtab[HASHSIZE];
 static struct hash_entry **hashtab;
 */

// static int      HASHSIZE = 100;
static int      record_count = 1;
static int      bucket = -1;
static struct nlist *last_np = NULL;

void            pre_allocate_records();

int hash( struct database *db, const char *s) {
    int             hashval;

    for (hashval = 0; *s != '\0';) {
        hashval += *s++;
    }

    return (hashval % db->hashsize);
}

/**
 * @brief Lookup record
 * @param s Data element name
 * @param db databae handle
 * @return pointer to record.
 **/
struct nlist *lookup(const char *s, struct database *db) {
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

/**
 * @brief Lookup a matching record.<br>
 * Wild card lookup return first record with the key field that contains the
 * given string.
 * @param s Data element name
 * @param db databae handle
 * @return pointer to record.
 **/
struct nlist *wild_key_lookup(const char *s, int instance, struct database *db) {
    struct nlist   *np;
    int             i;
    char           *tmp;

    if (instance == 1) {
        bucket = 0;
    }

    for (i = bucket; i < db->hashsize ; i++) {

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

/**
 * @brief Lookup a matching record, by its definition.<br>
 * Similar to wild_key_lookup, but looks in the definition field instead. 
 * @param s Data element definition.
 * @param db database handle
 * @return pointer to record.
 **/

struct nlist *wild_def_lookup(const char *s, int instance, struct database *db) {
    struct nlist   *np;
    char           *tmp;
    int             i;
    static int      bucket = -1;

    if (instance == 0) {
        bucket = 0;
    }

    for (i = bucket; i < db->hashsize; i++) {

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

/**
 * @brief Lookup first record with matching definition.<br>
 * @param s Data element definition.
 * @param db database handle.
 * @return pointer to record.
 **/
struct nlist *find_first_def( const char *s, struct database *db) {
    struct nlist   *np;
    struct nlist   *wild_def_lookup();
    extern int      record_count;

    record_count = 0;

    np = wild_def_lookup(s, record_count, db);
    return (np);
}

/**
 * @brief Lookup next record with matching definition.<br>
 * @param s Data element definition.
 * @param db database handle.
 * @return pointer to record.
 **/
struct nlist   *find_next_def( char *s, struct database *db) {
    struct nlist   *np;
    struct nlist   *wild_def_lookup();
    extern int      record_count;

    record_count++;

    np = wild_def_lookup(s, record_count, db);
    return (np);
}

/**
 * @brief Lookup first record with matching name.<br>
 * @param s Data element name
 * @param db database handle
 * @return pointer to record.
 **/
struct nlist   *find_first( const char *s, struct database *db) {

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

/**
 * @brief Lookup next record with matching name.<br>
 * @param s Data element name
 * @param db database handle
 * @return pointer to record.
 **/
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

/**
 * @brief Add  record
 * @param name Data element name
 * @param def Data element value
 * @param db databae handle
 * @return pointer to new record.
 **/
struct nlist *db_install( const char *name,const char *def, struct database *db) {
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
            if (!ent) {
                return (NULL);
            }

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
            if (np == NULL) {
                return (NULL);
            }
        }
        memset(np,0,sizeof(np));

        np->bucket_number = hashval;

//        if (db->flags & FIXED) {
//            if (!(db->flags & (FIXED_DB_SIZE | NEVER_SHRINK))) {
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

                if (db->flags & STAMP) {
                    np->updateTime = time(NULL);
                } else {
                    np->updateTime = 0;
                }

                np->subSet = setNew(MAX_SUB);
                np->cb_ptr = NULL;
//            }
//        } else {
//            (void)strncpy(np->name,name,sizeof(np->name));
//            (void)strncpy(np->def,def,sizeof(np->def));
//            db->hash_table[hashval]->ref_count++;
//            return (np);
//            /*
//               if (((np->name = strsave(name)) == NULL) && ((np->def = strsave(def)) == NULL)) {
//               db->hash_table[hashval]->ref_count++;
//               return (NULL);
//               }
//               */
//        }
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
        // free(np->def);
        // np->def=(char *)strsave(def);
        (void)strncpy(np->def, def, sizeof(np->def));
    }
    return (np);
}

void nlist_sub(int id) {
}

/**
 * @brief Update record.
 * @param s Data element handle.
 * @param s New definition.
 * @param db database handle.
 * @return void.
 **/
// void db_update(struct nlist *np, char *def, struct database *db) {
void db_update(const char *key, const char *def, struct database *db) {

    bool changed = false;

    struct nlist *np = find_first(key,db);

    // 
    // Doesn't exist, so create and retrn
    //
    if(np == NULL) {
        db_install(key,def,db);
        return;
    }

    changed = (!strcmp(np->def, def)) ? false : true ;

    if(changed == true) {
        if (db->flags & FIXED) {
            (void) memset(np->def, (int) 0, (size_t) db->def_size);
            strncpy(np->def, def, strlen(def));
        } else {
            (void)strncpy(np->def,def,sizeof(np->def));
        }

        if( np->published == true) {
//            printf("PUBLISH\n");

            for(int i=0; i < (np->subSet->size); i++) {
                if( np->subSet->data[i] > 0) {
                //
                // TODO callback to update subscribers here
                //
//                    printf("\t%10s:%10s: notify:%4d\n",np->name, np->def,np->subSet->data[i]);
                    updateCallback(np->name, np->def,np->subSet->data[i]);
                }
            }
        }
    }

    if (db->flags & STAMP) {
        np->updateTime = time(NULL);
    } else {
        np->updateTime = 0;
    }
}


// void db_dump( FILE *fp, struct database *db) {
void db_dump( char *fname, struct database *db) {
    int             i;
    struct nlist   *np;

    FILE *fp = fopen(fname,"w");

    if( fp == NULL ) {
        fprintf(stderr, "Failed to open %s\n",fname);
        return;
    }

    fprintf(fp, "# flags:name_size:def_size:number_of_records\n");
    fprintf(fp, "%d:%d:%d:%d\n", db->flags, db->name_size, db->def_size, db->max_num_records);
    // for (i = 0; i < HASHSIZE; i++) {
    for (i = 0; i < db->hashsize; i++) {
        if (db->hash_table[i]) {
            np = db->hash_table[i]->hash_head;

            while (np != NULL){
                fprintf(fp, "%s\t%s\t%d\n", np->name, np->def,(int)np->updateTime);

                np = np->next;
            }

        }
    }
    fclose( fp );
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
    char scratch_buffer[MAX_REC_SIZE];

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

    //    char scratch_buffer[MAX_REC_SIZE];

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
                //                fixed_width_print(np->name, db->name_size);
                //                printf("\tName\t\t:%s:\n", scratch_buffer);
                printf("\tName\t\t:%s:\n", np->name);

                //                fixed_width_print(np->def, db->def_size);
                //                printf("\tDefinition\t:%s:\n", scratch_buffer);
                printf("\tDefinition\t:%s:\n", np->def);

                printf("\tPublished\t:");
                if( np->published == true ) {
                    printf("YES\n");
                } else {
                    printf("NO \n");
                }

                setDisplay( np->subSet );
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
    if( max_num_recs > 0) {
        db->max_num_records = max_num_recs;
    }
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
            if(db->flags & STAMP)
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
        (void)memset(np->name,0,sizeof(np->name));
        (void)memset(np->def,0,sizeof(np->def));
        /*
           np->name = (char *) malloc(db->name_size);
           np->def = (char *) malloc(db->def_size);

           if ((!np->name) || (!np->def)) {
           fprintf(stderr, "pre_allocate_records: Failed to allocate space for date for entry %d\n", i);
           exit(-1);
           }
           */
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
            // 
            // Alocations all OK, so add to free list.
            //
            np->next = db->free_rec_list;
            db->free_rec_list = np;
            db->free_rec_count++;
            db->max_num_records++;

            /*
               np->name = (char *) malloc(db->name_size);
               np->def = (char *) malloc(db->def_size);

               if ((!np->name) || (!np->def)) {
               free(np);
               exit_flag=1;
               } else {
            // 
            // Alocations all OK, so add to free list.
            //
            np->next = db->free_rec_list;
            db->free_rec_list = np;
            db->free_rec_count++;
            db->max_num_records++;
            }
            */
        }
    }
    return(added);
}			

/**
 * @brief Delete record
 * @param np record handle
 * @param db databae handle
 * @return void.
 **/
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

/**
 * @brief Create empty database
 * @param hashsize Number of has buckets, or linked lists.
 * @return db handle.
 **/
struct database *db_create(int    hashsize) {
    struct database *table;
    int             i;

    table = (struct database *) malloc(sizeof(struct database));

    if (table) {
        table->hashsize = hashsize;
//        table->flags    = 0x39;
        table->flags    = MATCH|STAMP|NEVER_SHRINK|FIXED;
        printf("flags= 0x%02x\n", table->flags);

        table->name_size = MAX_NAME;
        table->def_size = MAX_DEF;
        table->free_rec_list = (struct nlist *) NULL;
        table->free_rec_count = 0;
        table->max_num_records = 0;
        table->alarm_level=100; // Default is alarm when full.
        table->locked = false;  // Otherwise we wont be able to add new records.
        table->hash_table = (struct hash_entry **) malloc(table->hashsize * (sizeof(struct hash_entry)));

        if (table->hash_table) {
            for (i = 0; i < hashsize; i++) {
                table->hash_table[i] = (struct hash_entry *) NULL;
            }
        }
    }
    return (table);
}

void db_publish(const char *key, bool state, struct database *db) {
    struct nlist *np = find_first( key, db) ;

    if( np != NULL ) {
        np->published = state;
    }
}

void db_subscribe(const char *key, const int id, struct database *db) {
    struct nlist *np = find_first( key, db) ;

    if( np != NULL ) {
        setAdd(np->subSet, id);
    }
}

void db_set_key_len(int len, struct database *db) {
#ifndef MAX_NAME
    db->name_size = len;
#endif
}

void db_set_def_len(int len, struct database *db) {
#ifndef MAX_DEF
    db->def_size = len;
#endif
}
