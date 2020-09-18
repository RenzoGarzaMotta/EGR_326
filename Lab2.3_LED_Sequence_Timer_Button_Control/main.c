#include "msp.h"
#include "Interrupts.h"
#include "LEDs.h"
#include "Macros.h"
#include "SysTick.h"
#include "Buttons.h"

int blink;
int LEDstate = 0;
int click = 0;

void GPIO_init(void);

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    GPIO_init();

    NVIC->ISER[1] = 1 << (PORT1_IRQn & 31);
    __enable_interrupt();

    while(1){
    }
}

void GPIO_init(void){
    sysTick_init();
    LED_init();
    buttonInit();
}
