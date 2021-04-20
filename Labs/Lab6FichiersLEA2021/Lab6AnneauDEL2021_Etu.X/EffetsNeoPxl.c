/*
 * Fichier:   EffetsNoePxl.c
 * Auteur: Benoit
 * Crée le 18 février 2020, 15:59, modif 16 avril 2021
 * Brief: 
 * 
 */


#include <xc.h>
#include "NeoPxl.h"
#include <stdbool.h>
#include <stdint.h>

extern uint8_t g_NeoGreen [NEO_NUM];
extern uint8_t g_NeoBlue [NEO_NUM];
extern uint8_t g_NeoRed [NEO_NUM];


void NeoRotate (void)
{
   uint8_t NeoPixel; 
   uint8_t R,G,B; //données temporaires
   G = g_NeoGreen[0];
   B = g_NeoBlue[0];
   R = g_NeoRed[0];
           
           
   for (NeoPixel = 0; NeoPixel < NEO_NUM - 1; NeoPixel++)   
   {           
      g_NeoGreen[NeoPixel] = g_NeoGreen[NeoPixel + 1];
      g_NeoBlue[NeoPixel] = g_NeoBlue[NeoPixel + 1];
      g_NeoRed[NeoPixel] = g_NeoRed[NeoPixel + 1];
   }
   g_NeoGreen[NEO_NUM - 1] = G;
   g_NeoBlue[NEO_NUM - 1] = B;
   g_NeoRed[NEO_NUM - 1] = R; 
}

void NeoWave(void)
{
   
}


/**
 * @brief Iniialise les tableaux de couleurs. 2 DEL de chaque couleur (rouge, bleu
 * violet,vert, jaune et cian)
 * On met 64 Comme valeur et non 255 car à 255 ça éclaire trop fort !
 * @param 
 * @return rien
 */
void NeoSet6Couleur (void)
{
   uint8_t NeoPixel;
   //boucle pour les 12 DEL
   for (NeoPixel = 0; NeoPixel < NEO_NUM; NeoPixel++)   
   {
      if (NeoPixel < 2) 
         { g_NeoGreen[NeoPixel] = 0; g_NeoBlue[NeoPixel] = 0; g_NeoRed[NeoPixel] = 64; } //2 del en rouge
      else if ((NeoPixel >= 2) & (NeoPixel < 4))
         { g_NeoGreen[NeoPixel] = 0; g_NeoBlue[NeoPixel] = 64; g_NeoRed[NeoPixel] = 0; } //2 del en bleu
      else if ((NeoPixel >= 4) & (NeoPixel < 6))
         { g_NeoGreen[NeoPixel] = 0; g_NeoBlue[NeoPixel] = 64; g_NeoRed[NeoPixel] = 64; } //2 del en violet
      else if ((NeoPixel >= 6) & (NeoPixel < 8))
         { g_NeoGreen[NeoPixel] = 64; g_NeoBlue[NeoPixel] = 0; g_NeoRed[NeoPixel] = 0; } //2 del en vert
      else if ((NeoPixel >= 8) & (NeoPixel < 10))
         { g_NeoGreen[NeoPixel] = 64; g_NeoBlue[NeoPixel] = 0; g_NeoRed[NeoPixel] = 64; } //2 del en jaune
      else if ((NeoPixel >= 10) & (NeoPixel < NEO_NUM))
         { g_NeoGreen[NeoPixel] = 64; g_NeoBlue[NeoPixel] = 64; g_NeoRed[NeoPixel] = 0; } //2 del en cian
   }
}
