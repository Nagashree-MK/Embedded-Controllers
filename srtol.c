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
char message[] ="hi hello how are you";
int count = 0;
int lcd;
//main
int main()
{
	char displayText[]= "                ";
	int count,index, msgLen,temp,i,lenDisplayText,j=1,k=1,idx;
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
					displayText[15-index]=message[temp-1];
					temp--;
				}

			}
			else if((count>msgLen)&&(count<=16))//if count is > msglen and also <=16 it should change position 
			{
				lcdClear(lcd);
				lcdPosition(lcd,16-count, 0);
				strcpy(displayText, message);
			}

/*			else if(msgLen>16)
			{
				lcdClear(lcd);
				strcpy(finalText, "               ");
				for(idx=0;idx<msgLen-k;idx++)
				{
					finalText[idx]=message[idx+k];
				}
				k++;
				strcpy(displayText,finalText);
*/			}
			else//for removing the last character bcs of scrolling 
			{
//				lenDisplayText=strlen(displayText);
			//	strcpy(finaltext, "            ");
				lcdClear(lcd);
			//	memset(finalText, '\0', sizeof(finalText));
			//	memset(tempText, '\0', sizeof(tempText));
			/*	if(j==msgLen)//this condition is required bcs for 1st time it will scroll full.
						// 2nd time it will end till else if.
						// else is not performed because  of j++ for the second time 
						// j will be > than msglen which results in negative index
						//then it will show error called Segmentation fault
				{
					j=1;
				}
				else
				{*/
			//		strrev(displayText);
			//		strcpy(tempText,displayText);
			//		lenTempText=strlen(tempText);
			//		strncpy(finalText,tempText,lenTempText-1);
			//		lcdPosition(lcd, 0, 0);
			//		strrev(finalText);
			//		strcpy(displayText,finalText);
			//	}
				if(j==msgLen)
				{
					j=1;
				}
				else
				{
					strcpy(finalText, "               ");
					for(idx=0;idx<msgLen-j;idx++)
					{
						finalText[idx]=message[idx+j];
						//printf("index=%d, character=%c\n", idx, finalText[idx]);
						/*if(idx==lenDisplayText-j)
						{
							finalText[idx]='\0';
						}*/
					}
				
					strcpy(displayText,finalText);
					lcdPosition(lcd,0,0);
					j++;
				}
			}//end of else

			//display the final text
			lcdPrintf(lcd, "%s", displayText);
			delay(300);
		}//end of for
//	delay(1000);
	}// end of  while(1)
}
