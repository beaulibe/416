/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des différentes interruptions.
 * @version 1.1 Benoit Beaulieu, mars 2015
 */

#include "commun.h"

/** valeur à utiliser pour la sortie PWM */
//int valeurPwm_                  = 0;
/** valeur obtenue suite à la conversion A/N */
int g_resAN       = 0;


/**
 * @brief Fonction qui reçoit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{    
    
    if (PIR1bits.ADIF)     // conversion A/N
    {
        g_resAN = ADRESH;  // le résultat de la conversion est configuré comme etant aligné à GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // démarrer une autre conversion
    }

}

