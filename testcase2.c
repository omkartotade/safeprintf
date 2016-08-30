/*
The strcpy(buffer,arg) line in the copytobuffer function is vulnerable here, since it does not
specify any format specifier while copying arg to buffer. Hence one or more %n used here can 
behave maliciously.
*/

#include <stdio.h>

int copytobuffer(char *arg);

int main(int argc, char** argv)
{	
	if (argc!=2)
	{
		fprintf(stderr, "Usage: %s <any string>\n", argv[0]);
	  	return -1;
	}
	copytobuffer(argv[1]);
	return 0;	
}

int copytobuffer(char *arg)
{
	char buffer[256];
	strcpy(buffer,arg);	
	snprintf(buffer, sizeof buffer, arg);
	printf("Buffer contents: %s\n", buffer);
	return 0;
}

