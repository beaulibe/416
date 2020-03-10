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

void NeoWave(void)
{
   uint8_t NeoPixel; 
   
   static int position = 0;
   static int couleur;
   
   // on décale tout le mode
   for (NeoPixel = 0; NeoPixel < NeoNum - 1; NeoPixel++)   
   {           
      NeoGreen[NeoPixel] = NeoGreen[NeoPixel + 1];
      NeoBlue[NeoPixel] = NeoBlue[NeoPixel + 1];
      NeoRed[NeoPixel] = NeoRed[NeoPixel + 1];
   }
   
   couleur = (couleur + 10) % 300;
   
   if (couleur < 100)
   {
        NeoGreen[NeoNum - 1] = (uint8_t) couleur; 
        NeoBlue[NeoNum - 1] = (uint8_t) 0;
        NeoRed[NeoNum - 1] = (uint8_t) 0;
   }
   else if (couleur < 200)
   {
        NeoGreen[NeoNum - 1] = (uint8_t) 0; 
        NeoBlue[NeoNum - 1] = (uint8_t) couleur % 100;
        NeoRed[NeoNum - 1] = (uint8_t) 0;
   }

   else if (couleur < 300)
   {
        NeoGreen[NeoNum - 1] = (uint8_t) 0; 
        NeoBlue[NeoNum - 1] = (uint8_t) 0;
        NeoRed[NeoNum - 1] = (uint8_t) couleur % 200;
   }

   
   
   
}