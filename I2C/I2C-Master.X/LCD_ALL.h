/* 
 * File: LCD_ALL.h
 * Librería para controlar un LCD en modo de 8 bits.
 */

#ifndef LCD_ALL_H
#define LCD_ALL_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#include <xc.h>

// Definiciones de pines de control y datos del LCD
#define RS PORTEbits.RE0
#define EN PORTEbits.RE1
#define D0 PORTAbits.RA0
#define D1 PORTAbits.RA1
#define D2 PORTAbits.RA2
#define D3 PORTAbits.RA3
#define D4 PORTAbits.RA4
#define D5 PORTAbits.RA5
#define D6 PORTAbits.RA6 
#define D7 PORTAbits.RA7

void LcdALL_Port(char a);
void LcdALL_Cmd(char a);
void LcdALL_Clear(void);
void LcdALL_Set_Cursor(char a, char b);
void LcdALL_Init(void);
void LcdALL_Write_Char(char a);
void LcdALL_Write_String(char *a);
void LcdALL_Shift_Right(void);
void LcdALL_Shift_Left(void);
char LcdALL_set_value(int byte_value);
float LcdALL_map(float valor, float rango_min, float rango_max, float nuevo_min, float nuevo_max);

#endif /* LCD_ALL_H */