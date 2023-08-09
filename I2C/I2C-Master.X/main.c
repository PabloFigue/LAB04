/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Master
 * Created on 17 de febrero de 2020, 10:32 AM
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include "INTERRUPT_Library.h"
#include "LCD_ALL.h"
#include "REAL_CLOCK.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
int ADC;
int8_t estado = 0;
int8_t day, mth, year, dow, hr, min, sec;
char buffer[20];

const char letra[8] = {0x0E, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00};


void __interrupt() isr(void){
     
    if (INTCONbits.RBIF){//Interrupción del PORTB
        if (PORTBbits.RB0 == 0) {
            estado++;
            while (PORTBbits.RB0 == 0) {    //While antirebote
                ;
            }
        }
        INTCONbits.RBIF = 0; 

    }
    return;
    
}
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    LcdALL_Init();    //Inicializar la LCD
    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(PORTD);
        I2C_Master_Stop();
        __delay_ms(200);
       
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        ADC = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        //LcdALL_Clear();
        PORTD++;   
        switch(estado)
        {
            case 0:
                DS3231_Get_Date((uint8_t)&day, (uint8_t)&mth, (uint8_t)&year, (uint8_t)&dow);
                DS3231_Get_Time((uint8_t)&hr, (uint8_t)&min, (uint8_t)&sec);
                //LcdALL_Clear();
                sprintf(buffer, "S1:   %02u/%02u/20%02u", day, mth, year);
                LcdALL_Set_Cursor(1,1);
                LcdALL_Write_String(buffer);
                sprintf(buffer, "%03u    %02u:%02u:%02u",ADC, hr, min, sec);
                LcdALL_Set_Cursor(2,1);
                LcdALL_Write_String(buffer);
                __delay_ms(200);
                break;
                
            case 1:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                sprintf(buffer, "Dia: %02u", day);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    day++;
                    if(day > 31){
                        day = 31;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    day--;
                    if(day < 1){
                        day = 1;
                    }
                }
                break;
                
            case 2:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                sprintf(buffer, "Mes: %02u", mth);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    mth++;
                    if(mth > 12){
                        mth = 12;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    mth--;
                    if(mth < 1){
                        mth = 1;
                    }
                }
                break;
                
            case 3:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                LcdALL_Write_Char('A');
                LcdALL_Write_Char(0);
                LcdALL_Write_Char('o');
                sprintf(buffer, ": %02u", year);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    year++;
                    if(year > 99){
                        year = 99;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    year--;
                    if(year == -1){
                        year = 0;
                    }
                }
                break;
                
            case 4:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                sprintf(buffer, "Dia semana: %u", dow);
                LcdALL_Write_String(buffer);
                LcdALL_Set_Cursor(2,1);
                sprintf(buffer, "%s    ", dw[dow]);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    dow++;
                    if(dow > 6){
                        dow = 6;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    dow--;
                    if(dow == -1){
                        dow = 0;
                    }
                }
                break;
                
            case 5:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                sprintf(buffer, "Hora: %02u", hr);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    hr++;
                    if(hr > 23){
                        hr = 23;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    hr--;
                    if(hr == -1){
                        hr = 0;
                    }
                }
                break;
                
            case 6:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                sprintf(buffer, "Minuto: %02u", min);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    min++;
                    if(min > 59){
                        min = 59;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    min--;
                    if(min == -1){
                        min = 0;
                    }
                }
                break;
                
            case 7:
                LcdALL_Clear();
                LcdALL_Set_Cursor(1,1);
                sprintf(buffer, "Segundo: %02u", sec);
                LcdALL_Write_String(buffer);
                if(PORTBbits.RB1 == 0)
                {
                    while(PORTBbits.RB1 == 0);
                    __delay_ms(20);
                    sec++;
                    if(sec > 59){
                        sec = 59;
                    }
                }
                if(PORTBbits.RB2 == 0)
                {
                    while(PORTBbits.RB2 == 0);
                    __delay_ms(20);
                    sec--;
                    if(sec == -1){
                        sec = 0;
                    }
                }
                break;
                
            default:
            	day = (uint8_t)day;
            	mth = (uint8_t)mth;
            	year = (uint8_t)year;
            	dow = (uint8_t)dow;
            	hr = (uint8_t)hr;
            	min = (uint8_t)min;
            	sec = (uint8_t)sec;
                DS3231_Set_Date_Time(day,mth,year,dow,hr,min,sec);
                estado = 0;
                break;
        }
        
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISE = 0;
    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    PORTA = 0;
    PORTE = 0;
    
    ioc_init(0);
    ioc_init(1);
    ioc_init(2);

     //INTERRUPCIÓN GLOBAL
    INTCONbits.GIE = 1;         // Activación Interrupción Global

    //OSCILADOR
    OSCCONbits.IRCF = 0b111;    // 8MHz
    OSCCONbits.SCS = 1;         // Utilización del oscilador Interno
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
    
}