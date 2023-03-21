/*
 * gpio.h
 *
 *  Created on: Jun 1, 2022
 *      Author: LetraGis
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef uint32_t uint32;
typedef uint8_t uint8;

/* RCC register to enable GPIO ports */
#define RCC_AHB1ENR_ADDRESS 0x40023830u
/* GPIO base register address */
#define GPIOX_REG_BASE_ADDRESS 0x40020000u

#define HIGH (1u)
#define LOW (0)
#define OK (0u)
#define N_OK (1u)
#define PORT_MAX (8u) //Maximum number of ports
#define PIN_MODE_MAX (4u) //Maximum number of pin modes
#define PIN_NUM_MAX (16u) //Maximum number of pins per port

typedef enum
{
	low = 0,
	high = 1,
} pinState;

typedef enum
{
	porta = 0,
	portb,
	portc,
	portd,
	porte,
	portf,
	portg,
	porth,
} portNumber;

typedef enum
{
	input = 0,
	output,
	alternate,
	analog,
} portMode;

/* Function prototypes */
uint8 Gpio_Port_Init(portNumber port);
uint8 Gpio_Pin_Mode(portNumber port, uint8 pin, portMode mode);
uint8 Gpio_Pin_State(portNumber port, uint8 pin, pinState state);

#endif /* GPIO_H_ */
