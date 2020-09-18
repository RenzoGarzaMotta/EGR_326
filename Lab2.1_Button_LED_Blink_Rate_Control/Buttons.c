#include "msp.h"
#include "Buttons.h"
#include "SysTick.h"
#include "Macros.h"

void buttonInit(void){
    BUTTON_PORT->SEL0 &=~ BUTTONS;  //Use button bits primary function
    BUTTON_PORT->SEL1 &=~ BUTTONS;
    BUTTON_PORT->DIR &=~ BUTTONS;   //Set buttons as inputs
    BUTTON_PORT->REN |= BUTTONS;    //Enable MSP's internal resistor
    BUTTON_PORT->OUT |= BUTTONS;    //Set internal resistor as a pull-up

    BUTTON_PORT->IES |= BUTTONS;    //Interrupt Edge Select: (0)Low to High (1)High to Low
    BUTTON_PORT->IE |= BUTTONS;     //Enable interrupt for all buttons
    BUTTON_PORT->IFG = 0;           //Clear interrupt flag
}

/****************************************************************
*                      BUTTON CHECK FUNCTION                    *
*DEBOUNCES AND CHECKS THE STATE OF THE BUTTON TO DETERMINE USER *
*INPUT.                                                         *
*****************************************************************/
int CHECK(uint8_t BUTTON){
    int pressed = 0;
    do{
        msDelay(25);
        if((BUTTON_PORT->IN & BUTTON) == 0){            //CHECK TO SEE IF THE BUTTON IS PRESSED
            pressed = 1;                                //(IF BUTTON WAS PRESSED) FLAG THAT BUTTON WAS PRESSED
            if((BUTTON_PORT->IN & BUTTON) == 0){        //CHECK IF THE BUTTON IS STILL PRESSED
                pressed = 1;                            //CONFIRM BUTTON PRESSED
            }else{
                pressed = 0;
            }
        }else{
        }
    }while((BUTTON_PORT->IN & BUTTON) == 0);

    return pressed;
}


/****************************************************************
*                           debounceUP                          *
*****************************************************************/
uint8_t debounceUP(void){
    static uint16_t State = 0;
    State = (State << 1) | (BUTTON_PORT->IN & UP_BUTTON) >> 1 | 0xF800;
    __delay_cycles(5);
    if(State == 0xFC00) return 1;
    return 0;
}

/****************************************************************
*                           debounceDOWN                        *
*****************************************************************/
uint8_t debounceDOWN(void){
    static uint16_t State = 0;
    State = (State << 1) | (BUTTON_PORT->IN & DOWN_BUTTON) >> 1 | 0xF800;
    __delay_cycles(5);
    if(State == 0xFC00) return 1;
    return 0;
}
