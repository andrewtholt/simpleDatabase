#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

#ifndef _DB_H
#define _DB_H

#define NAME_LEN 32
#define DEF_LEN 32

struct nlist {
  char name[NAME_LEN];

  char def[DEF_LEN];

  time_t ttl;

  int bucket_number;
  time_t updateTime;
  
  bool dontSave;        // If true dump wont outpit this.
  struct nlist *next;
  struct nlist *prev;
};

struct hash_entry {
  struct nlist *hash_head;
  int ref_count;
  int rec_count;
};

/* Database properties held in flags */

#define FIXED         0x01
#define DUPLICATE     0x02
#define FIXED_DB_SIZE 0x04
#define NEVER_SHRINK  0x08
#define STAMP         0x10
#define MATCH         0x20 /* find must be a perfect match */

struct database {
  struct hash_entry **hash_table;
  int hashsize;
  unsigned int flags;
  struct nlist *free_rec_list;
  int free_rec_count;
  int max_num_records;	/* only has meaning if FIXED_DB_SIZE set */
  int name_size;
  int def_size;
  int alarm_level;	/* % at which database is nearly full */
};

#define MAX_REC_SIZE 1024
// char scratch_buffer[MAX_REC_SIZE];

#define FREE -1
#define IN_USE 0
/*
All databases have four basic functions :-

Create
Retrieve
Update
Delete

So here are mine */

/* Create & update */
struct database *db_create(int);

struct nlist *db_install( char *name, char *def, struct database *db);
struct nlist *install();
/* Retrieve */
struct nlist *find_first(char *, struct database *);
struct nlist *find_next();
struct nlist *find_first_def();
struct nlist *find_next_def();
struct nlist   *find_first_def();
struct nlist   *find_first_def();

/* Delete */
// void delete();

/* Utilities */
// Update
void db_update(struct nlist *, char *, struct database *);
void db_setattr(struct database *, int, int , int , int);
void db_dump();
void debug_dump(struct database *);
void bucket_stat();
int db_load(char *, struct database *);
void db_status( struct database *);

void db_set_key_len();
void db_set_def_len();

int db_get_key_len();
int db_get_def_len();

#endif

