/*
 * Fichier:   main.c, version étudiant
 * Auteur: Benoit
 * Crée le 18 février 2020, modif le 16 avril 2021
 * Brief: Lab6 du cours 416.
 * Matériel: PIC18F458, osciallateur de 40MHz (important pour les timings critiques des DEL NeoPixel, 
 * Anneau de DEL neoPixel WS2812 
 * (https://www.digikey.ca/product-detail/en/adafruit-industries-llc/1643/1528-1102-ND/5154677)
 * Convertisseur USB-Série.
 * Fonctionne avec le simulateur (SimTrameLabServomoteur) écrit en C# par Benoit
 * 
 */


#include <xc.h>
#include "NeoPxl.h"
#include "EffetsNeoPx.h"
#include <stdbool.h>
#include <stdint.h>


/****** Constantes ************/
#define _XTAL_FREQ 40000000 //Constante utilisée par delaisMS(x). Doit = fréq de l'oscillateur 
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
 * @brief Vérifie s'il y a un caractère de reçu par le port série. Si oui
 * on l'ajoute à la trame. La variable indexTrame nous indique où mettre le 
 * caracère reçu dans le buffer de réception.
 * @param Le pointeur du buffer de réception des caractères
 * @return Vrai si tous les caractères de la trame ont été reçu (indexTrame = MAX_TRAME) et 
 * si le checksum est bon.
 * Faux Si tous les caractères n'ont pas encore été reçu.
 * 
 */
bool rxTrame(unsigned char* buffer)
{
    bool retour = false;
    static int indexTrame = 0;

    //à compléter
    
    return retour;
    
}

/**
 * @brief Selon l'octet "Effet" (buffer[EFFET]) dans la trame, appelle la méthode correspondant à l'effet désiré.
 * @param Le pointeur de la trame reçue.
 * @return rien
 * 
 */
void traiteTrame(unsigned char* buffer)
{
    
}


void initialisation(void)
{
    
}

