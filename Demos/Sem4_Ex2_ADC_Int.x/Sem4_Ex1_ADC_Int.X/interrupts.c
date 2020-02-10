/**
 * @file   interrupts.c
 */

#include <xc.h>
#include "interrupts.h"


// variables globales 

struct moteur stMotMoulin;
unsigned int g_lectureAN = 0;

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
    
    if(PIR1bits.ADIF) //Flag d'interruption de l'ADC
    {
        //On assemble les 10 bits et on les enregistre dans g_lectureAN. 
        //Note: Il faut un alignement à droite ADFM = 1
        g_lectureAN = (unsigned int)((ADRESH << 8) | ADRESL); 
        PIR1bits.ADIF = 0; //On remet à zéro le flag d'interruption
        ADCON0bits.GO_DONE = 1; //On démarre une nouvelle conversion de l'ADC
    }
    
    
}

/* Low-priority interrupt service routine */
void __interrupt(low_priority) low_isr(void)
{
    //Rien à faire dans cette fonction pour l'exercice actuel
}