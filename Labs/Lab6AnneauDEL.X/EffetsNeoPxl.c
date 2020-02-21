/*
 * Fichier:   EffetsNoePxl.c
 * Auteur: Benoit
 * Crée le 18 février 2020, 15:59
 * Brief: 
 * 
 */


#include <xc.h>
#include "NeoPxl.h"
#include <stdbool.h>
#include <stdint.h>

extern uint8_t NeoGreen [NeoNum];
extern uint8_t NeoBlue [NeoNum];
extern uint8_t NeoRed [NeoNum];


void NeoRotate (void)
{
   uint8_t NeoPixel; 
   uint8_t R,G,B; //données temporaires
   G = NeoGreen[0];
   B = NeoBlue[0];
   R = NeoRed[0];
           
           
   for (NeoPixel = 0; NeoPixel < NeoNum - 1; NeoPixel++)   
   {           
      NeoGreen[NeoPixel] = NeoGreen[NeoPixel + 1];
      NeoBlue[NeoPixel] = NeoBlue[NeoPixel + 1];
      NeoRed[NeoPixel] = NeoRed[NeoPixel + 1];
   }
   NeoGreen[NeoNum - 1] = G;
   NeoBlue[NeoNum - 1] = B;
   NeoRed[NeoNum - 1] = R; 
}

