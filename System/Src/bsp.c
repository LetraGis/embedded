/*
 * bsp.c
 *
 *  Created on: Nov 2, 2022
 *      Author: LARL
 */

/******************************************************************************
EXTERNAL DEPENDENCIES
******************************************************************************/

#include "bsp.h"

/******************************************************************************
MODULE DEFINES
******************************************************************************/

/******************************************************************************
MODULE TYPES
******************************************************************************/

/******************************************************************************
DECLARATION OF LOCAL FUNCTIONS
******************************************************************************/

/******************************************************************************
DEFINITION OF LOCAL VARIABLES
******************************************************************************/

/******************************************************************************
DEFINITION OF EXPORTED VARIABLES
******************************************************************************/

/******************************************************************************
DEFINITION OF LOCAL CONSTANT DATA
******************************************************************************/

/******************************************************************************
DEFINITION OF EXPORTED CONSTANT DATA
******************************************************************************/

/******************************************************************************
MODULE FUNCTION-LIKE MACROS
******************************************************************************/

/******************************************************************************
DEFINITION OF APIs
******************************************************************************/

/*!****************************************************************************
 * @brief			Initializes RTOS kernel.
 * @details		   	Initializes RTOS by setting the priority of PendSV
 *                  exception to the lowest (which is used for context
 *                  switching) and starts the idle thread.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void SysTick_Handler(void) 
{

	OS_Tick();

    __disable_irq();
    OS_Sched();
    __enable_irq();

}

/*!****************************************************************************
 * @brief			Initializes RTOS kernel.
 * @details		   	Initializes RTOS by setting the priority of PendSV
 *                  exception to the lowest (which is used for context
 *                  switching) and starts the idle thread.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void OS_onStartup_Callback(void)
{
    /* Function given by core M4 CMSIS. We provide number of ticks as input. */
	(void)SysTick_Config(BSP_SYS_CLOCK_HZ/BSP_TICKS_PER_SEC);

	NVIC_SetPriority(SysTick_IRQn, 0U);

	/* Alternatively we can set the fields individually using CMSIS
	structure as shown bellow. */
	/* Specifies the start value of SysTick Counter */
	/* SysTick->LOAD = SYS_CLOCK_HZ - 1U; */
    /* Specifies the current value of SysTick Counter */
	/* SysTick->VAL  = 0U; */
    /* Bit 2 - ClkSource (Internal OScillator - HSI in this case) */
	/* Bit 1 - TickInt (Enables exception request when counting down to 0) */
	/* Bit 0 - Enables SysTick Counter (Counter reloads value from LOAD reg) */
	/* SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0); */
}

/*!****************************************************************************
 * @brief			Initializes RTOS kernel.
 * @details		   	Initializes RTOS by setting the priority of PendSV
 *                  exception to the lowest (which is used for context
 *                  switching) and starts the idle thread.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void OS_onIdle_Callback(void)
{
    __WFI();
}

/*!****************************************************************************
 * @brief			Initializes RTOS kernel.
 * @details		   	Initializes RTOS by setting the priority of PendSV
 *                  exception to the lowest (which is used for context
 *                  switching) and starts the idle thread.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Gpio_InitCallback(void)
{
	/* Pin 5 of Port A is connected to On-Board Green LED */
	/* Pin 13 of Port C is connected to On-Board User Button */
	(void)Gpio_PortInit(porta);
	(void)Gpio_PinMode(porta, pin5, output);
	(void)Gpio_PinMode(porta, pin6, output);
}

/*!****************************************************************************
 * @brief			Initializes RTOS kernel.
 * @details		   	Initializes RTOS by setting the priority of PendSV
 *                  exception to the lowest (which is used for context
 *                  switching) and starts the idle thread.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Q_onAssert(char const *module, int loc)
{
	/* TBD */
	(void)module;
	(void)loc;
	NVIC_SystemReset();
}

/******************************************************************************
End Of File
******************************************************************************/
