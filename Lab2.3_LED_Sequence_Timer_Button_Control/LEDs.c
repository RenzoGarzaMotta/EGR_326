/*
 * LEDs.c
 *
 *  Created on: Sep 13, 2020
 *      Author: RenzoGarzaMotta
 */
#include "msp.h"
#include "SysTick.h"
#include "Macros.h"
#include "Buttons.h"
#include "LEDs.h"

extern int blink;
extern int click;
extern int LEDstate;

void LED_init(void){
    LED_PORT->SEL0 &=~ LEDS;    //Default function
    LED_PORT->SEL1 &=~ LEDS;
    LED_PORT->DIR |= LEDS;      //LEDS bits as outputs
    LED_PORT->OUT &=~ LEDS;     //LEDs Off
}

void turnOn(uint8_t LED){
    LED_PORT->OUT |= LED;   //Turn on LED

}

void turnOff(uint8_t LED){
    LED_PORT->OUT &=~ LED;  //Turn off LED
}

void sequence(void){
    //SysTick->VAL = 0;
    switch(LEDstate){
        case RED:
            turnOn(RED_LED);
            turnOff(GREEN_LED);
            turnOff(BLUE_LED);
            //msDelay(1000);
            break;
        case GREEN:
            turnOff(RED_LED);
            turnOn(GREEN_LED);
            turnOff(BLUE_LED);
            //msDelay(1000);
            break;
        case BLUE:
            turnOff(RED_LED);
            turnOff(GREEN_LED);
            turnOn(BLUE_LED);
            //msDelay(1000);
            break;
    }
}

void  LED_blink(void){
    int sec = 500;
    turnOff(RED_LED);
    turnOff(GREEN_LED);
    turnOff(BLUE_LED);
    msDelay(sec);
    switch(LEDstate){
        case RED:
            turnOn(RED_LED);
            turnOff(GREEN_LED);
            turnOff(BLUE_LED);
            msDelay(sec);
            break;
        case GREEN:
            turnOff(RED_LED);
            turnOn(GREEN_LED);
            turnOff(BLUE_LED);
            msDelay(sec);
            break;
        case BLUE:
            turnOff(RED_LED);
            turnOff(GREEN_LED);
            turnOn(BLUE_LED);
            msDelay(sec);
            break;
    }
}



