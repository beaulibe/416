#ifndef NEOPXL_H
#define NEOPXL_H


#define NeoPin PORTDbits.RD0 
#define NeoNum 12 //Anneau de 12 DEL 

/****** Prototypes *********/
void NeoInit (void);
void NeoDraw (void);


#endif