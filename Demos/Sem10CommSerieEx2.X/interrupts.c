/**
 * @file   interrupts.c
 * @author Benoit Beaulieu
 * @date   mars 2020
 * @brief  Ce fichier contient la gestion des diff�rentes interruptions.
 * @version 
 */


#include <xc.h>
#include <stdbool.h>       /* For true/false definition */

unsigned char g_rxCar = 0;
/**
 * @brief Fonction qui re�oit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{    
        if (PIR1bits.RC1IF == 1) //une donn�e re�ue
        {
            PIR1bits.RC1IF = 0; //raz du flag. Je crois qu'une lecture du RCREG est suffusante pour raz le flag... � v�rifier
            g_rxCar = RCREG; //lecture au port s�rie
            PORTD = g_rxCar; //affiche la donn�e re�u sur les DEL
        }
}

