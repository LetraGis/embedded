/*
 * gpio.c
 *
 *  Created on: Jun 1, 2022
 *      Author: LetraGis
 */

#include "gpio.h"

/*!****************************************************************************
 * @details		   Initializes the indicated port.
 * @param[in]      port    Holds the port number.
 * @return         retVal
 *                 OK:     port has been enabled
 *                 N_OK:   port has not been enabled
 ******************************************************************************/
uint8 Gpio_Port_Init(portNumber port)
{
	uint8 retVal = N_OK;
	/* GPIO port enable */
	if(port < PORT_MAX)
	{
		*(volatile uint32 * const)(RCC_AHB1ENR_ADDRESS) |= (1u << port);
		retVal = OK;
	}
	else
	{
		retVal = N_OK;
	}
	return retVal;
}

/*!****************************************************************************
 * @details		   Sets the port mode as output, input,
 * @param[in]      port    Holds the port number.
 * @return         retVal
 *                 OK:     request successful
 *                 N_OK:   Request was not successful
 ******************************************************************************/
uint8 Gpio_Pin_Mode(portNumber port, uint8 pin, portMode mode)
{
	uint8 retVal = N_OK;
	if((port < PORT_MAX) && (mode < PIN_MODE_MAX ) && (pin < PIN_NUM_MAX))
	{
		*(volatile uint32 * const)(GPIOX_REG_BASE_ADDRESS + (port * 0x400u))
				&= (~(uint32)(1u << (pin * 2u)) | ~(uint32)(1u << ((pin * 2u) + 1u)));
		*(volatile uint32 * const)(GPIOX_REG_BASE_ADDRESS + (port * 0x400u)) |= ((uint32)(mode << (pin * 2)));
		retVal = OK;
	}
	else
	{
		retVal = N_OK;
	}
	return retVal;
}

/*!****************************************************************************
 * @details		   Initializes the indicated port.
 * @param[in]      port    Holds the port number.
 * @return         retVal
 *                 OK:     request successful
 *                 N_OK:   Request was not successful
 ******************************************************************************/
uint8 Gpio_Pin_State(portNumber port, uint8 pin, pinState state)
{
	uint8 retVal = N_OK;
	if((port < PORT_MAX) && (pin < PIN_NUM_MAX))
	{
		if(state == low)
		{
			*(volatile uint32 * const)(GPIOX_REG_BASE_ADDRESS + (port * 0x400u) + 0x14u) |= (uint32)(1u << pin);
			retVal = OK;
		}
		else if(state == high)
		{
			*(volatile uint32 * const)(GPIOX_REG_BASE_ADDRESS + (port * 0x400u) + 0x14u) &= ~(uint32)(1u << pin);
			retVal = OK;
		}
		else
		{
			retVal = N_OK;
		}
	}
	return retVal;
}

