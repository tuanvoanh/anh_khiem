
/*
 * Core.c
 *
 *  Created on: Oct 19, 2018
 *      Author: Administrator
 */
#define device_num 5
#define TIME_DELAY 1000

#include "stm32f0xx_hal.h"
#include "core.h"
#include "stm32f0xx_hal_uart.h"
#include <stdint.h>
#include <string.h>

UART_HandleTypeDef huart1;
char deviceReadStatusPin[device_num] = {0,0,0,0,0}, deviceReadResult = 0;
uint8_t vDeviceStatus = 0;
uint8_t uartWrite(uint8_t pChar){
	HAL_UART_Transmit(&huart1, &pChar, 1, 100);
	return 1;
}
void setup()
{
	uartWrite(65);
}


char read_gpio()
{
	deviceReadResult = 0;
	deviceReadStatusPin[0] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	deviceReadStatusPin[1] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
	deviceReadStatusPin[2] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);
	deviceReadStatusPin[3] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);
	deviceReadStatusPin[4] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);
	for(int i = device_num-1; i>=0;--i)
	{
		deviceReadResult<<=1;
		deviceReadResult += deviceReadStatusPin[i];
	}
	return deviceReadResult;
}
void loop()
{
	vDeviceStatus = read_gpio();
	uartWrite(0x01);
	uartWrite(vDeviceStatus);
	HAL_Delay(TIME_DELAY);
}

