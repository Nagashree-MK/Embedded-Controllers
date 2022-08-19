if ((uart0 = serialOpen ("/dev/ttyS0", 9600)) < 0)      /* open serial port */
  {
   printf ( "Unable to open serial device\n") ;
    return 1 ;
  }#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(){
	int uart0;
	printf("Beginning...\n");
	if ((uart0 = serialOpen ("/dev/ttyS0", 9600)) < 0)	/* open serial port */
  {
   printf ( "Unable to open serial device\n") ;
    return 1 ;
  }
//	uart0 = serialOpen("\\dev\\ttyS0", 9600);
	serialPuts( uart0, "Yureeekaaa...");
	serialPrintf(uart0, "Check123");
	printf("Serial Flush...\n");
	serialFlush(uart0);
	printf("Serial Close...\n");
	serialClose(uart0);
	return 0;
}
