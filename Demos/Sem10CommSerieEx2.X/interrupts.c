/**
 * @file   interrupts.c
 * @author Benoit Beaulieu
 * @date   mars 2020
 * @brief  Ce fichier contient la gestion des différentes interruptions.
 * @version 
 */


#include <xc.h>
#include <stdbool.h>       /* For true/false definition */

unsigned char g_rxCar = 0;
/**
 * @brief Fonction qui reçoit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{    
        if (PIR1bits.RC1IF == 1) //une donnée reçue
        {
            PIR1bits.RC1IF = 0; //raz du flag. Je crois qu'une lecture du RCREG est suffusante pour raz le flag... à vérifier
            g_rxCar = RCREG; //lecture au port série
            PORTD = g_rxCar; //affiche la donnée reçu sur les DEL
        }
}

