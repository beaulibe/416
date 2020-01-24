/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Reception des caracteres du clavier par INT0
 * @revision Benoit Beaulieu, janvier 2016, ajustement pour le nom des variables globales
 *           Jacob Deschamps, décembre 2018, ajout de commentaires et contrôle de la DEL rouge pour qu'elle réagisse à chaque interruption
 */

#include <xc.h>
#include "interrupts.h"

//Variables globales pour la lecture du clavier par interruption
unsigned int  g_nombreCar = 0; //Nombre de caractères dans le tampon
unsigned char g_temponClavier[NOMBRE_CAR_MAX]; //Tampon de reception des caractères

/******************************************************************************/
/* Interrupt Service Routines                                                 */
/******************************************************************************/

/* High-priority interrupt service routine */
void __interrupt(high_priority) high_isr(void)
{
    unsigned char nLecture; //Variable qui contiendra le caractère ASCII du clavier
    
    if(INTCONbits.INT0F)   //interruption du clavier (INT0)?
    {
        nLecture = PORTD & 0x7f; //Valeur du code ASCII du clavier (le bit RD7 du port D n'est pas connecté au clavier)
        PORTDbits.RD7 ^= 1; //La DEL rouge clignote (pour indiquer que l'interruption INT0 est survenue)
        
        if(g_nombreCar < NOMBRE_CAR_MAX)  //Si le tampon n'est pas plein
        {
            g_temponClavier[g_nombreCar] = nLecture;  //Enregistre le caractère reçu dans le tampon
            g_nombreCar++; //Incrémente le nombre de caractères présents dans le tampon
        }
        else //S'il y a trop de caractères, on ne garde que le nouveau
        {
            g_nombreCar = 1; //Le nombre de caractères revient à un seul
            g_temponClavier[0] = nLecture; //Enregistre le caractère reçu dans le tampon
        }
        
        INTCONbits.INT0F = 0;  //On remet le flag d'interruption à 0
    }
 
}

/* Low-priority interrupt service routine */
void __interrupt(low_priority) low_isr(void)
{
    //Il n'y a rien à ajouter ici pour le laboratoire 1
}
