; --- Piano2.asm ----
; When you press button RB0..RB3, you play a note
; on RC0:
;   RB0:  261 Hz (C4)
;   RB1:  293 Hz (D4)
;   RB2:  329 Hz (E4)
;   RB3:  349 Hz (F4)

#include <p18f4620.inc>

; Variables
CNT0 EQU 1
CNT1 EQU 2

; Program
	org 0x800
	call Init
Loop:
    movf  PORTB,F	; if any button is pressed
	btfss STATUS,Z
	call Toggle		; Drive a speaker on RC0
	
	btfsc PORTB,0
	call  Wait_C4
	btfsc PORTB,1
	call  Wait_D4
	btfsc PORTB,2
	call  Wait_E4
	btfsc PORTB,3
	call  Wait_F4
	
	goto Loop

; --- Subroutines ---

Init:
	clrf TRISA  	;PORTA is output
    movlw 0xFF
	movwf TRISB 	;PORTB is input
	clrf TRISC 		;PORTC is output
	clrf TRISD 		;PORTD is output
	clrf TRISE 		;PORTE is output
	movlw 15
	movwf ADCON1 	;everyone is binary
    clrf  PORTD
    clrf  PORTC
    clrf  PORTB
    clrf  PORTA
	return

Toggle:
	btg 	PORTC,0
	return

Wait_C4: ; Wait 19,157 clocks
	movlw 8
	movwf CNT1
Loop1c:
	movlw 239
	movwf CNT0
Loop0c:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz CNT0,F
	goto Loop0c
	decfsz CNT1,F
	goto Loop1c
	return


Wait_D4: ; Wait 17,064 clocks
	movlw 7
	movwf CNT1
Loop1d:
	movlw 243
	movwf CNT0
Loop0d:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz CNT0,F
	goto Loop0d
	decfsz CNT1,F
	goto Loop1d
	return


Wait_E4: ; Wait 15,197 clocks
	movlw 6
	movwf CNT1
Loop1e:
	movlw 253
	movwf CNT0
Loop0e:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz CNT0,F
	goto Loop0e
	decfsz CNT1,F
	goto Loop1e
	return

Wait_F4: ; Wait 14,326 clocks
	movlw 6
	movwf CNT1
Loop1f:
	movlw 239
	movwf CNT0
Loop0f:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz CNT0,F
	goto Loop0f
	decfsz CNT1,F
	goto Loop1f
	return
	end