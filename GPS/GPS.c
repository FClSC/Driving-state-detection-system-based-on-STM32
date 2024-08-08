#include "GPS.h"




void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}




void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)//�����ж��Ƿ��ȡ����GPS����
	{
		Save_Data.isGetData = false;
		printf("**************\r\n");
		printf(Save_Data.GPS_Buffer);//�ȴ�ӡ��õ�ȫ��֡����	

		
		for (i = 0 ; i <= 9 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//��������
			}
			else
			{
				subString++;//ָ�������ƶ�һλ
				if ((subStringNext = strstr(subString, ",")) != NULL)//�������ָ�������ַ�����һ�����ŵ�λ��
				{
					char usefullBuffer[2]; 
					switch(i)//�����İ������ڴ�洢���ַ����ƣ�Ҳ������������֮��Ķ�������ճ��
					{              //��ճ����ʼ��ַ   ��������ʼ��ַ   ���Ƶ��ֽ���
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//��ȡE/W
						case 7:memcpy(Save_Data.Speed, subString, subStringNext - subString);break;  //��ȡ�ٶ�
						case 8:memcpy(Save_Data.Direct, subString, subStringNext - subString);break; //��ȡ����
	          case 9:memcpy(Save_Data.UTCDate, subString, subStringNext - subString);break; //��ȡUTC����
						default:break;
					}

					subString = subStringNext;//��������ƶ�����һ�����ŵ�λ��
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//��������
				}
			}


		}
	}
}

void printGpsBuffer()
{
	if (Save_Data.isParseData)//�����Ƿ�������
	{
		Save_Data.isParseData = false;//����ˡ���־λ���
		
		printf("UTCʱ�� = ");
		printf(Save_Data.UTCTime);
		printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("γ������ = ");
			printf(Save_Data.latitude);
			printf("\r\n");


			printf("Save_Data.N_S = ");
			printf(Save_Data.N_S);
			printf("\r\n");

			printf("�������� = ");
			printf(Save_Data.longitude);
			printf("\r\n");

			printf("Save_Data.E_W = ");
			printf(Save_Data.E_W);
			printf("\r\n");
			
			printf("�ٶ�=");
			printf(Save_Data.Speed);
			printf("\r\n");
			
			printf("����=");
			printf(Save_Data.Direct);
			printf("\r\n");
			
			printf("UTC����=");
			printf(Save_Data.UTCDate);
			printf("\r\n");
		}
		else
		{
			printf("GPS�����ݲ�����\r\n");
		}
		
	}
}
float convertArrayToFloat(char *array, int length) //�ַ�����ת����������
	{
    float result = 0.0;
    int dotIndex = -1; 


    for (int i = 0; i < length; i++) {
        if (array[i] == '.') {
            dotIndex = i;
            break;
        }
    }


    for (int i = 0; i < dotIndex; i++) {
        result = result * 10 + (array[i] - '0');
    }


    float decimal = 0.0;
    float multiplier = 0.1;
    for (int i = dotIndex + 1; i < length; i++) {
        decimal += (array[i] - '0') * multiplier;
        multiplier *= 0.1;
    }

    result += decimal;

    return result;
}
void BeiJingDate(int*Year,int*Month,int*Day)
	{
		*Day=(Save_Data.UTCDate[0]-'0')*10+(Save_Data.UTCDate[1]-'0');
		*Month=(Save_Data.UTCDate[2]-'0')*10+(Save_Data.UTCDate[3]-'0');
		*Year=(Save_Data.UTCDate[4]-'0')*10+(Save_Data.UTCDate[5]-'0');

	}
void BeiJingTime(int *H, int *M, int *S) {
    int UTCtime = convertArrayToFloat(Save_Data.UTCTime, 9);
    

    *H = (UTCtime / 10000 + 8) % 24;
    

    *M = (UTCtime % 10000) / 100;
    

    *S = UTCtime % 100;
}
void GetLo_La(float* lo, float* la)//����γ�ȵĳ�ʼ������10834.56789תΪ׼ȷ�ľ�γ�ȸ�����ʽ
	{
    float Lo = convertArrayToFloat(Save_Data.longitude, 12); 
    float La = convertArrayToFloat(Save_Data.latitude, 12); 
    
    int A1 = (int)Lo / 100;
    int B1 = (int)(Lo - A1 * 100);
    float C1 = Lo - A1 * 100 - B1;
    *lo = A1 + B1 / 60.0f + C1 / 60.0f;
    
    int A2 = (int)La / 100;
    int B2 = (int)(La - A2 * 100);
    float C2 = La - A2 * 100 - B2;
    *la = A2 + B2 / 60.0f + C2 / 60.0f; 
}
float hav(float x) {
  return  (1 - cos(x)) / 2;
}

double Get_Distance(double llo,double lla,double lo,double la)
{
	
	

    double r = 6371;  
     //lla=34.030764, llo=108.765889;
     //la=34.03064, lo=108.78;
    double x;
    double d;
    double a1_rad = lla * 3.1415926 / 180.0;
    double b1_rad = llo * 3.1415926 / 180.0;
    double a2_rad = la * 3.1415926 / 180.0;
    double b2_rad = lo * 3.1415926 / 180.0;

    x = hav(a2_rad - a1_rad) + cos(a1_rad) * cos(a2_rad) * hav(b2_rad - b1_rad);
    d = r * acos(1-2*x)*1000;
	  return d;
	
	
}
void  Store_Target_Position(int Loint,int Lofra1,int Lofra2,int Laint,int Lafra1,int Lafra2)
{
	Store_Data[1]=Loint;
	Store_Data[2]=Lofra1;
	Store_Data[3]=Lofra2;
	Store_Data[4]=Laint;
	Store_Data[5]=Lafra1;
	Store_Data[6]=Lafra2;
	Store_Save();

}
void Clear_Target_Position(void)
{
	Store_Clear();
}
void Get_Target_Position(double* Lo,double* La)
{
	*Lo=Store_Data[1]+Store_Data[2]/1000.0+Store_Data[3]/1000000.0;
	*La=Store_Data[4]+Store_Data[5]/1000.0+Store_Data[6]/1000000.0;
}


double Get_Speed(void)//����ٶ�
{
	double Jie=convertArrayToFloat(Save_Data.Speed,6 );
  return Jie*0.514444;
}

double Get_Direct(void)//��ú���
{
	
	return convertArrayToFloat(Save_Data.Direct,6);
	
}
double SoveEQ(double a,double b,double c)
{
	double discriminant = b * b - 4 * a * c;
	
	double  root1 = (-b + sqrt(discriminant)) / (2 * a);
   double root2 = (-b - sqrt(discriminant)) / (2 * a);
	
	 if(root1>0&&root2<0){return root1;}
	else {return root2;}
	
	
}




