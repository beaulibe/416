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



int g_resAN = 0;/** valeur obtenue suite � la conversion A/N */
int g_freq = 0;
int g_delTmr0; //Variable indiquant l'�tat de la DEL7 (allum�e ou �teinte)

   

/**
 * @brief Fonction qui re�oit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{   
    static int nbInt1 = 0;
    int diviseurAN = 1;
    
    // ADC
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
        
        TMR0 = 65536 - (((unsigned long)FOSC)/(4*(unsigned int)PRESCALER))/diviseurAN;
  
        //PORTDbits.RD7 ^= 1; //Toggle del 7. � NE PAS FAIRE ICI, CAR GENERE L'INTERRUPTION D'INT1 IMMEDIATEMENT ET CA FAIT DES PROBLEMES
        g_delTmr0 = !g_delTmr0; //On changera l'�tat de la DEL7 dans le main
    }    
    
    //Timer 1
    if (PIR1bits.TMR1IF) //Si l'interruption du timer 1 survient
    {
        PIR1bits.TMR1IF = 0; //On remet � z�ro le flag d'interruption du timer 1

        g_freq = nbInt1; //La fr�quence revient au nombre de fois que l'INT1 est survenue
        nbInt1 = 0; //On remet le compteur d'interruption � 0
        
        TMR1 = 0x85EE; //On recharge la valeur du timer 1 pour qu'il puisse de nouveau s'�couler
    }
    
    
    
    // INT1
    if(INTCON3bits.INT1IF) //Si l'interruption INT1 survient
    {
        INTCON3bits.INT1IF = 0; //On remet � z�ro le flag d'interruption de l'INT1
        nbInt1++; //On incr�mente le nombre de fois que cette interruption est survenue
    }

    
   
}

/* Low-priority interrupt routine */
void __interrupt(low_priority) low_isr(void)
{

}
