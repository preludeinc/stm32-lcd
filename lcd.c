/*
 * lcd.c
 * Code ported from the lcd.c file created for the PIC Microcontroller.
 * 
 */

#include "main.h"
#include "lcd.h"

#define nop HAL_Delay(1)

#define LCD_STROBE HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET); \
		nop; \
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET); \
		nop

   /* writes a byte to the LCD in 4 bit mode */
   void lcdWrite(unsigned char b)
   {
	GPIOE -> ODR = (GPIOE -> ODR & 0xFFF) | (b & 0xF0) << 8;            // sends the Most-Significant Nibble
        LCD_STROBE;
        GPIOE -> ODR = (GPIOE -> ODR & 0xFFF) | (b & 0x0F) << 12;           // sends the Least-Significant Nibble
        LCD_STROBE;
        HAL_Delay(1);
   }

   /* initializes the LCD */
    void lcdInit(void)
    {
    	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);    // LCD enable
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);    // instruction mode (register select)
        HAL_Delay(50);                            			    // power on delay (must be larger than 40 ms)

        GPIOE -> ODR = (GPIOE -> ODR & 0x0FFF) | (3 << 12);                 // clears the upper nibble, then a 3 is shifted into it
        LCD_STROBE;                                 	                    // passes information to the LCD
        HAL_Delay(5);
        LCD_STROBE;
        HAL_Delay(5);
        LCD_STROBE;
        HAL_Delay(5);

        GPIOE -> ODR = (GPIOE -> ODR & 0x0FFF) | (2 << 12);                 // clears the upper nibble, then a 2 is shifted into it
        LCD_STROBE;
        HAL_Delay(5);
        lcdWrite(0x28);                             		            // 4 bit mode - 1/16th duty cycle, 5x8 font
        lcdWrite(0x0F);                             		            // display on, cursor off, blink off
        lcdWrite(0x01);				                            // clear display, reset cursor
        HAL_Delay(2);
        lcdWrite(0x06);                             		            // entry mode set, increment mode, shift off
        lcdWrite(0x01);                             		            // clear display, reset cursor
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);      // data input mode
    }

    /* clears and homes the LCD */
    void lcdClear(void)
    {
    	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);     // instruction mode
        lcdWrite(0x01);                                                      // clears LCD
        HAL_Delay(2);
        lcdWrite(0x02);                                                      // homes LCD
    }
      /* writes a string of characters to the LCD */
    void lcdPuts(char * s)
    {
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);       // data input mode
        while(*s !=0)                                                        // while s is not zero, execute the below code
       {
        	lcdWrite(*s);
        	s++;
       }
    }

    /* write a single character to the LCD */
    void lcdPutch(unsigned char c)
    {

        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);        // data input mode
        lcdWrite(c);                                			      // passing lcdWrite an unsigned char
    }

    /* go to specified position */
    void lcdGoto(unsigned char pos)
    {
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);      // instruction input
        lcdWrite(0x80 + pos);                       			      // 80 = goto command
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);        // data input mode
    }

    /* LCD back light function */
    void lcdBl(unsigned char status)
    {

        if (status)
        	 HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);     // turns the black-light on
        else
        	 HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);   // turns the black-light off
    }

    /* command provided to the LCD */
    void lcdCmd(unsigned char c)
    {

    	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);           // instruction input
        lcdWrite(c);                                			           // sends a command to LCD

    }
