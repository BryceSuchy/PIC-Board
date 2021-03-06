// Stepper3.C

// Global Variables
const unsigned char MSG[16] = "Stepper4.C      ";
unsigned char TABLE[4] = {1, 2, 4, 8};
int REF, STEP, N, TIME, Begin, SPEED, DIR, X;

// Subroutine Declarations
#include <pic18.h>
#include "LCD_PortD.C"

// High-priority service
void interrupt IntServe(void)
{
   if (TMR2IF) {
      TIME = TIME + 1;
      
	 if (RB0) {Begin = 1; SPEED = 5;}
	 if (RB1) {Begin = 0; SPEED = 0;}
	 if (RB3) SPEED = 1;
	 if (RB4) SPEED = 50;
     if (RB5) SPEED = 70;
	 if (RB6) {SPEED = 90; X = 1;}
     if (RB7) {SPEED = 50; X = 1;}
			
      N = (N + 1) % SPEED;
 if (N == 0) {
 STEP = STEP + DIR;
 PORTC = TABLE[STEP % 4];
 }
      TMR2IF = 0;
      }

   }



void LCD_Out(int DATA, unsigned char N)
{
   unsigned char A[5], i;
   
   if (DATA < 0) {
      LCD_Write('-');
      DATA = -DATA;
   }
   else LCD_Write('+');
   
   for (i=0; i<5; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
   }
   for (i=5; i>0; i--) {
      if (i == N) LCD_Write('.');
      LCD_Write(A[i-1] + '0');
   }
}

        
// Main Routine

void main(void)
{
   int i;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   STEP = 0;
   REF  = 0;
   //int Begin = 0;
	
   
   LCD_Init();
   LCD_Move(0,0);
   for (i=0; i<16; i++) LCD_Write(MSG[i]);
   Wait_ms(1000);
   LCD_Inst(0x01);

// initialize Timer2

   T2CON = 0x4D;
   PR2 = 249;
   TMR2ON = 1;
   TMR2IE = 1;
   PEIE = 1;

   GIE = 1;


   while(1) {
      LCD_Move(0,0);   LCD_Out(TIME,3);
      LCD_Move(0,8);   LCD_Out(DIR,0);
      LCD_Move(1,8);   LCD_Out(STEP,0);
if(RB0) {
 while(Begin == 1) {
		
		DIR = 1;
		Wait_ms(700);
		DIR = -1;
		Wait_ms(700);

		if(RB7) {
			while(X == 1) {
			DIR = 1;
			Wait_ms(5000);
			DIR = -1;
			Wait_ms(5000);
}

	}

	}
      }     
}
}