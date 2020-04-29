#ifndef NEOPXL_H
#define NEOPXL_H

#include <stdint.h>

#define NeoPin PORTDbits.RD0 
#define NeoNum 12 //Anneau de 12 DEL 

/****** Prototypes *********/
void NeoInit (void);
void NeoDraw (void);
void NeoSetColor(uint8_t R, uint8_t G, uint8_t B);


#endif