/*
 * File:   main.c
 * Author: Benoit
 *
 * Created on 18 février 2020, 15:59
 */


#include <xc.h>
#include "NeoCol.h"
#include <stdbool.h>

/****** Constantes ************/
#define _XTAL_FREQ 40000000 //Constante utilisée par delaisMS(x). Doit = fréq interne du uC


void main(void) 
{

    TRISD = 0; //NeoPin sur RD0. On met tout le port en sortie.
    NeoInit();   
    NeoDraw ();    
    while(true)
        
    {       
    //  NeoDraw ();
     // NeoRotate ();
      __delay_ms(25);
    }

    return;
}
