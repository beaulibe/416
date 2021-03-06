/**
 * @file   initialisation.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Contient la d�finition des prototypes de fonctions utilis�s pour l'initalisation des diff�rents registres de contr�le du PIC.
 *
 */
#ifndef INITIALISATION_H
#define	INITIALISATION_H

#include "commun.h"

/**
 * @brief Fonction utilis�e pour configurer l'ensemble des registres.
 */
void initialisation_ConfigurerRegistres(void);

/**
 * @brief Fonction utilis�e pour configurer le PORTD en sortie.
 */
void initialisation_ConfigurerPortDSortie(void);

/**
 * @brief Fonction utilis�e pour activer les interruptions (au global les activations sp�cifiques sont faites ailleurs).
 */
void initialisation_ActiverInterruptions(void);

/**
 * @brief Fonction utilis�e pour mettre la ligne RB0 en entr�e et activer les r�sistances de "PULL-UP" internes.
 */
void initialisation_ConfigurerInterrupteurRB0(void);

/**
 * @brief Fonction utilis�e pour activer l'INT0
 */
void initialisation_ActiverInt0(void);

/**
 * @brief Fonction utilis�e pour activer Timer0 avec un d�lai d'une seconde
 */
void initialisation_ActiverTimer0(void);

/**
 * @brief Configuration du mode Analogique pour AN0
 */
void initialisation_ConfigurerAdc(void);

/**
 * @brief Activer l'interruption de fin de conversion du ADC
 */
void initialisation_ActiverIntAdc(void);

/**
 * @brief Configuration et activation de la ligne PWM
 */
void initialisation_ActiverPWM(void);
#endif	/* INITIALISATION_H */

