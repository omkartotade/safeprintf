/*

The program is using sprintf for copying the user inputs to buffers, and in the fprintf function, 
it writes to the filewithout specifying any format. It should ideally write to the file using the %s
format specifier. Infact sprintf is also vunerable to buffer overflow in this case.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int calculateChars(char *item);

int main (int argc, char *argv[])
{
	char country[100];
	char continent[100];
	if (argc!=3)
	{
		fprintf(stderr, "Usage: %s <name of country> <continent>\n", argv[0]);
	  	return -1;
	}
	sprintf (country,argv[1]);
	sprintf (continent,argv[2]);
	int charactersCountry=calculateChars(country);
	int charactersContinent=calculateChars(continent);
	printf("%s=%d\n","Number of characters in your country",charactersCountry);
	printf("%s=%d\n","Number of characters in your continent",charactersContinent);
	return 0;
}

int calculateChars(char *item)
{
	int count;
	FILE *file;
	file=fopen("testcase3.txt","w+");
	fprintf(file,item);
	count=strlen(item);
	return count;
}