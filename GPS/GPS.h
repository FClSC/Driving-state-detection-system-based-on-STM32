#ifndef _GPS_H
#define _GPS_H
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "math.h"
#include "Store.h"
#include "OLED.h"

float hav(float x);
void errorLog(int num);
void parseGpsBuffer(void);//�����ݽ��н���������GPS������
void printGpsBuffer(void);
float convertArrayToFloat(char *array, int length);//ת������
void BeiJingTime(int*H,int*M,int*S);//��ñ���ʱ��
void BeiJingDate(int*Year,int*Month,int*Day);//��ñ���ʱ�������
void GetLo_La(float*lo,float*la);//��þ�γ��
double Get_Distance(double llo,double lla,double lo,double la);//��������Ŀ������
void  Store_Target_Position(int Loint,int Lofra1,int Lofra2,int Laint,int Lafra1,int Lafra2);//�洢Ŀ�������
void Clear_Target_Position(void);//���Ŀ���
void Get_Target_Position(double* Lo,double* La);//��ȡĿ���λ��
double Get_Speed(void);
double Get_Direct(void);
double SoveEQ(double a,double b,double c);





#endif
