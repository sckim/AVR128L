;
; asmBlink.asm
;
; Created: 2021-10-02 오후 1:36:30
; Author : Soochan Kim
;


; Replace with your application code
Setup:
    	sbi DDRB,DDB5 ; pinMode(PB5, HIGH)
 
Loop:
    	cbi PORTB,PB5 ; digitalWrite(PB5, LOW) 
    	sbi PORTB,PB5 ; digitalWrite(PB5, HIGH) 
    	rjmp Loop ; Jump relative back to label Loop, 2 clock cycles
