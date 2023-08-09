/* 
 * File:   ADC_Library.h
 * Author: pablo
 *
 * Created on 18 de julio de 2023, 4:05 p.m.
 */

#ifndef ADC_LIBRARY_H
#define	ADC_LIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif

int adc_init(int channel);
int adc_read();
int adc_change_channel(int channel);
int adc_get_channel();


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_LIBRARY_H */

