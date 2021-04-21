/**
 * @file   interrupts.c, projet FinalNo3
 * @author Benoit Beaulieu
 * @date   avril 2021
 * @brief  No 3 de l'examen final du cours 247-416
  */
#include <xc.h>


void __interrupt(high_priority) high_isr(void)
{
    //unsigned char tab[] = {0xAA55, 0x55AA, 0xAA55, 0x55AA, 0x03C0, 0x0660,0x0C30};
    unsigned char tab[] = {0x18, 0x3C, 0x66,0xC3, 0x81};
    static int indexTab=0;


    if (PIR1bits.TMR1IF) // timer 1
    {
        PORTD = tab[indexTab];
        PIR1bits.TMR1IF   = 0;    // rst flag de l'interruption
        TMR1 = 9286;
        indexTab = (indexTab+ 1) % 5 ;
    }
    
    if (PIR2bits.TMR3IF) // timer 3
    {
        PIR2bits.TMR3IF = 0;   // rst flag de l'interruption
        TMR3 = 53036;         

        PORTD = (unsigned char) (PORTD << 1);
        if (PORTD == 0) 
            PORTD = 1;
    }
        
}

 



