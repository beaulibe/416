/**
 * @file   interrupts.c
 */

#include <xc.h>
#include "interrupts.h"


// variables globales 

struct moteur stMotMoulin;

/******************************************************************************/
/* Interrupt Service Routines                                                         */
/******************************************************************************/

/* High-priority interrupt service routine */
void __interrupt(high_priority) high_isr(void)
{
   /* if(INTCONbits.INT0IF)   //interruption INT0?
    {
        stMotMoulin.courant++;
        INTCONbits.INT0IF = 0;  //Remise à zéro du flag d'interruption
    }
    
    if(INTCON3bits.INT2IF)   //interruption INT2?
    {
        stMotMoulin.courant--;
        INTCON3bits.INT2IF = 0;  //Remise à zéro du flag d'interruption
    }
    */
    
    
}

/* Low-priority interrupt service routine */
void __interrupt(low_priority) low_isr(void)
{
    //Rien à faire dans cette fonction pour l'exercice actuel
}