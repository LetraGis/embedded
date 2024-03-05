/*
 * sys_f446xx.h
 *
 *  Created on: Jan 12, 2024
 *      Author: LetraGis
 */

#ifndef SYS_F446XX_H_
#define SYS_F446XX_H_

/******************************************************************************
EXTERNAL DEPENDENCIES
******************************************************************************/
#include <stdio.h>
#include "stm32f446xx.h" /* CMSIS interfaces for STM32F446RE */
#include "stdint.h"
#include "gpio.h"
#include "spi.h"

/******************************************************************************
DEFINITION OF CONSTANTS
******************************************************************************/
/* Number of EXTI Configuration Registers */
#define SYSCFG_EXTI_NUM_REGS		(4u)
/* Length in bits of configuration field for each pin */
#define SYSCFG_EXTI_BITS_LENGTH		(4u)

/******************************************************************************
DECLARATION OF TYPES
******************************************************************************/
typedef enum
{
    rising = 0,		/* Rising Edge Detection */
    falling,		/* Falling Edge Detection */
    risingFalling	/* Both Rising and Falling Edge Detection */
} EXTI_EdgeDetection;

/******************************************************************************
DECLARATION OF VARIABLES
******************************************************************************/

/******************************************************************************
DECLARATION OF CONSTANT DATA
******************************************************************************/

/******************************************************************************
DECLARATION OF FUNCTIONS
******************************************************************************/

/*!****************************************************************************
 * @brief			Initialize SysCfg Peripheral.
 * @details		   	Initializes SysCfg Peripheral, which is used to remap
 * 					memory accessible in the code area and to manage the
 * 					external interrupt line connection to the GPIO's.
 * @param[in]      	void    No input parameters.
 * @return         	void	No output parameters.
 ******************************************************************************/
__STATIC_INLINE void SysCfg_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

/*!****************************************************************************
 * @brief			Configures External Interrupt source.
 * @details		   	Selects the port and the pin that will serve as a source of
 * 					External Interrupt.
 * @param[in]      	port    Holds the port that will trigger External Interrupt
 * @param[in]      	pin		Holds the pin that will trigger External Interrupt
 * @return         	void	No output parameters.
 ******************************************************************************/
__STATIC_INLINE void SysCfg_ExtIntCfg(Gpio_portNumber port, Gpio_pinNumber pin)
{
	/* By dividing the pin by SYSCFG_EXTI_NUM_REGS, we will know the register 
	   to be modified. E.g. if pin is 13, we will divide 13 by (4), which 
	   results in 3. We will access EXTICR[3] = EXTICR[4], that covers pin 12
	   to 15. */
	uint8_t temp1 = pin / SYSCFG_EXTI_NUM_REGS;
	/* By calculating the modulos of pin divided by SYSCFG_EXTI_BITS_LENGTH, we 
	   will know the offset that we need to consider to set the corresponding 
	   field. If we have pin 13, then we will divide 13 by 4. Modulus is 1. By 
	   multiplying the result by SYSCFG_EXTI_BITS_LENGTH we obtain the offset 
	   (4). Then we shift the port, which for this example will be C (2), 4
	   times to the left. */
	uint8_t temp2 = pin % SYSCFG_EXTI_BITS_LENGTH;
	SYSCFG->EXTICR[temp1] |= (port << (temp2 * SYSCFG_EXTI_BITS_LENGTH)); 
}

/*!****************************************************************************
 * @brief			Configures edge detection for pin interrupts.
 * @details		   	Configures edge detection for pin interrupts: it could be
 *                  configured as rising edge, falling edge or both.
 * @param[in]      	edge    Edge detection: rising, falling and both.
 * @param[in]      	pin		Holds the pin that will trigger External Interrupt
 * @return         	void	No output parameters.
 ******************************************************************************/
__STATIC_INLINE void EXTI_EdgeDetection(EXTI_EdgeDetection edge, Gpio_pinNumber pin)
{
	if(rising == edge)
	{
		EXTI->RTSR |= (1 << pin);
	}
	else if (falling == edge)
	{
		EXTI->FTSR |= (1 << pin);
	}
	else if (risingFalling == edge)
	{
		EXTI->RTSR |= (1 << pin);
		EXTI->FTSR |= (1 << pin);
	}
}

/*!****************************************************************************
 * @brief			Returns the value of Pending Register of a given pin.
 * @param[in]      	pin		Holds the pin that will trigger External Interrupt
 * @return         	1       If there is a Pending ISR on that particular pin
 *                  0       If there is no Pending ISR.	
 ******************************************************************************/
__STATIC_INLINE uint8_t EXTI_ReadPendISRBit(Gpio_pinNumber pin)
{
	return((uint8_t)((EXTI->PR >> pin) & 1u));
}

/*!****************************************************************************
 * @brief			Clears the value of Pending Register of a given pin.
 * @details		   	Clears the value of Pending Register of a given pin by
 *                  setting the correspoding bit.
 * @param[in]      	pin		Holds the pin that will trigger External Interrupt
 * @return         	void	No output parameters.
 ******************************************************************************/
__STATIC_INLINE void EXTI_ClearPendISRBit(Gpio_pinNumber pin)
{
	EXTI->PR |= (1 << pin);
}

/*!****************************************************************************
 * @brief			Configures Interrupt Mask Register to enable ISR on a pin.
 * @details		   	By setting the a bit on the Interrupt Mask Register, an ISR
 *                  can be triggered from the EXTI peripheral to NVIC Core
 *                  peripheral.
 * @param[in]      	pin		Holds the pin that will trigger External Interrupt
 * @return         	void	No output parameters.
 ******************************************************************************/
__STATIC_INLINE void EXTI_SetISRMaskBit(Gpio_pinNumber pin)
{
	EXTI->IMR |= (1 << pin);
}
/******************************************************************************
DECLARATION OF FUNCTION-LIKE MACROS
******************************************************************************/

/******************************************************************************
End Of File
******************************************************************************/

#endif /* SYS_F446XX_H_ */
