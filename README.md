# uC_examples
Microcontroller AVR128을 이용한 예제입니다.
강의 자료와 소스 코드는 계속 올리도록 하겠습니다.

## 강의 개요
+ 마이크로시스템설계
+ Email: sckim@hknu.ac.kr

## 강의 구성 
### 1주차: 마이크로컨트롤러란? 

### 2주차: 개발환경구축
+ AVR Studio ([Ver 7](http://www.microchip.com/mplab/avr-support/atmel-studio-7), [Ver 4.19](https://www.dropbox.com/s/8r5c4nze87vfh6r/AvrStudio4Setup.exe?dl=0))
+ Eclipse for AVR
+ [AVRToolchain](https://www.dropbox.com/s/7j8wxu1b2sp6b6n/AVR-Toolchain_330710.exe?dl=0)
+ [WinAVR](https://sourceforge.net/projects/winavr/files/)
+ [Training Boar Kit](https://docs.google.com/document/d/1z8ZOeDaLLHn7CCoW8pkEYocl6X6kjT0bNDkCtDhy2is/edit#heading=h.ewk21ulbo3a9)
+ [필수프로그램](https://www.dropbox.com/s/invxn9zygupyc5h/Core.zip?dl=0)

### 3주차: 범용 입/출력
+ [GPIO 출력](https://github.com/sckim/uC_examples/blob/master/10_Blink/Blink.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
+ [GPIO 입력](https://github.com/sckim/uC_examples/blob/master/20_Input_LED/Input.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
+ Debounce

### 4주차: 범용 입력 
+ [4x3 Keypad 입력](https://github.com/sckim/uC_examples/blob/master/25_Keypad/Keypad.c), [회로도](https://github.com/sckim/uC_examples/blob/master/25_Keypad/Keypad.DSN)

### 5주차: 외부 인터럽트 
+ [Interrupter를 사용한 버튼 입력](https://github.com/sckim/uC_examples/blob/master/27_Interrupt/Interrupt.c)
+ [2개 이상의 인터럽트](https://github.com/sckim/uC_examples/blob/master/29_Interrupts/Interrupt.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)

### 6주차: 디스플레이장치 (7Segments) 
+ [7Segments 사용하기](https://github.com/sckim/uC_examples/blob/master/14_7Segments/16_7Segments.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
+ [4개의 7Segments 사용하기](https://github.com/sckim/uC_examples/blob/master/48_Four7Segments_itoa/Four7Segments.c), [회로도](https://github.com/sckim/uC_examples/blob/master/48_Four7Segments_itoa/Four7Segments.DSN)

### 6주차: 디스플레이장치 (LCD) 
+ [Text LCD 사용하기](https://github.com/sckim/uC_examples/blob/master/62_textLCD/textLCD.c)
+ [LCD 함수 이용해서 제어](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/textLCDLib.c), [회로도](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/textLCDLib.DSN), [lcd_lib.c](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/lcd_lib.c), [lcd_lib.h](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/lcd_lib.h)

### 7주차: Analog to Digital 
+ [ADC 값을 부동소수점으로 출력하기](https://github.com/sckim/uC_examples/blob/master/101_ADC_on_LCD/ADC_on_LCD.c), [회로도](https://github.com/sckim/uC_examples/blob/master/101_ADC_on_LCD/ADC.DSN)

### 8주차: Timer
+ [Timer 0 Overflow 인터럽트 활용](https://github.com/sckim/uC_examples/blob/master/105_ADC_on_LCD_Timer/ADC_on_LCD_Timer.c)
+ [Timer 0 Ouput match 인터럽트 활용](https://github.com/sckim/uC_examples/blob/master/107_ADC_on_LCD_OCR/ADC_on_LCD_OCR.c)
+ Timer 2
+ [회로도](https://github.com/sckim/uC_examples/blob/master/101_ADC_on_LCD/ADC.DSN)

### 9주차: Timer (PWM)
+ Timer 1, 3

### 10주차: Serial communicate (UART)
### 11주차: SPI
### 12주차: I2C
### 13주차: 디스플레이장치 (Graphic LCD) 
### 14주차: WatchDog

### 16주차: 키트 직접 만들어보기
+ 부트로더

## 참고자료
+ 즐기면서 익히는 uC (자체자료)
+ AVR128.pdf ([Dropbox](https://www.dropbox.com/s/460vims4vl766m7/Atmega128L.pdf?dl=0), [Web](http://ww1.microchip.com/downloads/en/DeviceDoc/doc2467.pdf))
+ [BerkeleyX: EE40LX Electronic Interfaces](https://courses.edx.org/courses/course-v1:BerkeleyX+EE40LX+2T2015/info)
+ [AVR Programming Tutorial](http://ocw.mit.edu/courses/media-arts-and-sciences/mas-962-special-topics-new-textiles-spring-2010/readings-lectures-tutorials/tut06_avr1/)
+ [Atmega 128 레지스터](https://docs.google.com/document/d/1DUKQ7cIUKSunolqK0z9ITNyI9KXj2wUplr7f02rLgaM/edit)
