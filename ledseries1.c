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
#define GREEN 4
#define RED 5


//main
int main()
{
  int i;
  int arr[5]={14,13,12,4,5};

  if(wiringPiSetup()==-1)
  {
     printf("Failed to setup Wiring Pi\n");
     return 1;
  }
  //pinmode is  output 
  pinMode(WHITE, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  //initially all LEDS should be off
  digitalWrite(WHITE, OFF);
  digitalWrite(ORANGE, OFF);
  digitalWrite(BLUE, OFF);
  digitalWrite(GREEN, OFF);
  digitalWrite(RED, OFF);
   //looping
 /* while(1)
  {
   	digitalWrite(BLUE, ON);
	digitalWrite(WHITE, OFF);
	digitalWrite(ORANGE, OFF);
	digitalWrite(GREEN, OFF);
	digitalWrite(RED, OFF);
	delay(1000);
	digitalWrite(WHITE, ON);
	digitalWrite(ORANGE, OFF);
	digitalWrite(BLUE, OFF);
	digitalWrite(GREEN, OFF);
	 digitalWrite(RED, OFF);
	delay(1000);
	digitalWrite(ORANGE, ON);
	digitalWrite(BLUE, OFF);
	digitalWrite(WHITE, OFF);
	digitalWrite(GREEN, OFF);
	  digitalWrite(RED, OFF);
	delay(1000);
	digitalWrite(GREEN, ON);
        digitalWrite(BLUE, OFF);
        digitalWrite(WHITE, OFF);
        digitalWrite(ORANGE, OFF);
          digitalWrite(RED, OFF);
        delay(1000);
	digitalWrite(RED, ON);
        digitalWrite(BLUE, OFF);
        digitalWrite(WHITE, OFF);
        digitalWrite(GREEN, OFF);
          digitalWrite(ORANGE, OFF);
        delay(1000);
       digitalWrite(GREEN, ON);
        digitalWrite(BLUE, OFF);
        digitalWrite(WHITE, OFF);
        digitalWrite(ORANGE, OFF);
          digitalWrite(RED, OFF);
        delay(1000);
	digitalWrite(ORANGE, ON);
        digitalWrite(BLUE, OFF);
        digitalWrite(WHITE, OFF);
        digitalWrite(GREEN, OFF);
          digitalWrite(RED, OFF);
        delay(1000);
	digitalWrite(WHITE, ON);
        digitalWrite(ORANGE, OFF);
        digitalWrite(BLUE, OFF);
        digitalWrite(GREEN, OFF);
         digitalWrite(RED, OFF);
        delay(1000);
  }*/
  while(1)
  {
 	for(i=0;i<5;i++)
	{
		digitalWrite(arr[i], ON);
		delay(500);
		digitalWrite(arr[i], OFF);
	}
	for(i=3;i>=1;i--)
	{
		digitalWrite(arr[i], ON);
		delay(500);
		digitalWrite(arr[i], OFF);
	}
  }
  return 0;
}
