/*
 * LEDs.c
 *
 *  Created on: Sep 13, 2020
 *      Author: RenzoGarzaMotta
 */
#include "msp.h"
#include "SysTick.h"
#include "Macros.h"
#include "LEDs.h"

extern float blinkRate;
extern int LEDstate;

void LED_init(void){
    LED_PORT->SEL0 &=~ LED;
    LED_PORT->SEL1 &=~ LED;
    LED_PORT->DIR |= LED;
    LED_PORT->OUT &=~ LED;
}

void turnOn(void){
    LED_PORT->OUT |= LED;

}

void turnOff(void){
    LED_PORT->OUT &=~ LED;
}

void  LED_blink(void){
    float halfPeriod = ((1 / blinkRate) / 2) * 1000;
    msDelay(halfPeriod);
    turnOn();
    msDelay(halfPeriod);
    turnOff();
}



