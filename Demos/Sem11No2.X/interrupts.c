/**
 * @file   interrupts.c
 * @author Benoit Beaulieu
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des différentes interruptions.
 
 */

#include <xc.h>
//extern unsigned char decompte;
/**
 * @brief Fonction qui reçoit les appels d'interruptions "high"
 */
void __interrupt() high_isr(void)
{
    if (INTCONbits.TMR0IF) // timer 0
    {
        INTCONbits.TMR0IF   = 0;    // baisser l'indication de l'interruption
        PORTD--;
        if (PORTD == 0)
        {
            T0CONbits.TMR0ON    = 0; //stop tmr0
        }
        
        TMR0 = 62411; //65536 - 3125 //20Hz
    }
}

