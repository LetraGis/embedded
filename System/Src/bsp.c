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
	/* Pin 13 of Port C is connected to On-Board User Button */
	(void)Gpio_PortInit(portc);
	(void)Gpio_PinMode(portc, pin13, input);

	/* SPI Related Configuration */
	Gpio_PortInit(porta);
	Gpio_PinMode(porta, pin4, alternate);
	Gpio_PinMode(porta, pin5, alternate);
	Gpio_PinMode(porta, pin6, alternate);
	Gpio_PinMode(porta, pin7, alternate);

	Gpio_ConfigAltFnc(porta, pin4, altFun5);
	Gpio_ConfigAltFnc(porta, pin5, altFun5);
	Gpio_ConfigAltFnc(porta, pin6, altFun5);
	Gpio_ConfigAltFnc(porta, pin7, altFun5);

	Gpio_OutputTypeCfg(porta, pin4, pushPull);
	Gpio_OutputTypeCfg(porta, pin5, pushPull);
	Gpio_OutputTypeCfg(porta, pin6, pushPull);
	Gpio_OutputTypeCfg(porta, pin7, pushPull);

	Gpio_PullMode(porta, pin4, none);
	Gpio_PullMode(porta, pin5, none);
	Gpio_PullMode(porta, pin6, none);
	Gpio_PullMode(porta, pin7, none);

	Gpio_OutputSpeed(porta, pin4, highSpeed);
	Gpio_OutputSpeed(porta, pin5, highSpeed);
	Gpio_OutputSpeed(porta, pin6, highSpeed);
	Gpio_OutputSpeed(porta, pin7, highSpeed);
}

/*!****************************************************************************
 * @brief			Initializes SPI.
 * @details		   	Initializes SPI. Implementation is up to the developer. For
 * 					the example, SPI1 Configuration Register 1 is configured,
 * 					and SPI1 Peripheral 1 is enabled.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Spi_InitCallback(void)
{	
	SPI1_ENABLE();
	Spi_Config1Type spi1cfg1;
	spi1cfg1.Bytes = 0;
	spi1cfg1.Fields.BIDIMODE = twoLineUni;
	spi1cfg1.Fields.BR = pclkDivBy8;
	spi1cfg1.Fields.CPHA = firstEdge;
	spi1cfg1.Fields.CPOL = clkPolLowIdle;
	spi1cfg1.Fields.DFF = oneByte;
	spi1cfg1.Fields.MSTR = spiMaster;
	spi1cfg1.Fields.SSM = swMgtDisabled;

	Spi_Config_CR1(SPI_1, spi1cfg1.Bytes);
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

/*!****************************************************************************
 * @brief			Delays execution code.
 * @details		   	Waits for the number of ticks given by the input.
 * @param[in]      	ticks   Number of CPU cycles wasted.
 * @return         	void    No output parameters.
 ******************************************************************************/
void delay(const uint32_t ticks)
{
	for (uint32_t i = 0; i < ticks; i++);
}

/******************************************************************************
End Of File
******************************************************************************/
