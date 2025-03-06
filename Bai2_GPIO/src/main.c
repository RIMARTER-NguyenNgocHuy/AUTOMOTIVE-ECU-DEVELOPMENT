#include "stm32f4xx.h"
//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_gpio.h"

void RCCconfig();
void GPIOconfig();
void delay(uint32_t timedelay);

int main() {
    RCCconfig();
    GPIOconfig();
    while (1) {
//			GPIO_ToggleBits(GPIOB, GPIO_Pin_2);
			if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0){
				while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0);
				if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_2)){
					GPIO_ResetBits(GPIOB, GPIO_Pin_2);
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_2);
				}
			}
			delay(50000);
    }
}

void RCCconfig() {
//    RCC->AHB1ENR |= 0x000001F8;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
}

void GPIOconfig() {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void delay(uint32_t timedelay) {
		uint32_t i;
    for (i = 0; i < timedelay; i++) {
        __asm("NOP");
    }
}