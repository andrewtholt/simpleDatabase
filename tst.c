#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "db.h"
void            print_record();

#define DEBUG
int main() {
    struct nlist   *lookup();
    struct nlist   *install();
    struct nlist   *find_first();
    struct nlist   *find_next();

    char            name[255];
    char            def[255];
    struct nlist   *record;
    struct database *table;
    struct nlist *np;
    int status;
    int count;

    FILE *fp;

    table=db_create(101);

    if(!table) {
        fprintf(stderr,"Fatal Error: failed to create database\n");
        exit(1);
    }

    //	db_setattr(table,FIXED|NEVER_SHRINK|STAMP,0,10,10);

    db_status(table);

    status=db_load("tst.db", table);

    if(!status) {
        fprintf(stderr,"Load faiure\n");
        exit(1);
    }

    /*
    printf("\nSet Attributes ... \n");
    db_setattr(table,NEVER_SHRINK|STAMP|FIXED,0,10,10);
    */
    printf("max records %d\n", table->max_num_records);

    printf("\nLoaded data ...\n");
    db_status(table);

    printf("\nPerforming lookup ...\n");
    np=find_first("ANDREW",table);

    print_record(np);

    if(np) {
//        bucket_stats(table);
        db_update(np,(char *)"Changed",table);       
        /*
           db_delete(np,table);
           */
    }
    db_status(table);
    np=db_install("1000","NEW TEST",table);

    db_status(table);
    printf("Grow table by 100\n");
    count=add_to_free(table,100);
    printf("%6d records added\n\n",count);
    db_status(table);

    fp=fopen("tst1.db","w");

    // fp=stdout;

    db_dump(fp,table);
    db_dump(stdout,table);
    //	bucket_stats(table);
}

void print_record( struct nlist   *r) {

    if (r != NULL) {
        printf("\n\tName:\t%s\n", r->name);
        printf("\tdef:\t%s\n", (char *)r->def);
        printf("\tUpdate time:\t%d\n",(int)r->updateTime);
    } else {
        printf("\nEmpty record\n");
    }
}

