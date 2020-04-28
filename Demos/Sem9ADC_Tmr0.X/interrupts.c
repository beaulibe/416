/**
 * @file   interrupts.c
 * @author Benoit Beaulieu
 * @date   mars 2020
 * @brief  Ce fichier contient la gestion des diff�rentes interruptions.
 * @version 
 */


#include <xc.h>
//#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#define FOSC 1000000 //Fr�quence de l'horloge externe du PIC18F45K20
#define PRESCALER 16 //Prescaler utilis� pour le timer 0

/** valeur obtenue suite � la conversion A/N */
int g_resAN       = 0;


/**
 * @brief Fonction qui re�oit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{    
    int diviseurAN = 1;
    
    if (PIR1bits.ADIF)     // conversion A/N
    {
        g_resAN = ADRESH;  // le r�sultat de la conversion est configur� comme etant align� � GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // d�marrer une autre conversion
    }
    
    // Timer 0
    if (INTCONbits.TMR0IF) // timer 0
    {
        INTCONbits.TMR0IF   = 0;    // baisser l'indication de l'interruption
        
        diviseurAN = g_resAN>>4;
        if (diviseurAN == 0)
            diviseurAN = 1;
        
        TMR0 = 65536 - (((unsigned long)FOSC)/(4*(unsigned int)PRESCALER))/diviseurAN; //15625/diviseurAN
       

        PORTDbits.RD7 ^= 1; //Toggle del 0
    }    

}

