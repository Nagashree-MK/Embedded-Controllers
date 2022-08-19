#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>



int main()
{
int uart0_filestream;
int bytecount;
char str[25];
strcpy(str,"59.37");
strcat(str, "/");
strcat(str,"39.93");
uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY);
bytecount = read(uart0_filestream, str, 20);
if(bytecount>0)
   {
   str[bytecount]='\0';
   }
else
   {
   // Something bad happened?
   }
}
