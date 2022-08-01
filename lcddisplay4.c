#include <wiringPi.h>
#include <lcd.h>
//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D4  23               //Data pin 4
#define LCD_D5  22               //Data pin 5
#define LCD_D6  21               //Data pin 6
#define LCD_D7  14               //Data pin 7

int main()
{
    int lcd;
    wiringPiSetup();
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
//changing Position of the text
  /*  lcdPosition(lcd, 0, 0);
    lcdPuts(lcd, "Hello, world!");*/
// clear the screen
/*   lcdPuts(lcd, "Welcome Acufore");
    sleep(2);
    lcdClear(lcd);

    lcdPuts(lcd, "clear the screen");
    sleep(2);
    lcdClear(lcd);*/
//blinking the text
/*    while(1)
    {
        lcdPosition(lcd, 0, 0);
        lcdPuts(lcd, "Hello, world!");
        sleep(2);
        lcdClear(lcd);
        sleep(2);
    }*/
//Cursor On , off and blink
    lcdCursor(lcd, 0); //Cursor OFF
    lcdCursor(lcd, 1); //Cursor ON, underline, not blinking
    //lcdCursorBlink(lcd, 1); //Cursor ON, block, blinking
    //Use both lines below to get a blinking underline/block cursor
    //lcdCursor(lcd, 1);
    lcdCursorBlink(lcd, 1);
    lcdPuts(lcd, "Hello, world!");
}
