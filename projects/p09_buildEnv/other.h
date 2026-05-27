/*
 * other.h
 *
 *  Created on: Aug 4, 2023
 *      Author: LetraGis
 */


#ifndef OTHER_H_
#define OTHER_H_

/******************************************************************************
EXTERNAL DEPENDENCIES
******************************************************************************/
#include<stdint.h>

/******************************************************************************
DEFINITION OF CONSTANTS
******************************************************************************/
/* Taken from Table 1 - RM0390 (Reference Manual, page 57) */
#define RCC_BASE_ADDRESS        (0x40023800UL)
#define RCC_AHB1ENR_OFFSET      (0x30U)

#define RCC_AHB1ENR_ADDRESS     ((RCC_BASE_ADDRESS) + (RCC_AHB1ENR_OFFSET))
#define RCC_AHB1ENR             (*(volatile uint32_t * const)(RCC_AHB1ENR_ADDRESS))
#define GPIOA_EN_MSK            (1 << 0U)
#define GPIOC_EN_MSK            (1 << 2U)

#define GPIOA_BASE_ADDRESS      (0x40020000UL)
#define GPIOC_BASE_ADDRESS      (0x40020800UL)

#define GPIOA_MODE              (*(volatile uint32_t * const)(GPIOA_BASE_ADDRESS))
#define GPIOC_MODE              (*(volatile uint32_t * const)(GPIOC_BASE_ADDRESS))
#define GPIOA_5_OUT_MODE_MSK    (0x01 << (5 * 2))
#define GPIOA_5_CLR_MSK         ((1 << (5 * 2)) | (1 << ((5 * 2) + 1)))
#define GPIOC_13_IN_MODE_MSK    (0x11 << (13 * 2))

#define GPIOX_ODR_OFFSET        (0x14)
#define GPIOX_IDR_OFFSET        (0x10)
#define GPIOA_ODR               (*(volatile uint32_t * const)((GPIOA_BASE_ADDRESS) + (GPIOX_ODR_OFFSET)))
#define GPIOC_IDR               (*(volatile uint32_t * const)((GPIOC_BASE_ADDRESS) + (GPIOX_IDR_OFFSET)))

#define GPIOA_5_OUT_ST_MSK      (1 << 5)

#define GPIO_HIGH               1
#define GPIO_LOW                0

/******************************************************************************
DECLARATION OF TYPES
******************************************************************************/
typedef uint8_t gpioState;               

/******************************************************************************
DECLARATION OF VARIABLES
******************************************************************************/

/******************************************************************************
DECLARATION OF CONSTANT DATA
******************************************************************************/

/******************************************************************************
DECLARATION OF FUNCTIONS
******************************************************************************/
void Gpio_Init(void);
void Gpio_SetPinState(gpioState state);
gpioState Gpio_ReadPinState(void);

/******************************************************************************
DECLARATION OF FUNCTION-LIKE MACROS
******************************************************************************/

/******************************************************************************
End Of File
******************************************************************************/

#endif /* OTHER_H_ */
