
/*
 * PUSH BUTTON PRESS - LED Toggle
 * (PC13) - Push Button
 * (PA5) - LED
 * */

#include <stdint.h>
#include <stdio.h>

uint32_t *RCC_AHB1ENR  =(uint32_t*)0x40023830;

uint32_t *PC_MODER  =(uint32_t*)0x40020800;
uint32_t *PC_IDR  =(uint32_t*)0x40020810;

uint32_t *PA_MODER  =(uint32_t*)0x40020000;
uint32_t *PA_ODR  =(uint32_t*)0x40020014;
uint32_t *PA_BSRR  =(uint32_t*)0x40020818;

void init(void);

void delay(void)
{
	for(uint32_t i=0;i<500000;i++);
}


int main(void)
{
	while(1)
	{
		uint8_t Button_PinState=0;
		*RCC_AHB1ENR |=(1<<0); //GPIO A
		*RCC_AHB1ENR |=(1<<2); //GPIO C

		//clear and set MODER
		//PC13 - Push Button - i/p(00) - MODER13
		*PC_MODER &=0xF3FFFFFF; //11 11 00 11 - mask value
		*PC_MODER |=0x00000000; //00 00 00 00

		//PA5 - LED - o/p(01) - MODER5
		*PA_MODER &=0xFFFFF3FF; //00 11 11 11 11 11 - mask value
		*PA_MODER |=0x00000400; //01 00 00 00 00 00

		//PC13 - Push Button - IDR
		*PC_IDR &= 0xDFFF; // 1101 1111 - mask value


		//Button_PinState = ((*PC_IDR) & (0x2000)); //0010
		//Button_PinState = ((*PC_IDR) & (0x2000)) >> 13; //0010

		Button_PinState = (uint8_t) ((*PC_IDR) >> 13) & (0x01) ; //0010

		if( Button_PinState == 1)
		{
			*PA_ODR |= (1<<5); //Set
		}
		else
		{
			*PA_ODR &= (0<<5); //Reset
		}
	}
}
