/**
 ******************************************************************************
 * @file           : 3_IT_BTN_LED.c
 * @author         : Ayuba Tahiru
 * @date           : Oct 18, 2025
 * @target_mcu     : STM32F407VHT6
 * @toolchain      : STM32CubeIDE / GCC ARM Embedded
 ******************************************************************************
 * @attention
 * Copyright (c) 2025 Ayuba Tahiru
 * All rights reserved.
 *
 * This file is part of the Embedded-Hub project.
 * Redistribution or modification is permitted for educational use only.
 ******************************************************************************
 */


#include <stdint.h>
#include <string.h>
#include "../drivers/Inc/stm32f407xx.h"

void delay(void){
	for(uint32_t i = 0; i < 250000; i++){};
}

#define LOW			0
#define BTNPRESSED 	LOW

int main(void)
{	// LED Configuration
	GPIO_Handle_t GPIO_LED, GPIO_BTN;
//	memset(&GPIO_LED, 0, sizeof(GPIO_LED));


	GPIO_LED.pGPIOx = GPIOD;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_12;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_OUTPUT;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinOPType 		= GPIO_OTY_PUSPUL;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_NO;

	GPIO_PeriphControl(GPIOD, ENABLE);
	GPIO_Init(&GPIO_LED);

//	memset(&GPIO_BTN, 0, sizeof(GPIO_BTN));
	// Button Configuration
	GPIO_BTN.pGPIOx = GPIOA;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_0;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_INP_FE_T;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_PULUP;

	GPIO_PeriphControl(GPIOA, ENABLE);
	GPIO_Init(&GPIO_BTN);

//	GPIO_WriteOutputPin(GPIOD, GPIO_PIN_NO_12, GPIO_PIN_RESET);
	// IRQ Configuration

	GPIO_InterruptPriorityConfig(IRQ_EXTI0, NVIC_IRQ_PRIORITY_15);
	GPIO_InterruptConfig(IRQ_EXTI0, ENABLE);
//	GPIO_InterruptPriorityConfig(IRQ_EXTI9_5, NVIC_IRQ_PRIORITY_15);
//	GPIO_InterruptConfig(IRQ_EXTI9_5, ENABLE);

	while(1){

	}
	return 0;


}
// IRQ Handler

void EXTI0_IRQHandler(void){
	delay();
	GPIO_IRQHandler(GPIO_PIN_NO_0);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
//
}
//void EXTI9_5_IRQHandler(void){
//	delay();
//	GPIO_IRQHandler(GPIO_PIN_NO_5);
//	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
////
//}
