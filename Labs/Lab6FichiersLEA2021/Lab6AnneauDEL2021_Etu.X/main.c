/*
 * Fichier:   main.c, version �tudiant
 * Auteur: Benoit
 * Cr�e le 18 f�vrier 2020, modif le 16 avril 2021
 * Brief: Lab6 du cours 416.
 * Mat�riel: PIC18F458, osciallateur de 40MHz (important pour les timings critiques des DEL NeoPixel, 
 * Anneau de DEL neoPixel WS2812 
 * (https://www.digikey.ca/product-detail/en/adafruit-industries-llc/1643/1528-1102-ND/5154677)
 * Convertisseur USB-S�rie.
 * Fonctionne avec le simulateur (SimTrameLabServomoteur) �crit en C# par Benoit
 * 
 */


#include <xc.h>
#include "NeoPxl.h"
#include "EffetsNeoPx.h"
#include <stdbool.h>
#include <stdint.h>


/****** Constantes ************/
#define _XTAL_FREQ 40000000 //Constante utilis�e par delaisMS(x). Doit = fr�q de l'oscillateur 
#define MAX_TRAME 6
#define SOH 1

enum enumTrame {EFFET=1,R,G,B};

/****** Prototypes ********/
void initialisation(void);
//unsigned char rxComm(void);  //pour tests
bool rxTrame(unsigned char* buffer);
void traiteTrame(unsigned char* buffer);

    

void main(void) 
{
    
    unsigned char trame[MAX_TRAME];
    
    
    initialisation();
    
    NeoSet6Couleur();   //rempli les tableaux g_NeoGreen[], g_NeoBlue[] et g_NeoRed[] avec 2 DEL de chaque couleur. Il y aura donc 6 couleurs au total]
    NeoDraw (); //envoie les valeurs de tableaux aux DEL pour afficher   
    while(true)
        
    {       
      if (rxTrame(trame))
      {
          traiteTrame(trame);
          NeoDraw ();

      }
    }

    return;
}


/**
 * @brief V�rifie s'il y a un caract�re de re�u par le port s�rie. Si oui
 * on l'ajoute � la trame. La variable indexTrame nous indique o� mettre le 
 * carac�re re�u dans le buffer de r�ception.
 * @param Le pointeur du buffer de r�ception des caract�res
 * @return Vrai si tous les caract�res de la trame ont �t� re�u (indexTrame = MAX_TRAME) et 
 * si le checksum est bon.
 * Faux Si tous les caract�res n'ont pas encore �t� re�u.
 * 
 */
bool rxTrame(unsigned char* buffer)
{
    bool retour = false;
    static int indexTrame = 0;

    //� compl�ter
    
    return retour;
    
}

/**
 * @brief Selon l'octet "Effet" (buffer[EFFET]) dans la trame, appelle la m�thode correspondant � l'effet d�sir�.
 * @param Le pointeur de la trame re�ue.
 * @return rien
 * 
 */
void traiteTrame(unsigned char* buffer)
{
    
}


void initialisation(void)
{
    
}

