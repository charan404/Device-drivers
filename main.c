#include<stdio.h>
#include "GPIO_Driver.h"
#include "stm32f4xx.h" 
#define LEDPINNO 5
#define SWITCH_PIN 13
 GPIO_TypeDef *gpio,*gpioout;
 	unsigned int i=0;
int main()
{

  int Read_data =0;
  gpio = GPIOA;
	gpioout=GPIOC;
	Gpio_pin_def GpioConfig,GpioConfigl;
//GpioConfig->MODER |=(GPIO_OUTPUT_MODE<<(2*5));
	//GpioConfig->OTYPER |=(GPIO_OUTPUT_TYPE_PUSH_PULL<<5);
	//GpioConfig->OSPEEDR|=(GPIO_LOW_SPEED<<(2*5));
	//GpioConfig->PUPDR|=(GPIO_NO_PULL_UP_DOWN<<(2*5));
	//GpioConfig->AFR[0]|=(aft<<5*4);
	
	GPIO_ClockConfig(GPIOPORT_A);
	GPIO_ClockConfig(GPIOPORT_C);
	GPIO_Initialization(gpio,&GpioConfig, GPIO_OUTPUT_MODE, GPIO_OUTPUT_TYPE_PUSH_PULL, GPIO_LOW_SPEED,4,GPIO_NO_PULL_UP_DOWN,LEDPINNO);
	GPIO_Initialization(gpioout,&GpioConfigl, GPIO_INPUT_MODE, GPIO_OUTPUT_TYPE_PUSH_PULL, GPIO_LOW_SPEED,4,GPIO_NO_PULL_UP_DOWN,SWITCH_PIN);
	//GPIO_SetUp_InterruptSystem(EXTI2_IRQn, RISING_EDGE_TRIGGER,SWITCH_PIN);
	//SYSCFG->EXTICR|=(1<<11));

	while(1)
	{
			Read_data= GPIO_Read(gpioout,SWITCH_PIN);
	  if(Read_data==1)
	  {
	  	GPIO_Write(gpio,1,LEDPINNO);
	  	for(i=0;i<500000;i++);
	  	GPIO_Write(gpio,0,LEDPINNO); 
	  	for(i=0;i<500000;i++);
	  	
	  }
  }
	return 0;   
}
	void EXTI0_IRQHandler()
	{
		Gpio_ClearInterrupt(SWITCH_PIN);
		GPIO_Write(gpio,1,LEDPINNO);
		for(i=0;i<500000;i++);
		GPIO_Write(gpio,0,LEDPINNO); 
		for(i=0;i<500000;i++);
	}
