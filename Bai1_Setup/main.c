#include "stm32f10x.h" 

typedef struct
{
	unsigned int CRL;
	unsigned int CRH;
	unsigned int IDR;
	unsigned int ODR;
	unsigned int BSRR;
	unsigned int BRR;
	unsigned int LCKR;
} GPIO_typeDef;

typedef struct
{
	unsigned int CR;
	unsigned int CFGR;
	unsigned int CIR;
	unsigned int APB2RSTR;
	unsigned int APB1RSTR;
	unsigned int AHBENR;
	unsigned int APB2ENR;
	unsigned int APB1ENR;
	unsigned int BDCR;
	unsigned int CSR;
} RCC_typeDef;

#define RCC_APB2ENR ((RCC_typeDef *) 0x40021000)
#define GPIOD ((GPIO_typeDef *) 0x40011400)
#define GPIOC ((GPIO_typeDef *) 0x40011000)

void RCCconfig();
void GPIOconfig();
void delay(unsigned int  timedelay);
void WritePin(GPIO_TypeDef *GPIO_Port, unsigned int Pin, unsigned int state);

unsigned int j = 0, k = 0;

int main(){
	RCCconfig();
	GPIOconfig();
	while(1){
		if((GPIOC->IDR & (1 << 13))  == 0){
			WritePin(GPIOD, 2, 0);
			delay(10000000);
		}
		else 
			WritePin(GPIOD, 2, 1);
			delay(10000000);
		
//		WritePin(GPIOD, 2, 0);
//		delay(10000000);
//		WritePin(GPIOD, 2, 1);
//		delay(10000000);
	}
}

void RCCconfig(){
	RCC->APB2ENR |= (1 << 5) | (1 << 4);
}

void GPIOconfig(void){
		GPIOD->CRL |= (3 << 8);  
		GPIOD->CRL &= ~(3 << 10); 
	
		GPIOC->CRH |= (8 << 22);
		GPIOC->CRH &= ~(7 << 20);
		GPIOC->ODR |= (1 << 13);
		//GPIOD->CRL &= ~(0xF << 20); 
		//GPIOC->CRH |= (0x04 << 20); 
}

void WritePin(GPIO_TypeDef *GPIO_Port, unsigned int Pin, unsigned int state){
	if(state == 1) GPIO_Port->ODR |= (1 << Pin);
	else GPIO_Port->ODR &= ~(1 << Pin);
}

void delay(unsigned int timedelay) {
    for (unsigned int i = 0; i < timedelay; i++) {
        __asm("NOP");
    }
    j++;
}




