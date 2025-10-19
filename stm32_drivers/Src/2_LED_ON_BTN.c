/**
 ******************************************************************************
 * @file           : 2_LED_ON_BTN.c
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
#include "../drivers/Inc/stm32f407xx.h"

#define HIGH		1
#define BTN_PRESSED 	HIGH

void delay(void){
	for(uint32_t i = 0; i < 250000; i++){};
}

int main(void)
{
	GPIO_Handle_t GPIO_LED, GPIO_BTN;
	GPIO_LED.pGPIOx = GPIOD;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_12;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_OUTPUT;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinOPType 		= GPIO_OTY_PUSPUL;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_PULUP;

	GPIO_BTN.pGPIOx = GPIOA;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_0;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_INPUT;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_NO;

	GPIO_PeriphControl(GPIOD, ENABLE);
	GPIO_Init(&GPIO_LED);
	GPIO_PeriphControl(GPIOA, ENABLE);
	GPIO_Init(&GPIO_BTN);
    /* Loop forever */
	while(1){
		if(GPIO_ReadInputPin(GPIOA, GPIO_PIN_NO_0 == BTN_PRESSED)){
			delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);

		}

	}
}
