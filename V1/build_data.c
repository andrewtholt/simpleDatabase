#include <stdio.h>

main(argc,argv)
int argc;
char *argv[];
{
	int i;
	int rec_count;

	rec_count=atoi(argv[1]);

	printf("0:0:0\n");
	for(i=0;i<rec_count;i++)
	{
		printf("%d\tTEST %d\n",i,i);
	}
}
