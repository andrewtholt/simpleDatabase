#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include "db.h"
void            print_record();

#define DEBUG
main()
{
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

	if(!table)
	  {
	    fprintf(stderr,"Fatal Error: failed to create database\n");
	    exit(1);
	  }
	
//	db_setattr(table,FIXED|NEVER_SHRINK|STAMP,0,10,10);
	db_setattr(table,NEVER_SHRINK,0,10,10);

	printf("\nSet Attributes ... \n");
	db_status(table);

	status=db_load("tst.db", table);
//	status=db_load("fred.db", table);
	if(!status)
	  {
	    printf("Load faiure\n");
	  }

	printf("\nLoaded data ...\n");
	db_status(table);


	printf("\nPerforming lookup ...\n");
	np=find_first("ANDRE",table);
	print_record(np);
	if(np)
	{
		bucket_stats(table);
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

//	fp=fopen("tst1.db","w");

	fp=stdout;

	db_dump(fp,table);
	db_dump(stdout,table);
//	bucket_stats(table);
}

void 
print_record(r)
	struct nlist   *r;
{
	if (r != NULL)
	{
		printf("\n\tName:\t%s\n", r->name);
		printf("\tdef:\t%s\n", r->def);
		printf("\tUpdate time:\t%d\n",r->updateTime);
	} else
	{
		printf("\nEmpty record\n");
	}
}
