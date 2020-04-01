/**
 * @file   Commun.h
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fichier qui contient les "includes" n�cessaires pour le projet. Les d�finitions des fonctions partag�es entre les diff�rents fichiers.c sont faites ici.
 *
 */

#ifndef COMMUN_H
#define COMMUN_H

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/**
 * @brief Fonction utilitaire pour permettre de g�rer des d�lais fixe (CODE BLOQUANT!!!)
 * @param delai_ms valeur en ms du delai voulu
 */
void commun_delaiMS(uint16_t delai_ms);


unsigned int lectureAN_;  //variable globale pour la lecture AN (10bits) Lue dans interrupts.c


#endif