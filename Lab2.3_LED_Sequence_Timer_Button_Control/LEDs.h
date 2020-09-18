/*
 * LEDs.h
 *
 *  Created on: Sep 13, 2020
 *      Author: RenzoGarzaMotta
 */

#ifndef LEDS_H_
#define LEDS_H_


void LED_init(void);
void LED_blink(void);
void sequence(void);
void turnOn(uint8_t LED);
void turnOff(uint8_t LED);


#endif /* LEDS_H_ */
