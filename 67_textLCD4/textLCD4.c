#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

int main(void)
{
   unsigned char i;

   //Initialize LCD module
   LCDInit(LS_BLINK|LS_ULINE);

   //Clear the screen
   LCDClear();

   //Simple string printing
   LCDWriteString("Test LCD ");

   //A string on line 2
   LCDWriteStringXY(0,1,"Loading ");

   //Print some numbers
   for (i=0;i<99;i+=1)
   {
      LCDWriteIntXY(9,1,i,3);
      LCDWriteStringXY(12,1,"%");
      _delay_ms(1);
   }

   //Clear the screen
   LCDClear();

   //Some more text

   LCDWriteString("Completed");
   LCDWriteStringXY(0,1,"By SC Kim");    // <--- Write ur NAME HERE !!!!!!!!!!!

   //Wait
   for(i=0;i<100;i++) _delay_ms(1000);

   //Some More ......
   LCDClear();
   LCDWriteString("    eXtreme");
   LCDWriteStringXY(0,1,"  Electronics");

}
