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
 int toggle, prevSwiCon, curSwiCon;
 if(wiringPiSetup()==-1)
 {
  printf("failed to setup wiringpi\n");
 }
 pinMode(RED, OUTPUT);
 pinMode(SWITCH, INPUT);
 digitalWrite(SWITCH, OFF);
 digitalWrite(RED, OFF);
 toggle=0;
 prevSwiCon=digitalRead(SWITCH);
 while(1)
 {
  curSwiCon=digitalRead(SWITCH);
  if((prevSwiCon==close)&&(curSwiCon==open))
  {
    toggle=~toggle;
    if(toggle==0)
    digitalWrite(RED, OFF);
   else
   digitalWrite(RED, ON);
  }
  prevSwiCon=curSwiCon;
 }
}
