/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des diff�rentes interruptions.
 * @version 1.1 Benoit Beaulieu, mars 2015
 */

#include "commun.h"

/** valeur � utiliser pour la sortie PWM */
//int valeurPwm_                  = 0;
/** valeur obtenue suite � la conversion A/N */
int g_resAN       = 0;


/**
 * @brief Fonction qui re�oit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{    
    
    if (PIR1bits.ADIF)     // conversion A/N
    {
        g_resAN = ADRESH;  // le r�sultat de la conversion est configur� comme etant align� � GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // d�marrer une autre conversion
    }

}

