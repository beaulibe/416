/*
 * File:   NeoCol.c
 * Author: Benoit
 * Created on 18 février 2020, 15:59
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

//Pour le configuration_bits.c
//#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
//#FUSES NOBROWNOUT               //No brownout reset
//#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
//#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)


#include <xc.h>
#include "NeoPxl.h"
#include <stdint.h>


/*****  tableaux pour les valeurs (0 à 0xFF) des 3 couleurs */
// La couleur résultante de la DEL sera l'agencement de ces 3 valeurs de 8 bits sur 24 bits
// dans le format : 0xGGBBRR 
uint8_t NeoGreen [NeoNum];
uint8_t NeoBlue [NeoNum];
uint8_t NeoRed [NeoNum];


/**
 * @brief Met les courleurs dans les tableaux de couleurs. 
 * @param R, G, B valeur entre 0 et 255 pour chacune des 3 couleurs 
 * @return rien
 */
void NeoSetColor(uint8_t R, uint8_t G, uint8_t B)
{
    for (int i = 0; i < NeoNum; i++)
    {
        NeoGreen[i]= G;
        NeoRed[i]=R;
        NeoBlue[i]=B;
    }
    
}
/**
 * @brief Iniialise les tableaux de couleurs. 2 DEL de chaque couleur (rouge, bleu
 * violet,vert, jaune et cian)
 * On met 64 Comme valeur et non 255 car à 255 ça éclaire trop fort !
 * @param 
 * @return rien
 */
void NeoInit (void)
{
   uint8_t NeoPixel;
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)   
   {
      if (NeoPixel < 2)
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 64; } //2 del en rouge
      else if ((NeoPixel >= 2) & (NeoPixel < 4))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 0; } //2 del en bleu
      else if ((NeoPixel >= 4) & (NeoPixel < 6))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 64; } //2 del en violet
      else if ((NeoPixel >= 6) & (NeoPixel < 8))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; } //2 del en vert
      else if ((NeoPixel >= 8) & (NeoPixel < 10))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 64; } //2 del en jaune
      else if ((NeoPixel >= 10) & (NeoPixel < NeoNum))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 0; } //2 del en cian
   }
}


/**
 * @brief Génère une impultion de 400ns si Bit = 0 ou de 800ns si Bit=1 sur la broche NoePin
 * @param Bit Un des 8 bits sera à 1 si on doit faire une impultion de 800ns, 
 * sinon ils seront tous à 0 et on fera une impulsion de 400ns.
 * Note: Les timings sont critiques pour un 1 et un 0, mais ne semblent pas trop critiques
 * entre l'envoie de chacun des bits.
 * @return rien
 */
void NeoBit(uint8_t Bit)
{
   if (Bit != 0)  //au moins un bit à 1, donc impulsion de 800ns
   { 
      NeoPin = 1; // output_high (NeoPin); 
      Nop(); // On veut une impulsion de 800ns 
      Nop(); // 1 Nop() = 100nSec
      Nop();       
      Nop(); 
      Nop();       
      Nop(); 
      Nop();       
      NeoPin = 0; 
   } 
   else //tout les bits à 0 donc impulsion de 400ns
   { 
       NeoPin = 1; 
       Nop(); // On veut une impulsion de 400ns 
       Nop(); // 1 Nop() = 100nSec
       Nop();       
       NeoPin = 0;
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
   
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
    {    
      for (BitCount = 7; BitCount >= 0; BitCount--)
          NeoBit(NeoGreen[NeoPixel] & (1 <<(BitCount)));
      for (BitCount = 7; BitCount >= 0; BitCount--)           
         NeoBit(NeoRed[NeoPixel] & (1 <<(BitCount)));
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         NeoBit(NeoBlue[NeoPixel] & (1 <<(BitCount)));          
    }
   NeoPin = 0;//On s'assure de ramener la ligne à 0
}

