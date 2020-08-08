#include "wtn6.h"

/*
 *@brief 		1΢����ʱ��������
 *				STC-ISP�������
 *@param[in]	NULL
 *@author		MrWeng
 *@date			2020-8-7
 */
void Delay1us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 1;
	while (--i);
}

/*
 *@brief 		΢����ʱ����
 *				
 *@param[in]	us����Ҫ��ʱ��΢����
 *@author		MrWeng
 *@date			2020-8-7
 */
void Delay_us(unsigned short int us)
{
	unsigned short int i;
	for(i=0;i<us;i++)
		Delay1us();
}

/*
 *@brief 		1������ʱ��������
 *				STC-ISP�������
 *@param[in]	NULL
 *@author		MrWeng
 *@date			2020-8-7
 */
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 15;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}

/*
 *@brief 		������ʱ����
 *				
 *@param[in]	ms����Ҫ��ʱ�ĺ�����
 *@author		MrWeng
 *@date			2020-8-7
 */
void Delay_ms(unsigned short int ms)
{
	unsigned short int i;
	for(i=0;i<ms;i++)
		Delay1ms();
}

/*
 *@brief 		WTN6 1�ߴ���ͨ�ź�����������
 *				�����ϸ���ʱ��ͨ��
 *@param[in]	Send_DATA����Ҫ���͵ĵ����ݵĵ�ַ���鿴ͷ�ļ�
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Line_1(unsigned char Send_DATA)
{
	unsigned char S_DATA,j;
	bit B_DATA;
	S_DATA =Send_DATA;
	WNT6_DATA=0;
	Delay_ms(5);		//��ʱ5����			
	B_DATA = S_DATA&0X01;
	for(j=0;j<8;j++) 
	{ 
		if(B_DATA == 1) 
	{ 
		WNT6_DATA = 1; 
		Delay_us(600); //��ʱ 600us 
		WNT6_DATA = 0; 
		Delay_us(200); //��ʱ 200us 
	} 
	else 
	{ 
		WNT6_DATA = 1; 
		Delay_us(200); //��ʱ 200us 
		WNT6_DATA = 0; 
		Delay_us(600); //��ʱ 600us 
	} 
		S_DATA = S_DATA>>1; 
		B_DATA = S_DATA&0X01; 
	} 
		WNT6_DATA = 1;
}

/*
 *@brief 		��������			
 *@param[in]	Num[]����Ҫ����������
 * 				Len	 �����ֳ���	
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Num(unsigned char Num[],int Len)
{
	int i;
	for(i=0;i<Len;i++)
		{	
			Delay_ms(500);			//��ʱ1��
			WTN6_Line_1(Num[i]);
			Delay_ms(500);
		}
}
/*
 *@brief 		�����¶�	
 * 				ֻ֧��С�����1λ����������Ϊ���¶�XX��X�ȡ�
 *@param[in]	Num[]����Ҫ���������֣����3λ��С���㲻�ð�����
 *			    ����23.8�ȣ�ΪNum[]={0x02,0x03,0x08}		
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Temp(unsigned char Num[])
{
	WTN6_Temp_Type temp;						//�¶�
	WTN6_Symbol_Type Celsius,Dot;			   //���϶�,��
	
	temp 	=  WTN6_TH_Temp;	
	Celsius =  WTN6_S_TC;	
	Dot		=  WTN6_S_D;
	
	//��ʽ���¶� 23.5��
	Delay_ms(1000);					
	WTN6_Line_1(temp);							//�����¶�
	
	Delay_ms(1500);					
	WTN6_Line_1(Num[0]);						//�¶�ʮλ
	
	Delay_ms(1000);					
	WTN6_Line_1(Num[1]);						//�¶ȸ�λ
	
	Delay_ms(1000);					
	WTN6_Line_1(Dot);							//������
	
	Delay_ms(1000);			
	WTN6_Line_1(Num[2]);						//�¶�С��λ
	
	Delay_ms(1000);			
	WTN6_Line_1(Celsius);						//������
}

/*
 *@brief 		����ʪ��
 *				ֻ֧��С�����1λ����������Ϊ��ʪ�Ȱٷ�֮XX��
 *@param[in]	Num[]����Ҫ���������֣����3λ��С���㲻�ð�����
 *			    ����60.8%��ΪNum[]={0x06,0x00,0x08}
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Hump(unsigned char Num[])
{
	WTN6_Temp_Type hum;							//ʪ��
	WTN6_Symbol_Type Per_Cent,Dot;				//�ٷ�֮,��
	
	hum	 	 = WTN6_TH_Hum;
	Dot		 = WTN6_S_D;
	Per_Cent = WTN6_S_TH;
	
	//��ʽ���¶� 23.5%
	Delay_ms(1000);					
	WTN6_Line_1(hum);							//����ʪ��
	
	Delay_ms(1500);			
	WTN6_Line_1(Per_Cent);						//�����ٷ�֮
	
	Delay_ms(1500);					
	WTN6_Line_1(Num[0]);						//�¶�ʮλ
	
	Delay_ms(1000);					
	WTN6_Line_1(Num[1]);						//�¶ȸ�λ
	
	Delay_ms(1000);					
	WTN6_Line_1(Dot);							//������
	
	Delay_ms(1000);			
	WTN6_Line_1(Num[2]);						//�¶�С��λ	
}

/*
 *@brief 		������������������������ʽ��			
 *@param[in]	NULLL
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Ring(void)
{
	WTN6_Phone_Type ring;
	ring = WTN6_P_ICM;
	Delay_ms(1000);			
	WTN6_Line_1(ring);						
	Delay_ms(1000);				
}	

/*
 *@brief 		��������
 *				��������Ϊ�����硱
 *@param[in]	NULL
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_InCall(void)
{
	WTN6_Phone_Type ring;
	ring = WTN6_P_IC;
	Delay_ms(500);			
	WTN6_Line_1(ring);						
	Delay_ms(1000);				
}	

/*
  *@brief 		��������
 *				��������Ϊ������XXXX��X��X�ա�
 *@param[in]	Date����Ҫ����������
 *				���磺2020��8��18�գ�Date[]={0x02,0x00,0x02,0x00,0x00,0x08,0x01,0x08};
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_ReportDate(unsigned char Date[])						
{
//	unsigned char Year_Num[4],Month_Num[2],Day_Num[2];
	int i;
	
	WTN6_Date_Type Today,Year,Month,Day;
	Today = WTN6_D_TD;
	Year  = WTN6_D_Y;
	Month = WTN6_D_M;
	Day   = WTN6_D_D;
	
	Delay_ms(1000);			
	WTN6_Line_1(Today);
	Delay_ms(1000);
	
//������	
	for(i=0;i<4;i++)
	{	
		Delay_ms(500);			
		WTN6_Line_1(Date[i]);
		Delay_ms(500);
	}
	
	Delay_ms(500);			
	WTN6_Line_1(Year);
	Delay_ms(1000);
//������	
	if(Date[4] == 0x01)
	{
		Delay_ms(1000);			
		WTN6_Line_1(Date[4]);
		
		Delay_ms(1000);
		WTN6_Line_1(Date[5]);
		
		Delay_ms(1000);	
		WTN6_Line_1(Month);
		Delay_ms(1000);
	}
	{
		Delay_ms(1000);
		WTN6_Line_1(Date[5]);
		
		Delay_ms(1000);	
		WTN6_Line_1(Month);
		Delay_ms(1000);
	}
//������	
	if(Date[6] == 0x00)
	{
		Delay_ms(1000);
		WTN6_Line_1(Date[7]);
		
		Delay_ms(1000);	
		WTN6_Line_1(Day);
		Delay_ms(1000);
	}
	{
		
		Delay_ms(1000);			
		WTN6_Line_1(Date[6]);
		
		Delay_ms(1000);
		WTN6_Line_1(Date[7]);
		
		Delay_ms(1000);	
		WTN6_Line_1(Day);
		Delay_ms(1000);
	}
}

/*
 *@brief 		���㱨ʱ
 *				��������Ϊ����������18������
 *@param[in]	Time����Ҫ������ʱ�䡣
 *				Time[0]=0x01    ����
 *				Time[0]=0x02 	����
 *				Time[0]=0x03     ����
 *				���磺����18�㣬Date[]={0x02,0x01,0x08}��
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_ReportTime(unsigned char Time[])						
{
	WTN6_Time_Type OnHour,Mor,Aft,Nig,Now;
	WTN6_Symbol_Type Dot;
	
	OnHour = WTN6_T_O;
	Mor	   = WTN6_T_M;
	Aft    = WTN6_T_A;
	Nig    = WTN6_T_N;
	Now	   = WTN6_T_Now;
	Dot	   = WTN6_S_D;
	
	Delay_ms(1000);			
	WTN6_Line_1(Now);				//��������
	Delay_ms(1000);
	
	switch(Time[0])
	{
		case 0x01:
			Delay_ms(500);			
			WTN6_Line_1(Mor);		//��������
			Delay_ms(500);
		break;
		case 0x02:
			Delay_ms(500);			
			WTN6_Line_1(Aft);		//��������
			Delay_ms(500);
		break;
		case 0x03:
			Delay_ms(500);			
			WTN6_Line_1(Nig);		//��������
			Delay_ms(500);
		break;	
	}
//����ʱ��
	if(Time[1] == 0x00)
	{
		Delay_ms(1000);			
		WTN6_Line_1(Time[2]);			
	}else
	{
		Delay_ms(1000);			
		WTN6_Line_1(Time[1]);
		
		Delay_ms(1000);			
		WTN6_Line_1(Time[2]);	
	}
	
	Delay_ms(1000);
	WTN6_Line_1(Dot);			//������
	
	Delay_ms(1000);
	WTN6_Line_1(OnHour);			//������
	Delay_ms(1000);

}



