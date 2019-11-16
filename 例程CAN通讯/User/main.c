/***********************************************************************
�ļ����ƣ�main.C
��    �ܣ�KEY_LED����ɨ������жϷ�ʽ
ʵ��ƽ̨������STM32F407VET6 ������
��汾  ��V1.2.1 
***********************************************************************/
#include "main.h"	

void Delay(vu32 nCount);
void KeyInit(void);
void  GetKey(void);

int main(void)
{
	/*
		ϵͳʱ��������system_stm32f4xx.c �ļ��е�SystemInit()������ʵ�֣���λ��ֱ���������ļ�������
	*/
	NVIC_Configuration(); 
	CAN1_Configuration();
	CAN2_Configuration();
	KeyInit();
	LED_GPIO_Config();
	while(1)
	{
		GetKey();
	}
}
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*�����ܽų�ʼ��*/
void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

       RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
	/********************��������***************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);	

}
/*����Ƿ��а�������*/
void  GetKey(void)
{
        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10))
        {
                Delay(1000000);//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)){ ; }//�ȴ������ͷ�
                       can1_tx(0x11,0xaa); 
					   LED1_OFF;	LED2_OFF;	LED3_OFF;
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11))
        {
                Delay(1000000);//ȥ����//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)){ ; }//�ȴ������ͷ�                        
                        can2_tx(0x22,0xbb); 
						LED1_OFF;	LED2_OFF;	LED3_OFF;
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12))
        {
                 Delay(1000000);//ȥ����//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)){ ; }//�ȴ������ͷ�                        
                        
						LED1_OFF;	LED2_OFF;	LED3_OFF;
                }
        }       

      
}