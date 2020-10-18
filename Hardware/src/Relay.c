#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "math.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "relay.h"

//注：开关1用于控制key


_Bool key_value=0;
void relay_init(void)

{

  GPIO_InitTypeDef 
  GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

void relay_on(void)

{
  GPIO_SetBits(GPIOB,GPIO_Pin_9);
}

void relay_off(void)

{ 
  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}

void Pin_value(void)
{
		if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9))
		{
			key_value=1;
		}
}


	