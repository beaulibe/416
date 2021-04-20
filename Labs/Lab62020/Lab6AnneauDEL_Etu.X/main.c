/*
 * Fichier:  
 * Auteur:
 * Date
 * Brief: Lab6 du cours 416.
 * Mat�riel:
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
bool rxTrame(unsigned char* buffer);
void traiteTrame(unsigned char* buffer);

    

void main(void) 
{
    
    unsigned char trame[MAX_TRAME]; //Contient la trame re�u par le port s�rie
    
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
    
    static int indexTrame = 0;
    bool retour = false;
    
    // � compl�ter
    
    
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