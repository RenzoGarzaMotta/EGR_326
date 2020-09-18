/************************************************************************
*Author: RENZO GARZA MOTTA                                              *
*Date: Sept 11th, 2020                                                  *
*Class: EGR 326 Embedded System Design                                  *
*Section: 903                                                           *
*Assignment: Lab 1 Input Interfacing with the MSP432 Using Interrupts   *
*Part: 1                                                                *
*Description:                                                           *
*This program interfaces two pushbutton switches to control an LED color*
*sequence as well as an implementation of a debounce function           *
************************************************************************/

/****************************************************************
*                         PREPROCESSORS                         *
*****************************************************************/
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
#define RED         0       //Red state
#define GREEN       1       //Green state
#define BLUE        2       //Blue state

/****************************************************************
*                      VARIABLES DEFINITION                     *
*****************************************************************/
int click;          //Variable determines the state of the LED sequence

/****************************************************************
*                 FUNCTION PROTOTYPE DEFINITION                 *
****************************************************************/
void GPIO_init(void);           //General Puspose Input Output (GPIO) initialization
void sequenceFWD(void);         //LED sequence
int CHECK(uint8_t BUTTON);      //FUNCTION DEBOUNCES AND COMFIRMS A BUTTON PRESS
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
        if(CHECK(FWD_BUTTON)){ //Check if the button is pressed
            sequenceFWD();     //Proceed to light corresponding LEDs
        }
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
*                             sequence                          *
*LED Sequence to determine what LEDs need to be lit             *
*****************************************************************/
void sequenceFWD(void){
    switch(click){
    case RED:
        turnOff(BLUE_LED);     //(IF BUTTON IS PRESSED) TURN OFF BLUE_LED TO ENSURE THE LOOP STARTS WITH ONLY RED
        turnOn(RED_LED);       //TURN ON RED_LED
        click++;                    //INCREASE CLICK COUNTER TO SEE WHERE IN THE SEQUENCE WE ARE
        break;                      //IF NOTHING HAPPENS BREAK OUT OF THE SWITCH LOOP
    case GREEN:
        turnOff(RED_LED);      //(IF BUTTON IS PRESSED) TURN OFF RED_LED TO ENSURE THE LOOP STARTS WITH ONLY RED
        turnOn(GREEN_LED);     //TURN ON GREEN_LED
        click++;                    //INCREASE CLICK COUNTER TO SEE WHERE IN THE SEQUENCE WE ARE
        break;                      //IF NOTHING HAPPENS BREAK OUT OF THE SWITCH LOOP
    case BLUE:
        turnOff(GREEN_LED);    //(IF BUTTON IS PRESSED) TURN OFF RED_LED TO ENSURE THE LOOP STARTS WITH ONLY RED
        turnOn(BLUE_LED);          //TURN ON GREEN_LED
        click = 0;                  //RESET COUNTER TO RESTART SEQUENCE
        break;                      //IF NOTHING HAPPENS BREAK OUT OF THE SWITCH STATEMENT
    }
}

/****************************************************************
*                              turnON                           *
*Function turn on LED bit by setting HIGH the bit passed.       *
*****************************************************************/
void turnOn(uint8_t LED){
    LED_PORT->OUT |= LED;
}

/****************************************************************
*                             turnOff                           *
*Function turns off LED bit by setting LOW the bit passed.      *
*****************************************************************/
void turnOff(uint8_t LED){
    LED_PORT->OUT &=~ LED;
}

/****************************************************************
*                              toggle                           *
*Function toggles LED bit.                            *
*****************************************************************/
void toggle(uint8_t LED){
    LED_PORT->OUT ^= LED;
}

/****************************************************************
*                           GPIO_init                           *
*Function initializes the GPIO needed for this project.         *
*****************************************************************/
void GPIO_init (void){
    LED_PORT->SEL0 &=~ LEDS;
    LED_PORT->SEL1 &=~ LEDS;
    LED_PORT->DIR |= LEDS;
    LED_PORT->OUT &=~ LEDS;

    BUTTON_PORT->SEL0 &=~ FWD_BUTTON;
    BUTTON_PORT->SEL1 &=~ FWD_BUTTON;
    BUTTON_PORT->DIR &=~ FWD_BUTTON;
    BUTTON_PORT->REN |= FWD_BUTTON;
    BUTTON_PORT->OUT |= FWD_BUTTON;
}
