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
	for(i=0;i<3;i++)
	{
		digitalWrite(WHITE, ON);
		delay(100);
		digitalWrite(WHITE, OFF);
		delay(100);
	}
	delay(800);
	for(i=0;i<3;i++)
	{
		digitalWrite(ORANGE, ON);
		delay(100);
		digitalWrite(ORANGE, OFF);
		delay(100);
	}
	delay(800);
	for(i=0;i<3;i++)
	{
		digitalWrite(BLUE, ON);
		delay(100);
		digitalWrite(BLUE, OFF);
		delay(100);
	}
	delay(800);
  }
  return 0;
}

