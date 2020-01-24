/*
 * File:   main.c
 * Author: tge
 *
 * Created on 24 janvier 2020, 14:10
 */


#include <xc.h>

#define SW1 PORTBbits.RB0

struct moteur 
{
    int vitesse;
    int temperature;
    int courant;
};


void main(void)
{
    struct moteur stMotMoulin;

    stMotMoulin.vitesse = 100;
    stMotMoulin.temperature = 33;
    stMotMoulin.courant = 12;
    
    TRISD = 0; //Port D en sortie
    TRISBbits.RB0 = 1; //BR0 en entrée
    
    while (1)
    {
        PORTD = stMotMoulin.courant;
        if (SW1 == 0)
        {
            while (SW1 == 0);
            stMotMoulin.courant ++;
        }
    }


}
