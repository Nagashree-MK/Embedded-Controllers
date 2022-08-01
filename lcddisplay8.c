//includes
#include <wiringPi.h>
#include <lcd.h>

//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D0  29               //Data pin D0
#define LCD_D1  28               //Data pin D1
#define LCD_D2  27               //Data pin D2
#define LCD_D3  26               //Data pin D3
#define LCD_D4  23               //Data pin D4
#define LCD_D5  22               //Data pin D5
#define LCD_D6  21               //Data pin D6
#define LCD_D7  14               //Data pin D7
//main 
int main()
{
    int lcd, i;
    wiringPiSetup();
    lcd = lcdInit (2, 16, 8, LCD_RS, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
//changing position
/*  lcdPosition(lcd, 0, 0); //changing position to 0th row and 0th column
   lcdPosition(lcd, 0,1);  
    lcdPosition(lcd, 5, 0);
    lcdPuts(lcd,"Welcome");
    lcdPosition(lcd, 5, 1);
    lcdPuts(lcd,"Acufore");
    sleep(3);
    lcdClear(lcd);
    lcdPuts(lcd,"Electronics Team");*/
//shifting the position from left to right 
/*	for(i=0;i<15;i++)
	{
		lcdPosition(lcd, i, 0);
		lcdPuts(lcd,"Welcome Acufore");
		sleep(2);
		lcdClear(lcd);
	}
	lcdPuts(lcd,"Welcome Acufore");*/
// blinking the contents
/*	while(1)
	{
        	lcdPosition(lcd, 0, 0);
	        lcdPuts(lcd, "Hello, world!");
	        sleep(2);
	        lcdClear(lcd);
	        sleep(2);
        }*/
//cursor on and  off
	//lcdCursor(lcd, 0); //Cursor OFF
   
    lcdCursor(lcd, 1); //Cursor ON, underline, not blinking
    //lcdCursorBlink(lcd, 1); //Cursor ON, block, blinking    
    
    //Use both lines below to get a blinking underline/block cursor 
    //lcdCursor(lcd, 1);
    //lcdCursorBlink(lcd, 1);
//	lcdCursorBlink(lcd, 1);
    lcdPuts(lcd, "Hello, world!");

}
