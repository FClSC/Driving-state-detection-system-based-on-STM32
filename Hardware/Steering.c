#include "stm32f10x.h"                  // Device header



void Steering_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef structure;
	structure.GPIO_Mode=GPIO_Mode_AF_PP;//使用复用推挽输出，便于输出PWM波形
	structure.GPIO_Pin=GPIO_Pin_1;
	structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&structure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	//配置PA1口,用于通道二CH2输出PWM波形
	
}
void Steering_Set_Angle(float Angle)
{
   TIM_SetCompare2(TIM2,Angle/9*100+500);
	//直接设置CH2的CCR来调整舵机转动角度
	

}
