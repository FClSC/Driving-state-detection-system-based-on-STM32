#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP ;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_On(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Off(void)
{	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_turn(void)
{
	
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)//Ïì×Å
	{	
		GPIO_SetBits(GPIOB,GPIO_Pin_12);//¹ØÉùÒô	
	}
	else GPIO_ResetBits(GPIOB,GPIO_Pin_12);//ÅªÏì
}
void Buzzering(void)
{
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(500);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(200);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(500);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

	void Buzzer_playTone(int toneDuration) {
    unsigned int i;
    
    for (i = 0; i <= 100; i++) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        Delay_us(i);
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        Delay_us(100 - i);
    }

    Delay_ms(toneDuration);  // ???????

    for (i = 100; i != 0; i--) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        Delay_us(i);
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        Delay_us(100 - i);
    }
}
