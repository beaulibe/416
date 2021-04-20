/**
 * @file   interrupts.c
 * @author Benoit Beaulieu  
 * @date   Avril 2021
 * @brief  Fonctions pour les interruptions
 * 
 */


#include "xc.h"




/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */

void __interrupt(high_priority) high_isr(void)
{
    static unsigned char g_caracRx = 'A';

    //réception par le port série
    if (PIR1bits.RC1IF)
    {
        g_caracRx = RCREG;
        PORTD = g_caracRx;
        PIR1bits.RC1IF = 1;
    }
    
    //interruption INT0 sur SW1
    if ( INTCONbits.INT0IF)
    {
        while(PIR1bits.TXIF==0); //on attend que le registe de transmission soit prêt 
        PORTD = g_caracRx;
        TXREG = g_caracRx++;
        INTCONbits.INT0IF = 0;
    }   
}


