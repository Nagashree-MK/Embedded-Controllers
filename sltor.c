//includes
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>

//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D4  23               //Data pin 4
 #define LCD_D5  22               //Data pin 5
#define LCD_D6  21               //Data pin 6
#define LCD_D7  14               //Data pin 7
//global variables
char message[] = "Hello! world";
int count = 0;
int j = 0;
int lcd;
//main
int main()
{
	char displayText[]= "                ";
	int count,index, msgLen,temp,i,lenDisplayText,j=1;
	char finalText[16];

        wiringPiSetup();
        lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
	msgLen=strlen(message);
	while(1)
	{
//		delay(200);
		for(count=1;count<=(msgLen+16);count++)// Shifting Loop
		{
			strcpy(displayText,"                ");
			temp=count;

			lcdPosition(lcd, 0,0);
			if(count <= msgLen)      //count is <=msglen
			{
				for(index=0;index<count;index++)//appending character by charater to displaytext
				{
					displayText[index]=message[msgLen-temp];
					temp--;
				}

			}
			else if((count>msgLen)&&(count<=16))//if count is > msglen and also <=16 it should change position 
			{
				lcdClear(lcd);
				lcdPosition(lcd,count-msgLen, 0);
				strcpy(displayText, message);
			}
			else//for removing the last character bcs of scrolling 
			{
			//	lendisplaytext=strlen(displaytext);
			//	strcpy(finaltext, "            ");
				lcdClear(lcd);
				memset(finalText, '\0', sizeof(finalText));
				if(j==msgLen)//this condition is required bcs for 1st time it will scroll full.
						// 2nd time it will end till else if.
						// else is not performed because  of j++ for the second time 
						// j will be > than msglen which results in negative index
						//then it will show error called Segmentation fault
				{
					j=1;
				}
				else
				{
					strncpy(finalText,message,msgLen-j);
					lcdPosition(lcd, count-msgLen, 0);
					j++;
					strcpy(displayText,finalText);
				}
			}

			//display the final text
			lcdPrintf(lcd, "%s", displayText);
			delay(300);
		}
	}
}
 
