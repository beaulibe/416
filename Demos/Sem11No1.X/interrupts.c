/**
 * @file   interrupts.c
 * @author Benoit Beaulieu
 * @date   mars 2018
 */


#include "xc.h"


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
void __interrupt() high_isr(void)
{
    static char compteur=0;
    
    /***** AN *****/
    if(PIR1bits.ADIF)   //interruption du ADC
    {
        PORTD = (ADRESH & 0xF0) | (PORTD & 0x0F);
        PIR1bits.ADIF=0;  //reset flag d'intr.
        ADCON0bits.GO_DONE = 1;  //lance une nouvelle conversion AN
    }
    
    
    /***Timer 3****/
    if (PIR2bits.TMR3IF) // timer 3
    {
        PIR2bits.TMR3IF   = 0;    // baisser l'indication de l'interruption
        TMR3 = 49911; //16Hz (250KHz/15625=16Hz). 65536-15625 = 49911
        compteur++;
        PORTD = (PORTD & 0xF0) | (compteur & 0x0F);
    }

    
}


