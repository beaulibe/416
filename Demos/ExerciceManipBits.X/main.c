 /**
 * @file   main.c, projet ExerciceManipBits
 * @author Benoit Beaulieu
 * @date   Avril 2021
 * @breif  Exercices sur les masques et la manipulation des octets et des bits dans les variables.
*/
#include <xc.h>


void main(void)
{
    unsigned char v1 = 0x12;
    unsigned char v2 = 0x34;
    unsigned char v3 = 0;
    unsigned int vt = 0xABCD;
    
    TRISD = 0;
    PORTD = 0xA5; //valeur arbritaire pour tester le résultat

    //#1 Met à 1 les bits 7 et 0, sans changer les autres bits du port D
    PORTD = PORTD | 0b10000001;

    PORTD = 0xF0;
    //#2 Met à 0 les bits 4 et 3, sans changer les autres bits du port D
    PORTD = PORTD & 0b11100111;

    
    PORTD = 0xA5; //valeur arbritaire pour tester le résultat
    //#3 Inverser les 4 lsb et les 4 msb du PORTD
    PORTD = (PORTD >> 4) | (unsigned char)(PORTD << 4);
    
    v1 = 0x12;
    v2 = 0x34;

    //#4 On veut v3 = 0x14 
    v3 = (v1&0xF0) | (v2&0x0F);

    //#5 On veut v3 = 0x24;
    v3 = (unsigned char)(v1<<4) | (v2&0x0F);

    //#6 On veut v3 = 0x41;
    v3 = (v1>>4) | (unsigned char)(v2<<4);
    
    vt = 0xABCD;
    //7 On veut v3 = 0xCB;
    v3 = ((vt&0x0F00)>>8) | (vt & 0x00F0) ;

    
    //#8 On veut vt = 0x4231;
    //Faire la démarches avec une ligne de code par opération
    vt = (unsigned int)(v2<<12);
    vt = (vt & 0xF0FF) | ((unsigned int)(v1 << 8) & 0x0F00);
    vt = (vt & 0xFF0F) | (v2 & 0xF0);
    vt = (vt & 0xFFF0) | (v1 >> 4);
    
    vt = 0;
    //#9 On veut vt = 0x4231;
    //Faire en une seule ligne de code
     
    vt = (unsigned int)(v2<<12) | 
         ((unsigned int)(v1 << 8) & 0x0F00) | 
         (v2 & 0xF0) | (v1 >> 4);
    
    
    while(1);
    
    
}


