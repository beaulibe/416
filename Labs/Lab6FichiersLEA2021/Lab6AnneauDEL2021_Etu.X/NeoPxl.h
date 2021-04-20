#ifndef NEOPXL_H
#define NEOPXL_H

#include <stdint.h>

#define NEO_PIN PORTDbits.RD0 
#define NEO_NUM 12 //Anneau de 12 DEL 

/****** Prototypes *********/
void NeoDraw (void);
void NeoSetColor(uint8_t R, uint8_t G, uint8_t B);


#endif