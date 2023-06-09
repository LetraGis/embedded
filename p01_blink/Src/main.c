/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

typedef uint32_t uint32;
typedef uint8_t uint8;

/* Setting up RCC addresses and offsets to enable GPIOA peripheral.
 * The register RCC_AHB1ENR is the one that will be used to enable
 * GPIOA peripheral (check page 172 for RCC register map).
 * The Green LED on STM32F446RE board is connected to this peripheral. */
#define RCC_REGISTER_BASE_ADDRESS (uint32)(0x40023800u)
#define RCC_AHB1ENR_OFFSET (0x30u)
#define RCC_AHB1ENR_ADDRESS (RCC_REGISTER_BASE_ADDRESS + RCC_AHB1ENR_OFFSET)

/* Setting up the corresponding bit (bit 0) for enabling GPIOA peripheral.
 * Refer to page 173 for more information. */
#define RCC_AHB1ENR_PORTA_EN_BIT (0x0u)
#define RCC_AHB1ENR_PORTA_EN_MASK (uint32)(1u << RCC_AHB1ENR_PORTA_EN_BIT)

/* Setting up GPIOA addresses and offsets to set GPIOD mode (Input/Output, etc)
 * and change the output register (to change PortA bits to HIGH/LOW). Go to
 * page 193 for more information. */
#define GPIOA_REGISTER_BASE_ADDRESS (uint32)(0x40020000u)
#define GPIOA_MODER_OFFSET (0x00u)
#define GPIOA_MODER_ADDRESS (GPIOA_REGISTER_BASE_ADDRESS + GPIOA_MODER_OFFSET)

/* Setting up bits to change GPIOA pin 5 mode. Ports have 16 pins (from 0 to
 * 15), and Green LED is connected to pin 5 in the board. Refer to page
 * 193 for more information. */
#define GPIOA_MODER_MODE_5_BIT_LOW (10u)
#define GPIOA_MODER_MODE_5_BIT_HIGH (11u)
#define GPIOA_MODER_MODE_5_MASK_LOW (1u << GPIOA_MODER_MODE_5_BIT_LOW)
#define GPIOA_MODER_MODE_5_MASK_HIGH (1u << GPIOA_MODER_MODE_5_BIT_HIGH)
#define GPIOA_MODER_MODE_5_CLEAR_MASK ~( GPIOA_MODER_MODE_5_MASK_HIGH | GPIOA_MODER_MODE_5_MASK_LOW )

/* Setting up address for GPIOA output data register (GPIOA_ODR), which
 * will be used to modify the state of the port A pins (HIGH/LOW).
 * Go to page 194 for more information. */
#define GPIOA_ODR_ADDRESS (GPIOA_REGISTER_BASE_ADDRESS + GPIOA_ODR_OFFSET)

/* Setting up the bit 5 masks on the Output Data Register, so we can
 * modify output of pin 5. */
#define GPIOA_ODR_OFFSET (0x14u)
#define GPIOA_ODR_DATA_BIT_5 (5u)
#define GPIOA_ODR_SET_BIT_5 (1u << GPIOA_ODR_DATA_BIT_5)
#define GPIOA_ODR_CLEAR_BIT_5 ~(1u << GPIOA_ODR_DATA_BIT_5)

volatile uint8 var1 = 0xFFu;
volatile const uint8 var2 = 0xFFu;
int a = -4000;
int b = 200;
int c = 0;

int main(void)
{
	c = a + b;
	volatile static uint8 var3 = 0xFFu;

	/* Pointer to RCCAHB1. Enabling GPIOA peripheral.  */
	uint32 * ptrRccAhb1Er = (uint32*)RCC_AHB1ENR_ADDRESS;
	*ptrRccAhb1Er |= RCC_AHB1ENR_PORTA_EN_MASK;

	/* Pointer to GPIOA_MODER. Clearing bits for pin 5,
	 * and then setting only low bit to HIGH, so
	 * combination will be 01 - which will set the pin
	 * as output. */
	uint32 * ptrGpioaModeR = (uint32*)GPIOA_MODER_ADDRESS;
	*ptrGpioaModeR &= (uint32)GPIOA_MODER_MODE_5_CLEAR_MASK;
	*ptrGpioaModeR |= (uint32)GPIOA_MODER_MODE_5_MASK_LOW;

	/* Pointer to GPIOA_ODR. Setting pin 5 as HIGH.
	 * Turning on LED. */
	uint32 * ptrGpioaOdr = (uint32*)GPIOA_ODR_ADDRESS;
	*ptrGpioaOdr |= GPIOA_ODR_SET_BIT_5;

	/* Loop forever */
	while(1)
	{
		uint32 index = 0;
		/* Delay loop before turning off the LED. */
		for(index = 0; index < 100000; index++);
		/* Turning off LED. */
		*ptrGpioaOdr &= ~(uint32)(GPIOA_ODR_SET_BIT_5);
		/* Delay loop before turning on the LED. */
		for(index = 0; index < 100000; index++);
		/* Turning on LED. */
		*ptrGpioaOdr |= GPIOA_ODR_SET_BIT_5;
	}

}
