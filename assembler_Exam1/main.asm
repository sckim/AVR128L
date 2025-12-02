;
; assembler_Exam1.asm
;
; Created: 2021-10-02 오후 12:16:17
; Author : Soochan Kim
;
; Source: http://www.avr-asm-tutorial.net/avr_en/micro_beginner/3_Led_Blinking/3_Led_Blinking.html
;

; Replace with your application code

;start:
;    inc r16
;    rjmp start
/*
.equ cCounter = 250 ; (no code)

Setup:
	sbi DDRB,DDB5 ; PB0 as output, driver stage on, 2 clock cycles

Loop:
	cbi PORTB,PB5 ;LED on, 2 clock cycles
	;nop ; do nothing, 1 clock cycle
	;nop ; do nothing, 1 clock cycle
	/*
	ldi R16, cCounter ; 1 clock once executed
Delay:
	dec R16 ; 1 clock 250 times executed
	brne Delay ; 2 clock 249 times executed, 1 clock once executed
	*/

	sbi PORTB,PB5 ; LED off, 2 clock cycles
	rjmp Loop ; Jump relative back to label Loop, 2 clock cycles*/

; DDRB       = 0x04
; PORTB      = 0x05
; TCCR0B     = 0x25
; TCNT0      = 0x26

setup:
    ldi r16, (1<<PB5)       ; Set r16 to LED ON value
    out DDRB, r16           ; Set DDRB to output
    out PORTB, r16          ; Set PORTB to ON
    ldi r16, 0b00000101     ; Set r16 with prescaler 1024 value
    out TCCR0B, r16           ; Set the TCCROB to 1024
    ldi r20, 0              ; Reset r20
    ldi r21, 1              ; Hold value 1 to increment r20

loop:
    in r17, TCNT0            ; Read the timer 
    cpi r17, 128            ; Check to see if the timer is halfway done (1/2 second, max 255 value)
    brbc 0, increment       ; If r17 <= 128 (max 255 val before resets to 0), invert current LED state
    rjmp loop
increment:
    adc r20, r21            ; Add r21 (1) to r20 (with carry)
    brbs 0, reset           ; If the carry branch is set, reset the register
    rjmp loop               ; Otherwise, run the clock
reset:
    ldi r20, 0              ; Reset the delay register
    cpi r16, 0b00000000     ; Check if r16 is set to LED OFF
    brbs 1, switchon        ; If it is, change it to ON
    ldi r16, 0b00000000     ; Otherwise, change it to OFF
    out PORTB, r16           ; Set the LED to the new state
    rjmp loop               ; Run the clock
switchon:
    ldi r16, (1<<PB5)       ; Set r16 to LED ON value
    out PORTB, r16          ; Set the LED to the new state
    rjmp loop               ; Run the clock
	