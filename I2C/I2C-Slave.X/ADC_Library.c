/* 
 * Libreria de Configuracion del ADC
 * Author: pablo figueroa
 *
 * Created on 18 de julio de 2023, 
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>
#define _XTAL_FREQ 8000000

int adc_init(int channel){
//Configuración de las interrupciones para el ADC
PIR1bits.ADIF = 0;   // limpiar la bandera de interrupcion del ADC
PIE1bits.ADIE = 1;   // habilitar interrupciones de ADC
INTCONbits.PEIE = 1; // habilitar interrupciones perifericas   

switch (channel) {
    case 0:
        ANSELbits.ANS0 = 1;
        TRISAbits.TRISA0 = 1;
        ADCON0bits.CHS = 0b0000;
        break;
    case 1:
        ANSELbits.ANS1 = 1;
        TRISAbits.TRISA1 = 1;
        ADCON0bits.CHS = 0b0001;
        break;
    case 2:
        ANSELbits.ANS2 = 1;
        TRISAbits.TRISA2 = 1;
        ADCON0bits.CHS = 0b0010;
        break;
    case 3:
        ANSELbits.ANS3 = 1;
        TRISAbits.TRISA3 = 1;
        ADCON0bits.CHS = 0b0011;
        break;
    case 4:
        ANSELbits.ANS4 = 1;
        TRISAbits.TRISA5 = 1;
        ADCON0bits.CHS = 0b0100;
        break;
    case 5:
        ANSELbits.ANS5 = 1;
        TRISEbits.TRISE0 = 1;
        ADCON0bits.CHS = 0b0101;
        break;
    case 6:
        ANSELbits.ANS6 = 1;
        TRISEbits.TRISE1 = 1;
        ADCON0bits.CHS = 0b0110;
        break;
    case 7:
        ANSELbits.ANS7 = 1;
        TRISEbits.TRISE2 = 1;
        ADCON0bits.CHS = 0b0111;
        break;
    default:
        ANSEL = 0;
        // Handle invalid channel value here, if needed.
        break;
}
    //Configuracion ADC

    ADCON0bits.ADCS = 0b10;     //Conversion Clock
    ADCON1bits.ADFM = 0;    //justificado a la izquierda
    ADCON1bits.VCFG0 = 0;   //Vdd
    ADCON1bits.VCFG1 = 0;   //Vss
    ADCON0bits.ADON = 1;    //ADC enable
    ADIF =  0;
    __delay_ms(5);
}

int adc_read(){
    if (ADCON0bits.GO == 0){//Revisión si no está funcionando el ADC
        ADCON0bits.GO = 1; //iniciar la conversion del ADC0.
        __delay_ms(2);
    }    
    }
    
int adc_change_channel(int channel){
switch (channel) {
    case 0:
        ANSELbits.ANS0 = 1;
        TRISAbits.TRISA0 = 1;
        ADCON0bits.CHS = 0b0000;
        break;
    case 1:
        ANSELbits.ANS1 = 1;
        TRISAbits.TRISA1 = 1;
        ADCON0bits.CHS = 0b0001;
        break;
    case 2:
        ANSELbits.ANS2 = 1;
        TRISAbits.TRISA2 = 1;
        ADCON0bits.CHS = 0b0010;
        break;
    case 3:
        ANSELbits.ANS3 = 1;
        TRISAbits.TRISA3 = 1;
        ADCON0bits.CHS = 0b0011;
        break;
    case 4:
        ANSELbits.ANS4 = 1;
        TRISAbits.TRISA5 = 1;
        ADCON0bits.CHS = 0b0100;
        break;
    case 5:
        ANSELbits.ANS5 = 1;
        TRISEbits.TRISE0 = 1;
        ADCON0bits.CHS = 0b0101;
        break;
    case 6:
        ANSELbits.ANS6 = 1;
        TRISEbits.TRISE1 = 1;
        ADCON0bits.CHS = 0b0110;
        break;
    case 7:
        ANSELbits.ANS7 = 1;
        TRISEbits.TRISE2 = 1;
        ADCON0bits.CHS = 0b0111;
        break;
    default:
        ANSEL = 0;
        // Handle invalid channel value here, if needed.
        break;
}   
}
int adc_get_channel(){
    return ADCON0bits.CHS;
}

