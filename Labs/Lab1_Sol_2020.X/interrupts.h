/* 
 * File: interrupts.h
 * Author: Enseignants en TGE
 * Created on 12 janvier 2017, 14:05
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#define NOMBRE_CAR_MAX 10 //Taille maximale du tampon contenant les caract�res re�us

//Prototypes des fonctions d'interruption
void __interrupt(high_priority) high_isr(void); //Fonction d'interruption de haute priorit�
void __interrupt(low_priority) low_isr(void); //Fonction d'interruption de basse priorit�

#endif	/* INTERRUPTS_H */

