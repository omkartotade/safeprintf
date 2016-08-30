#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

int new_vprintf(const char *vformat, va_list varg, ...);
int new_vfprintf(FILE *file, const char *vfformat, va_list vfarg, ...);
int new_vsprintf(char *str, const char *vsformat, va_list vsarg, ...);
int new_vsnprintf(char *snstr, size_t size, const char *vsnformat, va_list vsnfarg, ...);
int findNumber(char *num_array);
//static int (*orig_puts)(const char *put) = NULL;
static int (*orig_printf)(const char *format, ...) = NULL;
static int (*orig_fprintf)(FILE *file,const char *format, ...) = NULL;
static int (*orig_sprintf)(char * str,const char *format, ...) = NULL;
static int (*orig_snprintf)(char * str,size_t size,const char *format, ...) = NULL;
char *n="%n";
char *x25="\x25";
char *str_to_print;
//char * removeAlln(const char * buf);

int printf (const char *format, ...)
{
	//variables
	int i=0;
	int out_int;
	int *out_n;
	//char temp;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char * str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	int count=0;
	va_list argp;
	va_start(argp, format);

	for (i=0;format[i]!='\0';)
	{
		if (format[i]=='%')
		{	
			//
			i=i+1;
			while (format[i]=='0'||format[i]=='1'||format[i]=='2'||format[i]=='3'||format[i]=='4'||format[i]=='5'||format[i]=='6'||format[i]=='7'||format[i]=='8'||format[i]=='9'||format[i]=='$'||format[i]=='*'||format[i]=='.')
			//while (!isalpha(format[i]))
			{
				if (format[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=format[i];
					i=i+1;					
				}	
			}
			//number=findNumber(number_array);
			//
			if (format[i]=='d')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%d",out_int);
				i=i+1;			//
			}
			else if (format[i]=='i')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%i",out_int);
				i=i+1;			//
			}
			else if (format[i]=='s')
			{
				out_string=va_arg(argp, char*);
				count=count+strlen(out_string);
				(orig_printf)("%s",out_string);
				i=i+1;			//
			}
			else if (format[i]=='c')
			{
				out_char=va_arg(argp, int);
				count++;
				(orig_printf)("%c",out_char);
				i=i+1;			//
			}
			else if (format[i]=='x')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%x",out_hex_int);
				i=i+1;			//
			}
			else if (format[i]=='X')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%X",out_hex_int);
				i=i+1;	
			}
			else if (format[i]=='f')
			{
				out_f=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				(orig_printf)("%f",out_f);
				i=i+1;			//
			}
			else if (format[i]=='u')
			{
				out_unsigned_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%u",out_unsigned_int);
				i=i+1;			//
			}
			//new
			else if (format[i]=='h')
			{
				if (format[i+1]=='n')
				{
					out_n=(int *)va_arg(argp,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",format[i]);
					i=i+1;
				}
			}
			else if (format[i]=='e')
			{
				out_e=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (format[i]=='o')
			{
				out_o=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (format[i]=='p')
			{
				out_p=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (format[i]=='a')
			{
				out_a=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (format[i]=='n')
			{
				out_n=(int *)va_arg(argp,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (format[i]=='%')
			{
				count++;
				(orig_printf)("%c",format[i]);
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			(orig_printf)("%c",format[i]);
			i++;
		}
	}
	va_end(argp);
	return 0;
}

int fprintf (FILE * file, const char *fmt, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_fprintf=(int (*)(FILE *file,const char *format, ...))dlsym(RTLD_NEXT,"fprintf");
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char *str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	int count=0;
	va_list argp;
	va_start(argp, fmt);

	for (i=0;fmt[i]!='\0';)
	{
		if (fmt[i]=='%')
		{
			//
			i=i+1;
			while (fmt[i]=='0'||fmt[i]=='1'||fmt[i]=='2'||fmt[i]=='3'||fmt[i]=='4'||fmt[i]=='5'||fmt[i]=='6'||fmt[i]=='7'||fmt[i]=='8'||fmt[i]=='9'||fmt[i]=='$'||fmt[i]=='*'||fmt[i]=='.')
			//while (!isalpha(fmt[i]))
			{	
				if (fmt[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=fmt[i];
					i=i+1;
				}
			}
			//number=findNumber(number_array);
			//
			if (fmt[i]=='d')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%d",out_int);
				i=i+1;			//
			}
			else if (fmt[i]=='i')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%i",out_int);
				i=i+1;			//
			}
			else if (fmt[i]=='s')
			{
				out_string=va_arg(argp, char*);
				count=count+strlen(out_string);
				(orig_fprintf)(file,"%s",out_string);
				i=i+1;			//
			}
			else if (fmt[i]=='c')
			{
				out_char=va_arg(argp, int);
				count++;
				(orig_fprintf)(file,"%c",out_char);
				i=i+1;			//
			}
			else if (fmt[i]=='x')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%x",out_hex_int);
				i=i+1;			//
			}
			else if (fmt[i]=='X')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%X",out_hex_int);
				i=i+1;			//
			}
			else if (fmt[i]=='f')
			{
				out_f=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%f",out_f);
				i=i+1;			//
			}
			else if (fmt[i]=='u')
			{
				out_unsigned_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%u",out_unsigned_int);
				i=i+1;			//
			}
			//new
			else if (fmt[i]=='h')
			{
				if (fmt[i+1]=='n')
				{
					out_n=(int *)va_arg(argp,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",fmt[i]);
					i=i+1;
				}
			}
			else if (fmt[i]=='e')
			{
				out_e=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (fmt[i]=='o')
			{
				out_o=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (fmt[i]=='p')
			{
				out_p=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (fmt[i]=='a')
			{
				out_a=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (fmt[i]=='n')
			{
				out_n=(int *)va_arg(argp,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (fmt[i]=='%')
			{
				count++;
				(orig_fprintf)(file,"%c",fmt[i]);
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			(orig_fprintf)(file,"%c",fmt[i]);
			i++;
		}
	}
	va_end(argp);
	return 0;
}

int sprintf (char *str, const char *sformat, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	int len;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	char final_string[65535];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_fprintf=(int (*)(FILE *file,const char *format, ...))dlsym(RTLD_NEXT,"fprintf");
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char *str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	int count=0;
	va_list argp;
	va_start(argp, sformat);

	for (i=0;sformat[i]!='\0';)
	{
		if (sformat[i]=='%')
		{
			//
			i=i+1;
			while (sformat[i]=='0'||sformat[i]=='1'||sformat[i]=='2'||sformat[i]=='3'||sformat[i]=='4'||sformat[i]=='5'||sformat[i]=='6'||sformat[i]=='7'||sformat[i]=='8'||sformat[i]=='9'||sformat[i]=='$'||sformat[i]=='*'||sformat[i]=='.')
			//while (!isalpha(sformat[i]))
			{	
				if (sformat[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=sformat[i];
					i=i+1;
				}
			}
			//number=findNumber(number_array);
			//
			if (sformat[i]=='d')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (sformat[i]=='i')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;
			}
			else if (sformat[i]=='s')
			{
				out_string=va_arg(argp, char*);
				count=count+strlen(out_string);
				strcat(final_string,out_string);
				i=i+1;			//
			}
			else if (sformat[i]=='c')
			{
				out_char=va_arg(argp, int);
				count++;
				len=strlen(final_string);
				final_string[len]=out_char;
				i=i+1;			//
			}
			else if (sformat[i]=='x')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (sformat[i]=='X')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;		
			}
			else if (sformat[i]=='f')
			{
				out_f=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (sformat[i]=='u')
			{
				out_unsigned_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			//new
			else if (sformat[i]=='h')
			{
				if (sformat[i+1]=='n')
				{
					out_n=(int *)va_arg(argp,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",sformat[i]);
					i=i+1;
				}
			}
			else if (sformat[i]=='e')
			{
				out_e=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (sformat[i]=='o')
			{
				out_o=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (sformat[i]=='p')
			{
				out_p=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (sformat[i]=='a')
			{
				out_a=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (sformat[i]=='n')
			{
				out_n=(int *)va_arg(argp,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (sformat[i]=='%')
			{
				count++;
				len=strlen(final_string);
				final_string[len]=sformat[i];
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			len=strlen(final_string);
			final_string[len]=sformat[i];
			i++;
		}
	}
	(orig_sprintf)(str,"%s",final_string);
	va_end(argp);
	return 0;
}

int snprintf(char *snstr, size_t size, const char * snformat, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	int len;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	char final_string[65535];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_fprintf=(int (*)(FILE *file,const char *format, ...))dlsym(RTLD_NEXT,"fprintf");
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char *str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	orig_snprintf=(int (*)(char *str,size_t size,const char *format, ...))dlsym(RTLD_NEXT,"snprintf");
	int count=0;
	va_list argp;
	va_start(argp, snformat);

	for (i=0;snformat[i]!='\0';)
	{
		if (snformat[i]=='%')
		{
			//
			i=i+1;
			while (snformat[i]=='0'||snformat[i]=='1'||snformat[i]=='2'||snformat[i]=='3'||snformat[i]=='4'||snformat[i]=='5'||snformat[i]=='6'||snformat[i]=='7'||snformat[i]=='8'||snformat[i]=='9'||snformat[i]=='$'||snformat[i]=='*'||snformat[i]=='.')
			//while (!isalpha(snformat[i]))
			{	
				if (snformat[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=snformat[i];
					i=i+1;
				}
			}
			//number=findNumber(number_array);
			//
			if (snformat[i]=='d')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (snformat[i]=='i')
			{
				out_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;		
			}
			else if (snformat[i]=='s')
			{
				out_string=va_arg(argp, char*);
				count=count+strlen(out_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (snformat[i]=='c')
			{
				out_char=va_arg(argp, int);
				count++;
				len=strlen(final_string);
				final_string[len]=out_char;
				i=i+1;			//
			}
			else if (snformat[i]=='x')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (snformat[i]=='X')
			{
				out_hex_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;		
			}
			else if (snformat[i]=='f')
			{
				out_f=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (snformat[i]=='u')
			{
				out_unsigned_int=va_arg(argp, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			//new
			else if (snformat[i]=='h')
			{
				if (snformat[i+1]=='n')
				{
					out_n=(int *)va_arg(argp,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",snformat[i]);
					i=i+1;
				}
			}
			else if (snformat[i]=='e')
			{
				out_e=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (snformat[i]=='o')
			{
				out_o=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (snformat[i]=='p')
			{
				out_p=va_arg(argp, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (snformat[i]=='a')
			{
				out_a=va_arg(argp,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (snformat[i]=='n')
			{
				out_n=(int *)va_arg(argp,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (snformat[i]=='%')
			{
				count++;
				len=strlen(final_string);
				final_string[len]=snformat[i];
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			len=strlen(final_string);
			final_string[len]=snformat[i];
			i++;
		}
	}
	(orig_snprintf)(snstr,size,"%s",final_string);
	//(orig_snprintf)(snstr,size,final_string);
	va_end(argp);
	return 0;
}

int vprintf (const char *format, va_list arg)
{
	new_vprintf(format,arg);
	return 0;
}

int vfprintf(FILE *file, const char *format, va_list arg)
{
	new_vfprintf(file, format, arg);
	return 0;
}

int new_vprintf(const char *vformat, va_list varg, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	//char temp;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char * str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	int count=0;
	
	for (i=0;vformat[i]!='\0';)
	{
		if (vformat[i]=='%')
		{
			//
			i=i+1;
			while (vformat[i]=='0'||vformat[i]=='1'||vformat[i]=='2'||vformat[i]=='3'||vformat[i]=='4'||vformat[i]=='5'||vformat[i]=='6'||vformat[i]=='7'||vformat[i]=='8'||vformat[i]=='9'||vformat[i]=='$'||vformat[i]=='*'||vformat[i]=='.')
			//while (!isalpha(vformat[i]))
			{	
				if (vformat[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=vformat[i];
					i=i+1;					
				}
			}
			//number=findNumber(number_array);
			//
			if (vformat[i]=='d')
			{
				out_int=va_arg(varg, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%d",out_int);
				i=i+1;			//
			}
			else if (vformat[i]=='i')
			{
				out_int=va_arg(varg, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%i",out_int);
				i=i+1;			
			}
			else if (vformat[i]=='s')
			{
				out_string=va_arg(varg, char*);
				count=count+strlen(out_string);
				(orig_printf)("%s",out_string);
				i=i+1;			//
			}
			else if (vformat[i]=='c')
			{
				out_char=va_arg(varg, int);
				count++;
				(orig_printf)("%c",out_char);
				i=i+1;			//
			}
			else if (vformat[i]=='x')
			{
				out_hex_int=va_arg(varg, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%x",out_hex_int);
				i=i+1;			//
			}
			else if (vformat[i]=='X')
			{
				out_hex_int=va_arg(varg, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%X",out_hex_int);
				i=i+1;	
			}
			else if (vformat[i]=='f')
			{
				out_f=va_arg(varg,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				(orig_printf)("%f",out_f);
				i=i+1;			//
			}
			else if (vformat[i]=='u')
			{
				out_unsigned_int=va_arg(varg, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				(orig_printf)("%u",out_unsigned_int);
				i=i+1;			//
			}
			//new
			else if (vformat[i]=='h')
			{
				if (vformat[i+1]=='n')
				{
					out_n=(int *)va_arg(varg,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",vformat[i]);
					i=i+1;
				}
			}
			else if (vformat[i]=='e')
			{
				out_e=va_arg(varg,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (vformat[i]=='o')
			{
				out_o=va_arg(varg, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (vformat[i]=='p')
			{
				out_p=va_arg(varg, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (vformat[i]=='a')
			{
				out_a=va_arg(varg,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (vformat[i]=='n')
			{
				out_n=(int *)va_arg(varg,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (vformat[i]=='%')
			{
				count++;
				(orig_printf)("%c",vformat[i]);
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			(orig_printf)("%c",vformat[i]);
			i++;
		}
	}

	return 0;
}

int new_vfprintf(FILE *file, const char *vfformat, va_list vfarg, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_fprintf=(int (*)(FILE *file,const char *format, ...))dlsym(RTLD_NEXT,"fprintf");
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char *str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	int count=0;

	for (i=0;vfformat[i]!='\0';)
	{
		if (vfformat[i]=='%')
		{
			//
			i=i+1;
			while (vfformat[i]=='0'||vfformat[i]=='1'||vfformat[i]=='2'||vfformat[i]=='3'||vfformat[i]=='4'||vfformat[i]=='5'||vfformat[i]=='6'||vfformat[i]=='7'||vfformat[i]=='8'||vfformat[i]=='9'||vfformat[i]=='$'||vfformat[i]=='*'||vfformat[i]=='.')
			//while (!isalpha(vfformat[i]))
			{	
				if (vfformat[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=vfformat[i];
					i=i+1;
				}
			}
			//number=findNumber(number_array);
			//
			if (vfformat[i]=='d')
			{
				out_int=va_arg(vfarg, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%d",out_int);
				i=i+1;			//
			}
			else if (vfformat[i]=='i')
			{
				out_int=va_arg(vfarg, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%i",out_int);
				i=i+1;			//	
			}
			else if (vfformat[i]=='s')
			{
				out_string=va_arg(vfarg, char*);
				count=count+strlen(out_string);
				(orig_fprintf)(file,"%s",out_string);
				i=i+1;			//
			}
			else if (vfformat[i]=='c')
			{
				out_char=va_arg(vfarg, int);
				count++;
				(orig_fprintf)(file,"%c",out_char);
				i=i+1;			//
			}
			else if (vfformat[i]=='x')
			{
				out_hex_int=va_arg(vfarg, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%x",out_hex_int);
				i=i+1;			//
			}
			else if (vfformat[i]=='X')
			{
				out_hex_int=va_arg(vfarg, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%X",out_hex_int);
				i=i+1;	
			}
			else if (vfformat[i]=='f')
			{
				out_f=va_arg(vfarg,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%f",out_f);
				i=i+1;			//
			}
			else if (vfformat[i]=='u')
			{
				out_unsigned_int=va_arg(vfarg, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				(orig_fprintf)(file,"%u",out_unsigned_int);
				i=i+1;			//
			}
			//new
			else if (vfformat[i]=='h')
			{
				if (vfformat[i+1]=='n')
				{
					out_n=(int *)va_arg(vfarg,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",vfformat[i]);
					i=i+1;
				}
			}
			else if (vfformat[i]=='e')
			{
				out_e=va_arg(vfarg,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (vfformat[i]=='o')
			{
				out_o=va_arg(vfarg, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (vfformat[i]=='p')
			{
				out_p=va_arg(vfarg, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (vfformat[i]=='a')
			{
				out_a=va_arg(vfarg,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (vfformat[i]=='n')
			{
				out_n=(int *)va_arg(vfarg,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (vfformat[i]=='%')
			{
				count++;
				(orig_fprintf)(file,"%c",vfformat[i]);
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			(orig_fprintf)(file,"%c",vfformat[i]);
			i++;
		}
	}
	return 0;
}

int vsprintf(char *str, const char * format, va_list arg)
{
	new_vsprintf(str,format,arg);
	return 0;
}

int new_vsprintf(char *str, const char *vsformat, va_list vsarg, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	int len;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	char final_string[65535];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_fprintf=(int (*)(FILE *file,const char *format, ...))dlsym(RTLD_NEXT,"fprintf");
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char *str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	int count=0;

	for (i=0;vsformat[i]!='\0';)
	{
		if (vsformat[i]=='%')
		{
			//
			i=i+1;
			while (vsformat[i]=='0'||vsformat[i]=='1'||vsformat[i]=='2'||vsformat[i]=='3'||vsformat[i]=='4'||vsformat[i]=='5'||vsformat[i]=='6'||vsformat[i]=='7'||vsformat[i]=='8'||vsformat[i]=='9'||vsformat[i]=='$'||vsformat[i]=='*'||vsformat[i]=='.')
			//while (!isalpha(vsformat[i]))
			{	
				if (vsformat[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=vsformat[i];
					i=i+1;				
				}
			}
			//number=findNumber(number_array);
			//
			if (vsformat[i]=='d')
			{
				out_int=va_arg(vsarg, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsformat[i]=='i')
			{
				out_int=va_arg(vsarg, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsformat[i]=='s')
			{
				out_string=va_arg(vsarg, char*);
				count=count+strlen(out_string);
				strcat(final_string,out_string);
				i=i+1;			//
			}
			else if (vsformat[i]=='c')
			{
				out_char=va_arg(vsarg, int);
				count++;
				len=strlen(final_string);
				final_string[len]=out_char;
				i=i+1;			//
			}
			else if (vsformat[i]=='x')
			{
				out_hex_int=va_arg(vsarg, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsformat[i]=='X')
			{
				out_hex_int=va_arg(vsarg, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;
			}
			else if (vsformat[i]=='f')
			{
				out_f=va_arg(vsarg,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsformat[i]=='u')
			{
				out_unsigned_int=va_arg(vsarg, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			//new
			else if (vsformat[i]=='h')
			{
				if (vsformat[i+1]=='n')
				{
					out_n=(int *)va_arg(vsarg,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",vsformat[i]);
					i=i+1;
				}
			}
			else if (vsformat[i]=='e')
			{
				out_e=va_arg(vsarg,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (vsformat[i]=='o')
			{
				out_o=va_arg(vsarg, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (vsformat[i]=='p')
			{
				out_p=va_arg(vsarg, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (vsformat[i]=='a')
			{
				out_a=va_arg(vsarg,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (vsformat[i]=='n')
			{
				out_n=(int *)va_arg(vsarg,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (vsformat[i]=='%')
			{
				count++;
				len=strlen(final_string);
				final_string[len]=vsformat[i];
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			len=strlen(final_string);
			final_string[len]=vsformat[i];
			i++;
		}
	}
	(orig_sprintf)(str,"%s",final_string);

	return 0;
}

int vsnprintf(char *snstr, size_t size, const char *snformat, va_list arg)
{
	new_vsnprintf(snstr, size, snformat, arg);
	return 0;
}

int new_vsnprintf(char *snstr, size_t size, const char *vsnformat, va_list vsnfarg, ...)
{
	int i=0;
	int out_int;
	int *out_n;
	int len;
	unsigned int out_hex_int;
	unsigned int out_unsigned_int;
	char out_char=NULL;
	char *out_string=NULL;
	char int_to_string[20];
	char final_string[65535];
	double out_f;
	double out_e;
	//
	double out_a;
	unsigned int out_o;
	unsigned int out_p;
	int k=0;
	//int circle=0;
	//int number;
	char number_array[6];
	//int loop;
	//
	orig_fprintf=(int (*)(FILE *file,const char *format, ...))dlsym(RTLD_NEXT,"fprintf");
	orig_printf=(int (*)(const char *format, ...))dlsym(RTLD_NEXT,"printf");
	orig_sprintf=(int (*)(char *str,const char *format, ...))dlsym(RTLD_NEXT,"sprintf");
	orig_snprintf=(int (*)(char *str,size_t size,const char *format, ...))dlsym(RTLD_NEXT,"snprintf");
	int count=0;

	for (i=0;vsnformat[i]!='\0';)
	{
		if (vsnformat[i]=='%')
		{
			//
			i=i+1;
			while (vsnformat[i]=='0'||vsnformat[i]=='1'||vsnformat[i]=='2'||vsnformat[i]=='3'||vsnformat[i]=='4'||vsnformat[i]=='5'||vsnformat[i]=='6'||vsnformat[i]=='7'||vsnformat[i]=='8'||vsnformat[i]=='9'||vsnformat[i]=='$'||vsnformat[i]=='*'||vsnformat[i]=='.')
			//while (!isalpha(vsnformat[i]))
			{	
				if (vsnformat[i]=='%')
				{
					break;
				}
				else
				{
					number_array[k++]=vsnformat[i];
					i=i+1;					
				}
			}
			//number=findNumber(number_array);
			//
			if (vsnformat[i]=='d')
			{
				out_int=va_arg(vsnfarg, int);
				(orig_sprintf)(int_to_string,"%d",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsnformat[i]=='i')
			{
				out_int=va_arg(vsnfarg, int);
				(orig_sprintf)(int_to_string,"%i",out_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsnformat[i]=='s')
			{
				out_string=va_arg(vsnfarg, char*);
				count=count+strlen(out_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsnformat[i]=='c')
			{
				out_char=va_arg(vsnfarg, int);
				count++;
				len=strlen(final_string);
				final_string[len]=out_char;
				i=i+1;			//
			}
			else if (vsnformat[i]=='x')
			{
				out_hex_int=va_arg(vsnfarg, int);
				(orig_sprintf)(int_to_string,"%x",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsnformat[i]=='X')
			{
				out_hex_int=va_arg(vsnfarg, int);
				(orig_sprintf)(int_to_string,"%X",out_hex_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsnformat[i]=='f')
			{
				out_f=va_arg(vsnfarg,double);
				(orig_sprintf)(int_to_string,"%f",out_f);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			else if (vsnformat[i]=='u')
			{
				out_unsigned_int=va_arg(vsnfarg, int);
				(orig_sprintf)(int_to_string,"%u",out_unsigned_int);
				count=count+strlen(int_to_string);
				strcat(final_string,int_to_string);
				i=i+1;			//
			}
			//new
			else if (vsnformat[i]=='h')
			{
				if (vsnformat[i+1]=='n')
				{
					out_n=(int *)va_arg(vsnfarg,int*);
					//*out_n=count;
					i=i+2;
				}
				else
				{
					count++;
					(orig_printf)("%c",vsnformat[i]);
					i=i+1;
				}
			}
			else if (vsnformat[i]=='e')
			{
				out_e=va_arg(vsnfarg,double);
				(orig_sprintf)(int_to_string,"%e",out_e);
				count=count+strlen(int_to_string);
				(orig_printf)("%e",out_e);
				i=i+1;	
			}
			else if (vsnformat[i]=='o')
			{
				out_o=va_arg(vsnfarg, unsigned int);
				(orig_sprintf)(int_to_string,"%o",out_o);
				count=count+strlen(int_to_string);
				(orig_printf)("%o",out_o);
				i=i+1;	
			}
			else if (vsnformat[i]=='p')
			{
				out_p=va_arg(vsnfarg, unsigned int);
				(orig_sprintf)(int_to_string,"%p",out_p);
				count=count+strlen(int_to_string);
				(orig_printf)("%p",out_p);
				i=i+1;
			}
			else if (vsnformat[i]=='a')
			{
				out_a=va_arg(vsnfarg,double);
				(orig_sprintf)(int_to_string,"%a",out_a);
				count=count+strlen(int_to_string);
				(orig_printf)("%a",out_a);
				i=i+1;		
			}
			//new
			else if (vsnformat[i]=='n')
			{
				out_n=(int *)va_arg(vsnfarg,int*);
				//*out_n=count;					//uncomment this for test1 and test2
				i=i+1;
			}
			else if (vsnformat[i]=='%')
			{
				count++;
				len=strlen(final_string);
				final_string[len]=vsnformat[i];
				i=i+1;
			}
			else
			{
				count++;
				i++;
			}
		}
		else
		{
			count++;
			len=strlen(final_string);
			final_string[len]=vsnformat[i];
			i++;
		}
	}
	(orig_snprintf)(snstr,size,"%s",final_string);
	//(orig_snprintf)(snstr,size,final_string);

	return 0;
}

int findNumber(char *num_array)
{
	//int length=strlen(num_array);
	int number;
	sscanf(num_array,"%d",&number);

	return number;
}