#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

#define RED 2
#define SWITCH 0


#define ON HIGH
#define OFF LOW

#define close 1
#define open 0

void main()
{
 if(wiringPiSetup()==-1)
 {
  printf("failed to setup wiringpi\n");
 }
 pinMode(RED, OUTPUT);
 pinMode(SWITCH, INPUT);
 digitalWrite(SWITCH, OFF);
 digitalWrite(RED, OFF);
 while(1)
 {
  if(digitalRead(SWITCH)==close)
  digitalWrite(RED, ON);
  else if(digitalRead(SWITCH)==open)
  digitalWrite(RED, OFF);
 }
}
