/**
 * @file   Commun.h
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fichier qui contient les "includes" nécessaires pour le projet. Les définitions des fonctions partagées entre les différents fichiers.c sont faites ici.
 *
 */

#ifndef COMMUN_H
#define COMMUN_H

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "initialisation.h"




/**
 * @brief Fonction utilitaire pour permettre de gérer des délais fixe (CODE BLOQUANT!!!)
 * @param delai_ms valeur en ms du delai voulu
 */
void commun_delaiMS(uint16_t delai_ms);

#endif