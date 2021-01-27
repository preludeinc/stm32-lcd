/*
 *  lcd.h
 *  Code ported from the lcd.h file created for the PIC Microcontroller
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

/* LCD Functions */

/* enable or disable LCD back light */
extern void lcdBl(unsigned char c);

/* writes a byte to the LCD in 4 bit mode */
extern void lcdWrite(unsigned char b);

/* initializes the LCD */
extern void lcdInit(void);

/* clears and homes the LCD */
extern void lcdClear(void);

/* writes a string of characters to the LCD */
extern void lcdPuts(char * s);

/* writes a single character to the LCD */
extern void lcdPutch(unsigned char);

/* go to specified position */
extern void lcdGoto(unsigned char pos);

extern void lcdCmd(unsigned char c);

#endif /* INC_LCD_H_ */
