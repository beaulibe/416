/*
 * File:   NeoPxl.c
 * Author: Benoit
 * Created on 18 février 2020, modif 16 avril 2021
 * Brief: Code permet de contrôler un anneau de 12 DEL utilisé dans le 
 * labo 6 du cours 416.
 * La difficulté provient des timings serrés pour transmettre les données aux DEL
 * C'est pourquoi on a utilisé un oscillateur de 40MHz
 * 
 * 
 * 
 * Le code originale provient de https://www.youtube.com/watch?v=EXr2_zSfnFw et 
 * https://github.com/EduardoAule/PIC18-Neopixel.
 * Anneau de DEL neoPixel WS2812 (https://www.digikey.ca/product-detail/en/adafruit-industries-llc/1643/1528-1102-ND/5154677)
 * 
 * 
 */



#include <xc.h>
#include "NeoPxl.h"
#include <stdint.h>


/*****  tableaux pour les 12 valeurs (0 à 0xFF) des 3 couleurs */
// La couleur résultante de la DEL sera l'agencement de ces 3 valeurs de 8 bits sur 24 bits
// dans le format : 0xGGBBRR 
uint8_t g_NeoGreen [NEO_NUM];  //NoeNum défini dans NeoPxl.h (= 12 car il y a 12 DEL)
uint8_t g_NeoBlue [NEO_NUM];
uint8_t g_NeoRed [NEO_NUM];


/**
 * @brief Met les couleurs dans les tableaux de couleurs. 
 * @param R, G, B valeur entre 0 et 255 pour chacune des 3 couleurs 
 * @return rien
 */
void NeoSetColor(uint8_t R, uint8_t G, uint8_t B)
{
    for (int i = 0; i < NEO_NUM; i++)
    {
        g_NeoGreen[i]= G;
        g_NeoRed[i]=R;
        g_NeoBlue[i]=B;
    }
    
}


/**
 * @brief Génère une impulsion de 400ns si Bit = 0 ou de 800ns si Bit=1 sur la broche NoePin
 * @param Bit Un des 8 bits sera à 1 si on doit faire une impulsion de 800ns, 
 * sinon ils seront tous à 0 et on fera une impulsion de 400ns.
 * Note: Les timings sont critiques pour un 1 et un 0, mais ne semblent pas trop critiques
 * entre l'envoie de chacun des bits.
 * @return rien
 */
void NeoBit(uint8_t Bit)
{
   if (Bit != 0)  //au moins un bit à 1, donc impulsion de 800ns
   { 
      NEO_PIN = 1; // output_high (NEO_PIN); 
      Nop(); // On veut une impulsion de 800ns 
      Nop(); // 1 Nop() = 100nSec
      Nop();       
      Nop(); 
      Nop();       
      Nop(); 
      Nop();       
      NEO_PIN = 0; 
   } 
   else //tous les bits à 0, donc impulsion de 400ns
   { 
       NEO_PIN = 1; 
       Nop(); // On veut une impulsion de 400ns 
       Nop(); // 1 Nop() = 100nSec
       Nop();       
       NEO_PIN = 0;
   } 

}

/**
 * @brief Méthode appelée lorsqu'on veut afficher les couleurs contenues dans les 
 * tableaux NeoGreen, NeoRed et NeoBlue sur les 12 DEL.
 * La méthode appelle la méthode NeoBit pour générer les impultions de 800ns et 400ns
 * @param aucun
 * @return rien
 */
void NeoDraw (void)
{
   uint8_t NeoPixel;
   int8_t BitCount;
     
  // while(1) NeoBit(1); //pour tester et ajuster la largeur d'impulsion dans NeoBit()
   
   for (NeoPixel = 0; NeoPixel < NEO_NUM; NeoPixel++)
    {    
      for (BitCount = 7; BitCount >= 0; BitCount--)
          NeoBit(g_NeoGreen[NeoPixel] & (1 <<(BitCount)));
      for (BitCount = 7; BitCount >= 0; BitCount--)           
         NeoBit(g_NeoRed[NeoPixel] & (1 <<(BitCount)));
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         NeoBit(g_NeoBlue[NeoPixel] & (1 <<(BitCount)));          
    }
   NEO_PIN = 0;//On s'assure de ramener la ligne à 0
}

