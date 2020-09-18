/************************************************************************
*Author: RENZO GARZA MOTTA                                              *
*Date: Sept 11th, 2020                                                  *
*Class: EGR 326 Embedded System Design                                  *
*Section: 903                                                           *
*Assignment: Lab 1 Input Interfacing with the MSP432 Using Interrupts   *
*Part: 2                                                                *
*Description:                                                           *
*This program interfaces two pushbutton switches to control an LED color*
*sequence as well as an implementation of a debounce function           *
************************************************************************/

/****************************************************************
*                         PREPROCESSORS                         *
*****************************************************************/
#include <stdio.h>
#include "msp.h"
#include "Systick.h"

/****************************************************************
*                       MACRO DEFINITION                        *
*****************************************************************/
#define PORT        0xFF    //Reference to an entire port (8 bits)
#define LED_PORT    P2      //Reference to the port LEDs are connected to
#define RED_LED     BIT0    //Bit of the Red led
#define GREEN_LED   BIT1    //Bit of the Green led
#define BLUE_LED    BIT2    //Bit of the Blue led
#define LEDS        (RED_LED | GREEN_LED | BLUE_LED)    //Reference to the RGB Led
#define BUTTON_PORT P1      //Reference to the port buttons are connected to
#define FWD_BUTTON  BIT6    //Bit of the button that indicates forward LED sequence
#define BCK_BUTTON  BIT7    //Bit of the button that indicates backward LED sequence
#define BUTTONS     (FWD_BUTTON | BCK_BUTTON)   //Reference to all buttons
#define RED         0   //Red state
#define GREEN       1   //Green state
#define BLUE        2   //Blue state

/****************************************************************
*                      VARIABLES DEFINITION                     *
*****************************************************************/
int click = 0;          //Variable determines the state of the LED sequence

/****************************************************************
*                 FUNCTION PROTOTYPE DEFINITION                 *
****************************************************************/
void GPIO_init(void);           //General Puspose Input Output (GPIO) initialization
void sequence(void);            //LED sequence
uint8_t debounceFWD(void);      //FWD_BUTTON Debounce
uint8_t debounceBCK(void);      //BCK_BUTTON Debounce
int CHECK(uint8_t BUTTON);      //Function Debounces and confirms button press
void turnOn(uint8_t LED);       //Turns on LED passed
void turnOff(uint8_t LED);      //Turns off LED passed
void toggle(uint8_t LED);       //Toggles LED passed

/****************************************************************
*                        MAIN DEFINITION                        *
*****************************************************************/
void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    GPIO_init();        //GPIO Initialization function call
    sysTick_init();     //Initialize Systick timer

    while(1){
        if(debounceFWD() /*CHECK(FWD_BUTTON) - Optional Debounce*/){
            switch(click){
                case RED:
                    click = GREEN;              //Move forward in the LED sequence
                    break;
                case GREEN:
                    click = BLUE;               //Move forward in the LED sequence
                    break;
                case BLUE:
                    click = RED;                //Move forward in the LED sequenceE
                    break;
            }
        }else if(debounceBCK() /*CHECK(BCK_BUTTON) - Optional Debounce*/){
            switch(click){
                case RED:
                    click = BLUE;               //Move backwards in the LED sequence
                    break;
                case GREEN:
                    click = RED;                //Move backwards in the LED sequence
                    break;
                case BLUE:
                    click = GREEN;              //Move backwards in the LED sequence
                    break;
            }
        }
        sequence();     //Proceed to light corresponding LEDs
    }
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
*                           debounceFWD                         *
*****************************************************************/
uint8_t debounceFWD(void){
    static uint16_t State = 0;
    State = (State << 1) | (BUTTON_PORT->IN & FWD_BUTTON) >> 1 | 0xF800;
    __delay_cycles(5);
    if(State == 0xFC00) return 1;
    return 0;
}

/****************************************************************
*                           debounceBCK                         *
*****************************************************************/
uint8_t debounceBCK(void){
    static uint16_t State = 0;
    State = (State << 1) | (BUTTON_PORT->IN & BCK_BUTTON) >> 1 | 0xF800;
    __delay_cycles(5);
    if(State == 0xFC00) return 1;
    return 0;
}

/****************************************************************
*                             sequence                          *
*LED Sequence to determine what LEDs need to be lit             *
*****************************************************************/
void sequence(void){
    switch(click){
        case RED:
            turnOff(GREEN_LED);
            turnOff(BLUE_LED);
            turnOn(RED_LED);
            break;
        case GREEN:
            turnOff(BLUE_LED);
            turnOff(RED_LED);
            turnOn(GREEN_LED);
            break;
        case BLUE:
            turnOff(RED_LED);
            turnOff(GREEN_LED);
            turnOn(BLUE_LED);
            break;
    }
}

/****************************************************************
*                              turnON                           *
*Function turn on LED bit by setting HIGH the bit passed.       *
*****************************************************************/
void turnOn(uint8_t LED){
    LED_PORT->OUT |= LED; //Turn on LED
}

/****************************************************************
*                             turnOff                           *
*Function turns off LED bit by setting LOW the bit passed.      *
*****************************************************************/
void turnOff(uint8_t LED){
    LED_PORT->OUT &=~ LED;  //Turn off LED
}

/****************************************************************
*                              toggle                           *
*Function toggles LED bit.                            *
*****************************************************************/
void toggle(uint8_t LED){
    LED_PORT->OUT ^= LED;   //Toggle LED
}

/****************************************************************
*                           GPIO_init                           *
*Function initializes the GPIO needed for this project.         *
*****************************************************************/
void GPIO_init (void){
    LED_PORT->SEL0 &=~ LEDS;    //Primary Function for LED_PORT
    LED_PORT->SEL1 &=~ LEDS;
    LED_PORT->DIR |= LEDS;      //Set LED pins as outputs
    LED_PORT->OUT &=~ LEDS;     //Initially Turn off LEDs

    BUTTON_PORT->SEL0 &=~ BUTTONS;  //Primary Function for BUTTON_PORT
    BUTTON_PORT->SEL1 &=~ BUTTONS;
    BUTTON_PORT->DIR &=~ BUTTONS;   //Set buttons as input
    BUTTON_PORT->REN |= BUTTONS;    //Enable Internal Resistor
    BUTTON_PORT->OUT |= BUTTONS;    //Set resistor as Pull-up
}
