#include <xc.h>
#include "NeoCol.h"
#include <stdlib.h>
#include <stdint.h>




//unsigned int8 NeoGreen [NeoNum];
//unsigned int8 NeoBlue [NeoNum];
//unsigned int8 NeoRed [NeoNum];

uint8_t NeoGreen [NeoNum];
uint8_t NeoBlue [NeoNum];
uint8_t NeoRed [NeoNum];



//void NeoBit(__bit Bit)
void NeoBit(uint8_t Bit)
{
//    Bit = 1;
//    while(1)
//    {
   if (Bit != 0)
   { 
      NeoPin = 1; // output_high (NeoPin); 
      Nop();//__delay_cycles (6); 
      Nop(); // 1 Nop() = 100nSec
      Nop();       
      Nop(); // 1 Nop() = 100nSec
      Nop();       
      Nop(); // 1 Nop() = 100nSec
      Nop();       
      

      

      NeoPin = 0; //output_low (NeoPin); 
   } // delay_cycles (3); // Bit '1'   
   else
   { 
       NeoPin = 1; //output_high (NeoPin); 
       Nop();//__delay_cycles (3); 
       Nop(); // 1 Nop() = 100nSec
       Nop();       
       
       
       NeoPin = 0; //output_low (NeoPin); 
   } // delay_cycles (6); // Bit '0'   
   // }
}
void NeoInit (void)
{
   uint8_t NeoPixel;
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)   
   {
      if (NeoPixel < 2)
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 64; } //2 del en rouge
      else if ((NeoPixel >= 2) & (NeoPixel < 4))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 0; } //2 del en bleu
      else if ((NeoPixel >= 4) & (NeoPixel < 6))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 64; } //2 del en violet
      else if ((NeoPixel >= 6) & (NeoPixel < 8))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; } //2 del en vert
      else if ((NeoPixel >= 8) & (NeoPixel < 10))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 64; } //2 del en jaune
      else if ((NeoPixel >= 10) & (NeoPixel < NeoNum))
         { NeoGreen[NeoPixel] = 64; NeoBlue[NeoPixel] = 64; NeoRed[NeoPixel] = 0; } //2 del en cian
   }
}
void NeoDraw (void)
{
   uint8_t NeoPixel;
   int8_t BitCount;
   
/*   while(1)
   {
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         NeoBit(bit_test(NeoGreen[NeoPixel], BitCount));      
       
   }*/
   
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
   {    
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         NeoBit(bit_test(NeoGreen[NeoPixel], BitCount));      
      for (BitCount = 7; BitCount >= 0; BitCount--)           
         NeoBit(bit_test(NeoRed[NeoPixel], BitCount));            
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         NeoBit(bit_test(NeoBlue[NeoPixel], BitCount));      
   }
   NeoPin = 0;// output_low (NeoPin);
}
void NeoRotate (void)
{
   uint8_t NeoPixel;   
   for (NeoPixel = 0; NeoPixel < NeoNum - 1; NeoPixel++)   
   {           
      NeoGreen[NeoPixel] = NeoGreen[NeoPixel + 1];
      NeoBlue[NeoPixel] = NeoBlue[NeoPixel + 1];
      NeoRed[NeoPixel] = NeoRed[NeoPixel + 1];
   }
   NeoGreen[NeoNum - 1] = NeoGreen[0];
   NeoBlue[NeoNum - 1] = NeoBlue[0];
   NeoRed[NeoNum - 1] = NeoRed[0]; 
}


/*void main()
{   
   NeoInit ();   
   while(true)
   {       
      NeoDraw ();
      NeoRotate ();
      delay_ms (25);
   }
 
}*/
