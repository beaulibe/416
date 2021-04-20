/*
 * Fichier:  
 * Auteur:
 * Date
 * Brief: Lab6 du cours 416.
 * Matériel:
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
bool rxTrame(unsigned char* buffer);
void traiteTrame(unsigned char* buffer);

    

void main(void) 
{
    
    unsigned char trame[MAX_TRAME]; //Contient la trame reçu par le port série
    
    initialisation();
    
    NeoInit();   
    NeoDraw ();    
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
    
    static int indexTrame = 0;
    bool retour = false;
    
    // à compléter
    
    
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