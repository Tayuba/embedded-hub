/**
 ******************************************************************************
 * @file           : 1_LED_Toggle.c
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

void delay(void){
	for(uint32_t i = 0; i < 100000; i++){};
}

int main(void)
{
	GPIO_Handle_t GPIO_LED;
	GPIO_LED.pGPIOx = GPIOD;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_12;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_OUTPUT;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinOPType 		= GPIO_OTY_PUSPUL;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_PULUP;

	GPIO_PeriphControl(GPIOD, ENABLE);
	GPIO_Init(&GPIO_LED);
    /* Loop forever */
	while(1){
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		delay();
	}
}
