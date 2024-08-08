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
void parseGpsBuffer(void);//对数据进行解析，解析GPS缓冲区
void printGpsBuffer(void);
float convertArrayToFloat(char *array, int length);//转浮点数
void BeiJingTime(int*H,int*M,int*S);//获得北京时间
void BeiJingDate(int*Year,int*Month,int*Day);//获得北京时间的日期
void GetLo_La(float*lo,float*la);//获得经纬度
double Get_Distance(double llo,double lla,double lo,double la);//本机距离目标点距离
void  Store_Target_Position(int Loint,int Lofra1,int Lofra2,int Laint,int Lafra1,int Lafra2);//存储目标点坐标
void Clear_Target_Position(void);//清空目标点
void Get_Target_Position(double* Lo,double* La);//获取目标点位置
double Get_Speed(void);
double Get_Direct(void);
double SoveEQ(double a,double b,double c);





#endif
