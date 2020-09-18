/*
 * Buttons.h
 *
 *  Created on: Sep 13, 2020
 *      Author: RenzoGarzaMotta
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "msp.h"

void buttonInit(void);
int CHECK(uint8_t BUTTON);
uint8_t debounceUP(void);
uint8_t debounceDOWN(void);

#endif /* BUTTONS_H_ */
