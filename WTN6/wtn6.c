#include "wtn6.h"

/*
 *@brief 		1微秒延时基础函数
 *				STC-ISP软件生成
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
 *@brief 		微秒延时函数
 *				
 *@param[in]	us：需要延时的微秒数
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
 *@brief 		1毫秒延时基础函数
 *				STC-ISP软件生成
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
 *@brief 		毫秒延时函数
 *				
 *@param[in]	ms：需要延时的毫秒数
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
 *@brief 		WTN6 1线串口通信函数基础函数
 *				必须严格按照时序通信
 *@param[in]	Send_DATA：需要发送的的内容的地址，查看头文件
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Line_1(unsigned char Send_DATA)
{
	unsigned char S_DATA,j;
	bit B_DATA;
	S_DATA =Send_DATA;
	WNT6_DATA=0;
	Delay_ms(5);		//延时5毫秒			
	B_DATA = S_DATA&0X01;
	for(j=0;j<8;j++) 
	{ 
		if(B_DATA == 1) 
	{ 
		WNT6_DATA = 1; 
		Delay_us(600); //延时 600us 
		WNT6_DATA = 0; 
		Delay_us(200); //延时 200us 
	} 
	else 
	{ 
		WNT6_DATA = 1; 
		Delay_us(200); //延时 200us 
		WNT6_DATA = 0; 
		Delay_us(600); //延时 600us 
	} 
		S_DATA = S_DATA>>1; 
		B_DATA = S_DATA&0X01; 
	} 
		WNT6_DATA = 1;
}

/*
 *@brief 		播报数字			
 *@param[in]	Num[]：需要播报的数字
 * 				Len	 ：数字长度	
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Num(unsigned char Num[],int Len)
{
	int i;
	for(i=0;i<Len;i++)
		{	
			Delay_ms(500);			//延时1秒
			WTN6_Line_1(Num[i]);
			Delay_ms(500);
		}
}
/*
 *@brief 		播报温度	
 * 				只支持小数点后1位，播报内容为“温度XX点X度”
 *@param[in]	Num[]：需要播报的数字，最多3位，小数点不用包含，
 *			    例如23.8度，为Num[]={0x02,0x03,0x08}		
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Temp(unsigned char Num[])
{
	WTN6_Temp_Type temp;						//温度
	WTN6_Symbol_Type Celsius,Dot;			   //摄氏度,点
	
	temp 	=  WTN6_TH_Temp;	
	Celsius =  WTN6_S_TC;	
	Dot		=  WTN6_S_D;
	
	//格式：温度 23.5度
	Delay_ms(1000);					
	WTN6_Line_1(temp);							//播报温度
	
	Delay_ms(1500);					
	WTN6_Line_1(Num[0]);						//温度十位
	
	Delay_ms(1000);					
	WTN6_Line_1(Num[1]);						//温度个位
	
	Delay_ms(1000);					
	WTN6_Line_1(Dot);							//播报点
	
	Delay_ms(1000);			
	WTN6_Line_1(Num[2]);						//温度小数位
	
	Delay_ms(1000);			
	WTN6_Line_1(Celsius);						//播报度
}

/*
 *@brief 		播报湿度
 *				只支持小数点后1位，播报内容为“湿度百分之XX”
 *@param[in]	Num[]：需要播报的数字，最多3位，小数点不用包含，
 *			    例如60.8%，为Num[]={0x06,0x00,0x08}
 *@author		MrWeng
 *@date			2020-8-7
 */
void WTN6_Hump(unsigned char Num[])
{
	WTN6_Temp_Type hum;							//湿度
	WTN6_Symbol_Type Per_Cent,Dot;				//百分之,点
	
	hum	 	 = WTN6_TH_Hum;
	Dot		 = WTN6_S_D;
	Per_Cent = WTN6_S_TH;
	
	//格式：温度 23.5%
	Delay_ms(1000);					
	WTN6_Line_1(hum);							//播报湿度
	
	Delay_ms(1500);			
	WTN6_Line_1(Per_Cent);						//播报百分之
	
	Delay_ms(1500);					
	WTN6_Line_1(Num[0]);						//温度十位
	
	Delay_ms(1000);					
	WTN6_Line_1(Num[1]);						//温度个位
	
	Delay_ms(1000);					
	WTN6_Line_1(Dot);							//播报点
	
	Delay_ms(1000);			
	WTN6_Line_1(Num[2]);						//温度小数位	
}

/*
 *@brief 		来电铃声，响铃声（音乐形式）			
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
 *@brief 		播报来电
 *				播报内容为“来电”
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
  *@brief 		播报日期
 *				播报内容为“今天XXXX年X月X日”
 *@param[in]	Date：需要播报的日期
 *				例如：2020年8月18日，Date[]={0x02,0x00,0x02,0x00,0x00,0x08,0x01,0x08};
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
	
//播报年	
	for(i=0;i<4;i++)
	{	
		Delay_ms(500);			
		WTN6_Line_1(Date[i]);
		Delay_ms(500);
	}
	
	Delay_ms(500);			
	WTN6_Line_1(Year);
	Delay_ms(1000);
//播报月	
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
//播报日	
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
 *@brief 		整点报时
 *				播报内容为“现在下午18点整”
 *@param[in]	Time：需要播报的时间。
 *				Time[0]=0x01    上午
 *				Time[0]=0x02 	下午
 *				Time[0]=0x03     晚上
 *				例如：下午18点，Date[]={0x02,0x01,0x08}，
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
	WTN6_Line_1(Now);				//播报现在
	Delay_ms(1000);
	
	switch(Time[0])
	{
		case 0x01:
			Delay_ms(500);			
			WTN6_Line_1(Mor);		//播报上午
			Delay_ms(500);
		break;
		case 0x02:
			Delay_ms(500);			
			WTN6_Line_1(Aft);		//播报下午
			Delay_ms(500);
		break;
		case 0x03:
			Delay_ms(500);			
			WTN6_Line_1(Nig);		//播报晚上
			Delay_ms(500);
		break;	
	}
//播报时间
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
	WTN6_Line_1(Dot);			//播报点
	
	Delay_ms(1000);
	WTN6_Line_1(OnHour);			//播报整
	Delay_ms(1000);

}



