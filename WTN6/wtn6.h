#ifndef	_WTN6_H
#define	_WTN6_H

#include <intrins.h>
#include <STC8.h>

sbit	WNT6_DATA	=	P5^0;			//WTN6����IO

/*								WTN6Ψ��֪���������ݵ�ַ��Ӧ��-2020��8��7��
|   ��������	|	��ַ |	*	|   ��������	|	��ַ |	*	|   ��������	|	��ַ |	*	|   ��������	|	��ַ |
|		1		|   0x00 |	*	|		8		|   0x08 |	*	|	  ����		|   0x10 |	*	|     ����		|   0x18 |
|		1		|   0x01 |	*	|		9		|   0x09 |	*	|	   ��		|   0x11 |	*	|     ����		|   0x19 |
|		2		|   0x02 |	*	|		*		|   0x0A |	*	|	   ��		|   0x12 |	*	|      ��		|   0x1A |
|		3		|   0x03 |	*	|		#		|   0x0B |	*	|	   ��		|   0x13 |	*	|    �ٷ�֮		|   0x1B |
|		4		|   0x04 |	*	|	  ����		|   0x0C |	*	|	   ��		|   0x14 |	*	|				|   	 |
|		5		|   0x05 |	*	| ���绰��������|   0x0D |	*	|	   ��		|   0x15 |	*	|				|		 |
|		6		|   0x06 |	*	|	  �¶�		|   0x0E |	*	|	  ����		|   0x16 |	*	|				|        |
|		7		|   0x07 |	*	|	  ʪ��		|   0x0F |	*	|	  ����		|   0x17 |	*	|				|        |			
*/
//����0-9
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

//������
typedef enum WTN6_Symbol
{
	WTN6_S_A  = 0x0A,					// *
	WTN6_S_N  = 0x0B,					// #
	WTN6_S_D  = 0x14,					//��
	WTN6_S_TC = 0x1A,					// ��Celsius
	WTN6_S_TH = 0x1B,					//%	
}WTN6_Symbol_Type;

//���硢�绰���������֣�
typedef enum WTN6_Phone
{
	WTN6_P_IC  = 0x0C,					//����Incoming Call
	WTN6_P_ICM = 0x0D,					//�绰���������֣�
}WTN6_Phone_Type;

//�¶ȡ�ʪ��
typedef enum WTN6_TH
{
	WTN6_TH_Temp = 0x0E,				//�¶�
	WTN6_TH_Hum  = 0x0F,				//ʪ��
}WTN6_Temp_Type;

//����
typedef enum WTN6_Date
{
	WTN6_D_TD 	= 0x10,					//����
	WTN6_D_Y    = 0x11,					//��
	WTN6_D_M    = 0x12,					//��
	WTN6_D_D    = 0x13,					//��
}WTN6_Date_Type;

//ʱ��
typedef enum WTN6_Time
{
	WTN6_T_O	  = 0x15,				//��
	WTN6_T_M 	  = 0x16,				//����
	WTN6_T_A      = 0x17,				//����
	WTN6_T_N      = 0x18,				//����
	WTN6_T_Now    = 0x19,				//����
}WTN6_Time_Type;


/*
 *@brief 		΢����ʱ����			
 *@param[in]	us����Ҫ��ʱ��΢����
 */
extern void Delay_us(unsigned short int us);

/*
 *@brief 		������ʱ����
 *@param[in]	ms����Ҫ��ʱ�ĺ�����
 */
extern void Delay_ms(unsigned short int ms);

/*
 *@brief 		WTN6 1�ߴ���ͨ�ź�����������
 *				�����ϸ���ʱ��ͨ��
 *@param[in]	Send_DATA����Ҫ���͵ĵ����ݵĵ�ַ���鿴ͷ�ļ�
 */
static void WTN6_Line_1(unsigned char SB_DATA);

/*
 *@brief 		��������			
 *@param[in]	Num[]����Ҫ����������
 * 				Len	 �����ֳ���	
 */
extern void WTN6_Num(unsigned char Num[],int Len);

/*
 *@brief 		�����¶�	
 * 				ֻ֧��С�����1λ����������Ϊ���¶�XX��X�ȡ�
 *@param[in]	Num[]����Ҫ���������֣����3λ��С���㲻�ð�����
 *			    ����23.8�ȣ�ΪNum[]={0x02,0x03,0x08}
 */
extern void WTN6_Temp(unsigned char Num[]);

/*
 *@brief 		����ʪ��
 *				ֻ֧��С�����1λ����������Ϊ��ʪ�Ȱٷ�֮XX��
 *@param[in]	Num[]����Ҫ���������֣����3λ��С���㲻�ð�����
 *			    ����60.8%��ΪNum[]={0x06,0x00,0x08}
 */
extern void WTN6_Hump(unsigned char Num[]);

/*
 *@brief 		������������������������ʽ��			
 *@param[in]	NULL
 */
extern void WTN6_Ring(void);

/*
 *@brief 		��������
 *				��������Ϊ�����硱
 *@param[in]	NULL
 */
extern void WTN6_InCall(void);

/*
 *@brief 		��������
 *				��������Ϊ������XXXX��X��X�ա�
 *@param[in]	Date����Ҫ����������
 *				���磺2020��8��18�գ�Date[]={0x02,0x00,0x02,0x00,0x00,0x08,0x01,0x08};
 */
extern void WTN6_ReportDate(unsigned char Date[]);

/*
 *@brief 		���㱨ʱ
 *				��������Ϊ����������18������
 *@param[in]	Time����Ҫ������ʱ�䡣
 *				Time[0]=0x01    ����
 *				Time[0]=0x02 	����
 *				Time[0]=0x03     ����
 *				���磺����18�㣬Date[]={0x02,0x01,0x08}��
 */
extern void WTN6_ReportTime(unsigned char Time[]);
#endif