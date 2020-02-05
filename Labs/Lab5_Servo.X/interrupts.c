/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des différentes interruptions.
 * @version Benoit Beaulieu, février 2020
 */

//#include "commun.h"
#include <xc.h>
#include <stdbool.h>

#define PWM_MIN 9
#define PWM_MAX 0x25


/** valeur à utiliser pour la sortie PWM */
//int valeurPwm_                  = 0;
/** valeur obtenue suite à la conversion A/N */
int g_resAN       = 0;


/**
 * @brief Fonction qui reçoit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{
    static unsigned char dutyWiper = PWM_MIN;
    static bool sensUp = true;
    
    
    if (PIR1bits.ADIF)     // conversion A/N
    {
        g_resAN = ADRESH;  // le résultat de la conversion est configuré comme etant aligné à GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // démarrer une autre conversion
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

