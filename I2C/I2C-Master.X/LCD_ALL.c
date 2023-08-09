/* 
 * File: LCD_ALL.c
 * Librería para controlar un LCD en modo de 8 bits.
 */

#include "LCD_ALL.h"
#include <xc.h>

void LcdALL_Port(char a) {
    // Configurar los pines D0 a D7 como salidas
    TRISA &= 0x00; // Configurar RB0 a RB7 como salidas
    //PORTE &= 0xFC; // Limpiar RE0 y RE1

    // Asignar los bits de datos (D0 a D7) a los pines correspondientes
    D0 = (a & 1);
    D1 = (a & 2) >> 1;
    D2 = (a & 4) >> 2;
    D3 = (a & 8) >> 3;
    D4 = (a & 16) >> 4;
    D5 = (a & 32) >> 5;
    D6 = (a & 64) >> 6;
    D7 = (a & 128) >> 7;
}

void LcdALL_Cmd(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    LcdALL_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void LcdALL_Clear(void) {
    LcdALL_Cmd(0x01);
    __delay_ms(2);
}

void LcdALL_Set_Cursor(char a, char b) {
    char temp;
    if (a == 1) {
        temp = 0x80 + b - 1;
        LcdALL_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        LcdALL_Cmd(temp);
    }
}

void LcdALL_Init(void) {
    LcdALL_Port(0x00);
    __delay_ms(20);
    LcdALL_Cmd(0x30); // Configuracion 8 bits
    __delay_ms(5);
    LcdALL_Cmd(0x30);
    __delay_us(100);
    ////////////////////////////////
    LcdALL_Cmd(0x38);
    LcdALL_Cmd(0x0C); // Configurar el display encendido, sin cursor parpadeante y sin visualización de posición del cursor
    LcdALL_Cmd(0x01); // Limpiar la pantalla
    LcdALL_Cmd(0x06); // Configurar el desplazamiento del cursor hacia la derecha
}

void LcdALL_Write_Char(char a) {
    RS = 1; // => RS = 1
    LcdALL_Port(a);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void LcdALL_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        LcdALL_Write_Char(a[i]);
}

void LcdALL_Shift_Right(void) {
    LcdALL_Cmd(0x01);
    LcdALL_Cmd(0x0C);
}

void LcdALL_Shift_Left(void) {
    LcdALL_Cmd(0x01);
    LcdALL_Cmd(0x08);
}

char LcdALL_set_value(int byte_value){
    int centenas = (byte_value / 100 + 48);       // Calcular las centenas 
    int decenas = ((byte_value%100)/10)+48;    // Calcular las decenas 
    int unidades = (byte_value%10)+48;         // Calcular las unidades
    LcdALL_Write_Char(centenas);
    LcdALL_Write_Char(decenas);
    LcdALL_Write_Char(unidades);
}

float LcdALL_map(float valor, float rango_min, float rango_max, float nuevo_min, float nuevo_max){
    float nuevo_valor = nuevo_min + (valor - rango_min)*(nuevo_max - nuevo_min)/(rango_max - rango_min);
    return nuevo_valor;
}
