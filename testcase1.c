/*Here, we have used sprintf function, which takes the command line argument 
string and copies it into buf. The sprintf function is vulnerable to various 
format specifiers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int charinvertpass (char *str);

int main(int argc, char** argv)
{
	if (argc!=2)
	{
		fprintf(stderr,"Usage %s <Enter password>", argv[0]);
		return -1;
	}

	char buf[100];	
	sprintf(buf,argv[1]);
	charinvertpass(buf);
	return 0;
}

int charinvertpass (char *str)
{
	char istr[strlen(str)];
	int i=0;
	int j=strlen(str)-1;
	for (i=0;i<strlen(str);i++)
	{
		istr[j]=str[i];
		j--;
	}
	printf (istr);
	printf("\n");
	return 0;
}