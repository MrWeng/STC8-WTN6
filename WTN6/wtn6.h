#ifndef	_WTN6_H
#define	_WTN6_H

#include <intrins.h>
#include <STC8.h>

sbit	WNT6_DATA	=	P5^0;			//WTN6数据IO

/*								WTN6唯创知音语音内容地址对应表-2020年8月7日
|   语音内容	|	地址 |	*	|   语音内容	|	地址 |	*	|   语音内容	|	地址 |	*	|   语音内容	|	地址 |
|		1		|   0x00 |	*	|		8		|   0x08 |	*	|	  今天		|   0x10 |	*	|     晚上		|   0x18 |
|		1		|   0x01 |	*	|		9		|   0x09 |	*	|	   年		|   0x11 |	*	|     现在		|   0x19 |
|		2		|   0x02 |	*	|		*		|   0x0A |	*	|	   月		|   0x12 |	*	|      度		|   0x1A |
|		3		|   0x03 |	*	|		#		|   0x0B |	*	|	   日		|   0x13 |	*	|    百分之		|   0x1B |
|		4		|   0x04 |	*	|	  来电		|   0x0C |	*	|	   点		|   0x14 |	*	|				|   	 |
|		5		|   0x05 |	*	| “电话铃铃声”|   0x0D |	*	|	   整		|   0x15 |	*	|				|		 |
|		6		|   0x06 |	*	|	  温度		|   0x0E |	*	|	  上午		|   0x16 |	*	|				|        |
|		7		|   0x07 |	*	|	  湿度		|   0x0F |	*	|	  下午		|   0x17 |	*	|				|        |			
*/
//数字0-9
typedef enum WTN6_Number
{
	WTN6_N_0 = 0x00,
	WTN6_N_1,
	WTN6_N_2,
	WTN6_N_3,
	WTN6_N_4,
	WTN6_N_5,
	WTN6_N_6,
	WTN6_N_7,
	WTN6_N_8,
	WTN6_N_9,
}WTN6_Number_Type;

//符号类
typedef enum WTN6_Symbol
{
	WTN6_S_A  = 0x0A,					// *
	WTN6_S_N  = 0x0B,					// #
	WTN6_S_D  = 0x14,					//点
	WTN6_S_TC = 0x1A,					// °Celsius
	WTN6_S_TH = 0x1B,					//%	
}WTN6_Symbol_Type;

//来电、电话铃声（音乐）
typedef enum WTN6_Phone
{
	WTN6_P_IC  = 0x0C,					//来电Incoming Call
	WTN6_P_ICM = 0x0D,					//电话铃声（音乐）
}WTN6_Phone_Type;

//温度、湿度
typedef enum WTN6_TH
{
	WTN6_TH_Temp = 0x0E,				//温度
	WTN6_TH_Hum  = 0x0F,				//湿度
}WTN6_Temp_Type;

//日期
typedef enum WTN6_Date
{
	WTN6_D_TD 	= 0x10,					//今天
	WTN6_D_Y    = 0x11,					//年
	WTN6_D_M    = 0x12,					//月
	WTN6_D_D    = 0x13,					//日
}WTN6_Date_Type;

//时间
typedef enum WTN6_Time
{
	WTN6_T_O	  = 0x15,				//整
	WTN6_T_M 	  = 0x16,				//上午
	WTN6_T_A      = 0x17,				//下午
	WTN6_T_N      = 0x18,				//晚上
	WTN6_T_Now    = 0x19,				//现在
}WTN6_Time_Type;


/*
 *@brief 		微秒延时函数			
 *@param[in]	us：需要延时的微秒数
 */
extern void Delay_us(unsigned short int us);

/*
 *@brief 		毫秒延时函数
 *@param[in]	ms：需要延时的毫秒数
 */
extern void Delay_ms(unsigned short int ms);

/*
 *@brief 		WTN6 1线串口通信函数基础函数
 *				必须严格按照时序通信
 *@param[in]	Send_DATA：需要发送的的内容的地址，查看头文件
 */
static void WTN6_Line_1(unsigned char SB_DATA);

/*
 *@brief 		播报数字			
 *@param[in]	Num[]：需要播报的数字
 * 				Len	 ：数字长度	
 */
extern void WTN6_Num(unsigned char Num[],int Len);

/*
 *@brief 		播报温度	
 * 				只支持小数点后1位，播报内容为“温度XX点X度”
 *@param[in]	Num[]：需要播报的数字，最多3位，小数点不用包含，
 *			    例如23.8度，为Num[]={0x02,0x03,0x08}
 */
extern void WTN6_Temp(unsigned char Num[]);

/*
 *@brief 		播报湿度
 *				只支持小数点后1位，播报内容为“湿度百分之XX”
 *@param[in]	Num[]：需要播报的数字，最多3位，小数点不用包含，
 *			    例如60.8%，为Num[]={0x06,0x00,0x08}
 */
extern void WTN6_Hump(unsigned char Num[]);

/*
 *@brief 		来电铃声，响铃声（音乐形式）			
 *@param[in]	NULL
 */
extern void WTN6_Ring(void);

/*
 *@brief 		播报来电
 *				播报内容为“来电”
 *@param[in]	NULL
 */
extern void WTN6_InCall(void);

/*
 *@brief 		播报日期
 *				播报内容为“今天XXXX年X月X日”
 *@param[in]	Date：需要播报的日期
 *				例如：2020年8月18日，Date[]={0x02,0x00,0x02,0x00,0x00,0x08,0x01,0x08};
 */
extern void WTN6_ReportDate(unsigned char Date[]);

/*
 *@brief 		整点报时
 *				播报内容为“现在下午18点整”
 *@param[in]	Time：需要播报的时间。
 *				Time[0]=0x01    上午
 *				Time[0]=0x02 	下午
 *				Time[0]=0x03     晚上
 *				例如：下午18点，Date[]={0x02,0x01,0x08}，
 */
extern void WTN6_ReportTime(unsigned char Time[]);
#endif