#include "stm32f10x.h"                  // Device header



void Steering_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef structure;
	structure.GPIO_Mode=GPIO_Mode_AF_PP;//ʹ�ø�������������������PWM����
	structure.GPIO_Pin=GPIO_Pin_1;
	structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&structure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	//����PA1��,����ͨ����CH2���PWM����
	
}
void Steering_Set_Angle(float Angle)
{
   TIM_SetCompare2(TIM2,Angle/9*100+500);
	//ֱ������CH2��CCR���������ת���Ƕ�
	

}
