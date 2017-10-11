#include <avr/io.h>
#include <stdint.h>

/* Which analog pin we want to read from.  The pins are labeled "ADC0"
 * "ADC1" etc on the pinout in the data sheet.  In this case ADC_PIN
 * being 0 means we want to use ADC0.  On the ATmega328P this is also
 * the same as pin PC0 */
#define ADC_PIN			0
#define	LED_PIN			PB0

#define ADC_THRESHOLD	512

uint16_t adc_read(uint8_t adcx) {
	/* adcx is the analog pin we want to use.  ADMUX's first few bits are
	 * the binary representations of the numbers of the pins so we can
	 * just 'OR' the pin's number with ADMUX to select that pin.
	 * We first zero the four bits by setting ADMUX equal to its higher
	 * four bits. */
	ADMUX	&=	0xf0;
	ADMUX	|=	adcx;

	/* This starts the conversion. */
	ADCSRA |= _BV(ADSC);

	/* This is an idle loop that just wait around until the conversion
	 * is finished.  It constantly checks ADCSRA's ADSC bit, which we just
	 * set above, to see if it is still set.  This bit is automatically
	 * reset (zeroed) when the conversion is ready so if we do this in
	 * a loop the loop will just go until the conversion is ready. */
	while ( (ADCSRA & _BV(ADSC)) );

	/* Finally, we return the converted value to the calling function. */
	return ADC;
}

int main(void) {

	/* Enable the ADC */
	ADCSRA |= _BV(ADEN);

	/* Set the LED pin as an output. */
	DDRB  |= _BV(LED_PIN);


	/* continually check if the ADC value is greater than the
	 * defined ADC_THRESHOLD value above.  If it is turn the LED on,
	 * if it isn't turn it off. */
	for (;;) {

		if (adc_read(ADC_PIN) > ADC_THRESHOLD)
			PORTB |= _BV(LED_PIN);
		else
			PORTB &= ~_BV(LED_PIN);

    }

}
