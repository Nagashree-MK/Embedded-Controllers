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

void scrollText(void);
char message[] = "Hello!";
int count = 0;
int j = 0;
int lcd;

int main()
{
	char scrollpadding[]= "                ";
	char text[16];
	int count=0;
	int msglen, i;
        wiringPiSetup();
        lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
	msglen=strlen(message);
        while(1)
	{
		count++;
		for(i=msglen-1; i>=0; i--)
		{
			scrollpadding[i+1]=message[i];
			scrollpadding[i]=NULL;
		}
		lcdPosition(lcd, 0, 0);
		strcpy(text, scrollpadding);
		lcdPrintf(lcd, "%s",text);
		//delay(200);
		for(i=0;i<msglen-1;i++)
		{
			if((count+msglen-i)==16)
			{
				scrollpadding[i]=message[msglen-1-i];
				lcdPrintf(lcd, "%s", scrollpadding);
			}
		}
	}
	return 0;
}
