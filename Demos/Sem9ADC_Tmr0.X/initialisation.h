/**
 * @file   initialisation.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Contient la définition des prototypes de fonctions utilisés pour l'initalisation des différents registres de contrôle du PIC.
 *
 */
#ifndef INITIALISATION_H
#define	INITIALISATION_H

#include "commun.h"

/**
 * @brief Fonction utilisée pour configurer l'ensemble des registres.
 */
void initialisation_ConfigurerRegistres(void);

/**
 * @brief Fonction utilisée pour configurer le PORTD en sortie.
 */
void initialisation_ConfigurerPortDSortie(void);

/**
 * @brief Fonction utilisée pour activer les interruptions (au global les activations spécifiques sont faites ailleurs).
 */
void initialisation_ActiverInterruptions(void);

/**
 * @brief Fonction utilisée pour mettre la ligne RB0 en entrée et activer les résistances de "PULL-UP" internes.
 */
void initialisation_ConfigurerInterrupteurRB0(void);

/**
 * @brief Fonction utilisée pour activer l'INT0
 */
void initialisation_ActiverInt0(void);

/**
 * @brief Fonction utilisée pour activer Timer0 avec un délai d'une seconde
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

