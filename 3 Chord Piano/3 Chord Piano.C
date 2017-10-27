/*8 key, 3 note chord piano
Created by Bryce Suchy 4/10/2017
	RB0-RB7
*/

// Global Variables

const unsigned char MSG0[21] = "Chord 8 Key.C       "; 
const unsigned char MSG1[21] = "                    "; 
    
const unsigned int A4 = 11363;
const unsigned int G4 = 12755;
const unsigned int F4 = 14317;
const unsigned int E4 = 15168;
const unsigned int D4 = 17026;
const unsigned int C4 = 19110;
const unsigned int B3 = 20247;
const unsigned int A3 = 22727;

const unsigned int G3 = 25511;
const unsigned int F3 = 28635;
const unsigned int E3 = 30338;
const unsigned int D3 = 34053;
const unsigned int C3 = 38223;
const unsigned int B2 = 40496;
const unsigned int A2 = 45455;
const unsigned int G2 = 51026;

unsigned int N0, N1, N3;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// Interrupt Service Routine
void interrupt IntServe(void)
{
   if (TMR0IF) {
      TMR0 = -N0;
      if (PORTB) RC0 = !RC0;
      TMR0IF = 0;
      }
   if (TMR1IF) {
      TMR1 = -N1;
      if (PORTB) RC1 = !RC1;					
      TMR1IF = 0;
	
      }
   if (TMR2IF) {
	  if (RB0) { N0 = G2;  N1 = B2;  N3 = D3; }
      if (RB1) { N0 = A2;  N1 = C3;  N3 = E3; }
      if (RB2) { N0 = B2;  N1 = D3;  N3 = F3; }
      if (RB3) { N0 = C3;  N1 = E3;  N3 = G3; }
 	  if (RB4) { N0 = D3;  N1 = F3;  N3 = A3; }
	  if (RB5) { N0 = E3;  N1 = G3;  N3 = B3; }
      if (RB6) { N0 = F3;  N1 = A3;  N3 = C4; }
	  if (RB7) { N0 = G3;  N1 = B3;  N3 = D4; }
      TMR2IF = 0;
      }   
   if (TMR3IF) {
      TMR3 = -N3;
      if (PORTB) RC2 = !RC2;
      TMR3IF = 0;
      }
   }
   
void LCD_Out(unsigned int DATA, unsigned char N)
{
   unsigned char A[5], i;
   
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
   unsigned char i;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
   LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

   Wait_ms(100);

// set up Timer0 for PS = 1
   T0CS = 0;
   T0CON = 0x88;
   TMR0ON = 1;
   TMR0IE = 1;
   TMR0IP = 1;
   PEIE = 1;
// set up Timer1 for PS = 1
   TMR1CS = 0;
   T1CON = 0x81;
   TMR1ON = 1;
   TMR1IE = 1;
   TMR1IP = 1;
   PEIE = 1;
// set up Timer2 for 1ms
   T2CON = 0x4D;
   PR2   = 249;
   TMR2ON = 1;
   TMR2IE = 1;
   TMR2IP = 1;
   PEIE = 1;
// set up Timer3 for PS = 1
   TMR3CS = 0;
   T3CON = 0x81;
   TMR3ON = 1;
   TMR3IE = 1;
   TMR3IP = 1;
   PEIE = 1;
// turn on all interrupts
GIE = 1;

   while(1) {
      LCD_Move(1,0);  LCD_Out(N0, 0);
      LCD_Move(1,6);  LCD_Out(N1, 0);
      LCD_Move(1,12);  LCD_Out(N3, 0);
      }      
   }
