#include <stdio.h>
#include "db.h"

main()
{
	char buffer[128];
	char buffer1[128];
	char *ptr;

	strcpy(buffer1,"This is a test");

	ptr=(char *)memset( (void *)buffer,(int)' ',128);
	(void) memcpy(buffer,buffer1,strlen(buffer1));


}

