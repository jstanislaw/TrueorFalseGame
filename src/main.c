/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/



#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "sdmodule.h"
#include "tm_stm32f4_hd44780.h"


int main(void)
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

// tworzenie strutkury
GPIO_InitTypeDef  GPIO_InitStructure;

// wypelnianie struktury nanymi
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOD, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStructure);



SDmodule_Configuration();

char* filename = "TEST.txt";
UINT loadedBytes;
char dane[48];
SDmodule_ReadFile(filename, &dane, &loadedBytes);



TM_HD44780_Init(24,4);
TM_HD44780_Clear();
TM_HD44780_Puts(0, 0, &dane);


for(;;)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
	{GPIO_SetBits(GPIOD,GPIO_Pin_12);
	TM_HD44780_Clear();
	TM_HD44780_Puts(0, 0, "WITAJ");

	}


}



}
