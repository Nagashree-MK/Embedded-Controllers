//includes
#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

//macros
#define ON HIGH
#define OFF LOW

#define WHITE 13
#define ORANGE 12
#define BLUE 14


//main
int main()
{
  int i;

  if(wiringPiSetup()==-1)
  {
     printf("Failed to setup Wiring Pi\n");
     return 1;
  }
  //pinmode is  output 
  pinMode(WHITE, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(BLUE, OUTPUT);
  //initially all LEDS should be off
  digitalWrite(WHITE, OFF);
  digitalWrite(ORANGE, OFF);
  digitalWrite(BLUE, OFF);
   //looping
   while(1)
  {
	digitalWrite(BLUE, ON);
 	digitalWrite(ORANGE, ON);
	digitalWrite(WHITE, OFF);
	delay(800);
	digitalWrite(WHITE, ON);
	digitalWrite(BLUE, OFF);
	digitalWrite(ORANGE, OFF);
	delay(800);
  }
  return 0;
}
