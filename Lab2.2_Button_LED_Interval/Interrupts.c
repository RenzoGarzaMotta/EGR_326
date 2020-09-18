#include "msp.h"
#include "Interrupts.h"
#include "Macros.h"
#include "Buttons.h"
#include "LEDs.h"


extern int blink;
extern int click;
extern int LEDstate;


void NonMaskableInt_IRQHandler(void){

}

void HardFault_IRQHandler(void){

}

void MemoryManagement_IRQHandler(void){

}

void BusFault_IRQHandler(void){

}

void UsageFault_IRQHandler(void){

}

void SVCall_IRQHandler(void){

}

void DebugMonitor_IRQHandler(void){

}

void PendSV_IRQHandler(void){

}

/****************************************************************
*                       SysTick_Handler                         *
*    USE THIS TO DEFINE INTERRUPT SEQUENCE THAT YOU DESIRE YOUR *
*CODE TO FOLLOW.                                                *
****************************************************************/
void SysTick_Handler(void){
    if(CHECK(BUTTON)){
        sequence();
        SysTick->LOAD = (1000 * 3000) - 1;  //Lead 1 sec to the SysTick Timer
    }
}

void PSS_IRQHandler(void){

}

void CS_IRQHandler(void){

}

void PCM_IRQHandler(void){

}

void WDT_IRQHandler(void){

}

void FPU_IRQHandler(void){

}

void FLCTL_IRQHandler(void){

}

void COMP_E0_IRQHandler(void){

}

void COMP_E1_IRQHandler(void){

}

void TA0_0_IRQHandler(void){

}

void TA0_1_IRQHandler(void){

}

void TA0_2_IRQHandler(void){

}

void TA0_3_IRQHandler(void){

}

void TA0_4_IRQHandler(void){

}

void TA1_0_IRQHandler(void){

}

void TA1_1_IRQHandler(void){

}

void TA1_2_IRQHandler(void){

}

void TA1_3_IRQHandler(void){

}

void TA1_4_IRQHandler(void){

}

void TA2_0_IRQHandler(void){

}

void TA2_1_IRQHandler(void){

}

void TA2_2_IRQHandler(void){

}

void TA2_3_IRQHandler(void){

}

void TA2_4_IRQHandler(void){

}

void TA3_0_IRQHandler(void){

}

void TA3_1_IRQHandler(void){

}

void TA3_2_IRQHandler(void){

}

void TA3_3_IRQHandler(void){

}

void TA3_4_IRQHandler(void){

}

void EUSCIA0_IRQHandler(void){

}

void EUSCIA1_IRQHandler(void){

}

void EUSCIA2_IRQHandler(void){

}

void EUSCIA3_IRQHandler(void){

}

void EUSCIB0_IRQHandler(void){

}

void EUSCIB1_IRQHandler(void){

}

void EUSCIB2_IRQHandler(void){

}

void EUSCIB3_IRQHandler(void){

}

void ADC14_IRQHandler(void){

}

void T32_INT1_IRQHandler(void){

}

void T32_INT2_IRQHandler(void){

}

void T32_INTC_IRQHandler(void){

}

void AES256_IRQHandler(void){

}

void RTC_C_IRQHandler(void){

}

void DMA_ERR_IRQHandler(void){

}

void DMA_INT3_IRQHandler(void){

}

void DMA_INT2_IRQHandler(void){

}

void DMA_INT1_IRQHandler(void){

}

void DMA_INT0_IRQHandler(void){

}

void PORT1_IRQHandler(void){
    if(BUTTON_PORT->IFG & BUTTON){
        if(CHECK(BUTTON)){
            click++;
            do{
                sequence();
            }while(CHECK(BUTTON));
        }
    }
    BUTTON_PORT->IFG = 0;
}

void PORT2_IRQHandler(void){

}

void PORT3_IRQHandler(void){

}

void PORT4_IRQHandler(void){

}

void PORT5_IRQHandler(void){

}

void PORT6_IRQHandler(void){

}
