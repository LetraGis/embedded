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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #error "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "bsp.h"

uint32_t stack_blinky1[40] __attribute__ ((aligned (8)));
OSThread blinky1;
void main_blinky1() {
   	while (1) {
       	Gpio_TogglePinState(porta, pin5);
       	OS_delay(BSP_TICKS_PER_SEC);
   	}
}

uint32_t stack_blinky2[40] __attribute__ ((aligned (8)));
OSThread blinky2;
void main_blinky2() {
   	while (1) {
       	Gpio_TogglePinState(porta, pin6);
       	OS_delay((BSP_TICKS_PER_SEC * 7U) / 3U);
   	}
}

uint32_t stack_idleThread[40] __attribute__ ((aligned (8)));

int main(void)
{
	Gpio_Init();
	OS_Init(&stack_idleThread, sizeof(stack_idleThread));

	OSThread_Start(&blinky1,
			&main_blinky1,
			11U,
			&stack_blinky1[0], sizeof(stack_blinky1));

	OSThread_Start(&blinky2,
				&main_blinky2,
				5U,
				&stack_blinky2[0], sizeof(stack_blinky2));

	OS_Run();
}
