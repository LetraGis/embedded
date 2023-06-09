/*
 * bsp.h
 *
 *  Created on: Nov 2, 2022
 *      Author: LARL
 */

#ifndef BSP_H_
#define BSP_H_

/******************************************************************************
EXTERNAL DEPENDENCIES
******************************************************************************/
#include <stdio.h>
#include "stm32f446xx.h" /* CMSIS interfaces for STM32F446RE */
#include "stdint.h"
#include "rtos.h"
#include "gpio.h"

/******************************************************************************
DEFINITION OF CONSTANTS
******************************************************************************/
#define BSP_TICKS_PER_SEC 100U
/* System Clock setting [Hz]. Macro HSI_VALUE or variable
	SystemCoreClock can be also used. */
#define BSP_SYS_CLOCK_HZ 16000000UL 

/******************************************************************************
DECLARATION OF TYPES
******************************************************************************/

/******************************************************************************
DECLARATION OF VARIABLES
******************************************************************************/

/******************************************************************************
DECLARATION OF CONSTANT DATA
******************************************************************************/

/******************************************************************************
DECLARATION OF FUNCTIONS
******************************************************************************/

void main_blinky1(void);
void main_blinky2(void);

/******************************************************************************
DECLARATION OF FUNCTION-LIKE MACROS
******************************************************************************/

/******************************************************************************
End Of File
******************************************************************************/

#endif /* BSP_H_ */
