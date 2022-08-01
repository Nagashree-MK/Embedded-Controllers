#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

#define RED 2
#define SWITCH 0

#define ON HIGH
#define OFF LOW

#define close 0
#define open 1

void main()
{
 int toggle, prevSwiCon, curSwiCon, count, i, timeInMs;
 if(wiringPiSetup()==-1)
 {
  printf("failed to setup wiringpi\n");
 }
 pinMode(RED, OUTPUT);
 pinMode(SWITCH, INPUT);
 digitalWrite(SWITCH, OFF);
 digitalWrite(RED, OFF); 
}
