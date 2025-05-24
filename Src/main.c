
/*
 * PUSH BUTTON PRESS - LED Toggle
 * (PB4) - Push Button - D5
 * (PB5) - LED - D4
 * */

#include <stdint.h>
#include <stdio.h>

uint32_t *RCC_PB_AHB1ENR = (uint32_t*)0x40023830;
uint32_t *PB_MODER = (uint32_t*)0x40020400;
uint32_t *PB_IDR = (uint32_t*)0x40020410;
uint32_t *PB_ODR = (uint32_t*)0x40020414;

void init(void);

void delay(void)
{
	for(uint32_t i=0;i<500000;i++);
}


int main(void)
{
	while(1)
	{
		//uint32_t Button_PinState=0;
		*RCC_PB_AHB1ENR |=(1<<1); //GPIO B

		//clear and set MODER
		//PB4 - Push Button - i/p(00) - MODER4
		*PB_MODER &=0xFFFFFCFF; //11 00 11 11 11 11 - mask value
		*PB_MODER |=0x00000000; //00 00 00 00 00 00

		//PB5 - LED - o/p(01) - MODER5
		*PB_MODER &=0xFFFFF3FF; //00 11 11 11 11 11 - mask value
		*PB_MODER |=0x00000400; //01 00 00 00 00 00

		//PB4 - Push Button - IDR
		*PB_IDR &= 0xFFEF; // 11 10 11 11 - mask value
		//PB5 - Push Button - ODR
		*PB_ODR &= 0xFFDF; // 11 01 11 11 - mask value

		//Switch Pull_Up connection in BreadBoard
		if( ((*PB_IDR) & (0x0010)) == 0) //0001 0000
		{
			*PB_ODR |= (1<<5); //Set
		}
		else
		{
			*PB_ODR &= (0<<5); //Reset
		}

		//Switch Pull_Down connection in BreadBoard
		/*if( ((*PB_IDR) & (0x0010)) == 0) //0001 0000
		{
			*PB_ODR &= (0<<5); //Reset
		}
		else
		{
			*PB_ODR |= (1<<5); //Set
		}*/
	}
}
