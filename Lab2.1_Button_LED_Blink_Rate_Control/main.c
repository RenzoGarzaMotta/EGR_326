#include "msp.h"
#include "Macros.h"
#include "Buttons.h"
#include "SysTick.h"
#include "Interrupts.h"
#include "LEDs.h"

void GPIO_init(void);


float blinkRate = 0;    //Blinking rate of LED in Hz

void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	GPIO_init();

	NVIC->ISER[1] = 1 << (PORT1_IRQn & 31);
	__enable_interrupt();

	while(1){
	    if(blinkRate > 0){
	        LED_blink();
	    }
	}
}

void GPIO_init(void){
    buttonInit();
    sysTick_init();
    LED_init();
}
