/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des diff�rentes interruptions.
 * @version Benoit Beaulieu, f�vrier 2020
 */

//#include "commun.h"
#include <xc.h>
#include <stdbool.h>

#define PWM_MIN 9
#define PWM_MAX 0x25


/** valeur � utiliser pour la sortie PWM */
//int valeurPwm_                  = 0;
/** valeur obtenue suite � la conversion A/N */
int g_resAN       = 0;


/**
 * @brief Fonction qui re�oit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{
    static unsigned char dutyWiper = PWM_MIN;
    static bool sensUp = true;
    
    
    if (PIR1bits.ADIF)     // conversion A/N
    {
        g_resAN = ADRESH;  // le r�sultat de la conversion est configur� comme etant align� � GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // d�marrer une autre conversion
    }
    
    if (INTCONbits.TMR0IF)     // Tmr0
    {   

        CCPR1L = dutyWiper;
        if (sensUp)
        {
            dutyWiper++;
            if (dutyWiper >= PWM_MAX)
                sensUp = false;
        }
        else
        {
            dutyWiper--;
            if (dutyWiper <= PWM_MIN)
                sensUp = true;
        }   

        INTCONbits.TMR0IF = 0;
        TMR0H = 0xE2;
        TMR0L = 0xB4;

    }


}

