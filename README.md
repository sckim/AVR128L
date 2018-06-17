# uC_examples
Microcontroller AVR128을 이용한 예제입니다.
강의 자료와 소스 코드는 계속 올리도록 하겠습니다.

## 강의 개요
+ 마이크로시스템설계
+ Email: sckim@hknu.ac.kr

## 강의 구성 
### 1주차: 마이크로컨트롤러란? 
### 2주차: 개발환경구축
+ AVR Studio 4.x
+ Eclipse for AVR
### 3주차: 범용 입/출력
+ [GPIO 출력](https://github.com/sckim/uC_examples/blob/master/10_Blink/Blink.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
+ [GPIO 입력](https://github.com/sckim/uC_examples/blob/master/20_Input_LED/Input.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
+ Debounce
### 4주차: 범용 입력 
+ [4x3 Keypad 입력](https://github.com/sckim/uC_examples/blob/master/25_Keypad/Keypad.c), [회로도](https://github.com/sckim/uC_examples/blob/master/25_Keypad/Keypad.DSN)
+ Debounce
### 5주차: 외부 인터럽트 
+ [Interrupter를 사용한 버튼 입력](https://github.com/sckim/uC_examples/blob/master/27_Interrupt/Interrupt.c)
+ [2개 이상의 인터럽트](https://github.com/sckim/uC_examples/blob/master/29_Interrupts/Interrupt.c)
+ [관련회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
### 6주차: 디스플레이장치 (7Segments) 
+ [7Segments 사용하기](https://github.com/sckim/uC_examples/blob/master/14_7Segments/16_7Segments.c), [회로도](https://github.com/sckim/uC_examples/blob/master/10_Blink/AVR128_LED_7Seg.DSN)
+ [4개의 7Segments 사용하기](https://github.com/sckim/uC_examples/blob/master/48_Four7Segments_itoa/Four7Segments.c), [회로도](https://github.com/sckim/uC_examples/blob/master/48_Four7Segments_itoa/Four7Segments.DSN)
### 6주차: 디스플레이장치 (LCD) 
+ [Text LCD 사용하기](https://github.com/sckim/uC_examples/blob/master/62_textLCD/textLCD.c)
+ [LCD 함수 이용해서 제어](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/textLCDLib.c), [회로도](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/textLCDLib.DSN), [lcd_lib.c](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/lcd_lib.c), [lcd_lib.h](https://github.com/sckim/uC_examples/blob/master/68_textLCDLib/lcd_lib.h)
### 7주차: ADC 
### 8주차: Timer
### 9주차: 디스플레이장치 (LCD) 
### 10주차: 디스플레이장치 (7Segments) 
### 11주차: Serial communicate (UART)
### 12주차: SPI
### 13주차: I2C
### 14주차: WatchDog
### 15주차: Timer (PWM)
### 16주차: 키트 직접 만들어보기
+ 부트로더

## 참고자료
+ [BerkeleyX: EE40LX Electronic Interfaces](https://courses.edx.org/courses/course-v1:BerkeleyX+EE40LX+2T2015/info)
+ [AVR Programming Tutorial](http://ocw.mit.edu/courses/media-arts-and-sciences/mas-962-special-topics-new-textiles-spring-2010/readings-lectures-tutorials/tut06_avr1/)
