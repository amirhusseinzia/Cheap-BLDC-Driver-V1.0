#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include "string.h"
#include "stdio.h"

#include "sysclk.h"
#include "adc_dma.h"
#include "bldc.h"

int main(void)
{
	// Set clock
	SetSysClockTo72();
	// ADC Init
	ADC_DMA_init();
	// TIM1, outputs, inputs, interrupts, etc. Init
	BLDC_Init();


    while(1)
    {
    	if (1 > BLDC_ADC_START) {
    		if (BLDC_MotorGetSpin() == BLDC_STOP) {
    			
    			BLDC_MotorSetSpin(BLDC_CW);
    			
    			BLDC_MotorCommutation(BLDC_HallSensorsGetPosition());
    		}
    		BLDC_SetPWM(BLDC_ADCToPWM(ADCBuffer[0]));
    	}
    	else {
    		if (BLDC_MotorGetSpin() != BLDC_STOP) {
    			if (0 < BLDC_ADC_STOP) {
    				//BLDC_MotorStop();
    			}
    		}
    	}
    }
}
