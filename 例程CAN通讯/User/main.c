/***********************************************************************
文件名称：main.C
功    能：KEY_LED按键扫描采用中断方式
实验平台：基于STM32F407VET6 开发板
库版本  ：V1.2.1 
***********************************************************************/
#include "main.h"	

void Delay(vu32 nCount);
void KeyInit(void);
void  GetKey(void);

int main(void)
{
	/*
		系统时钟配置在system_stm32f4xx.c 文件中的SystemInit()函数中实现，复位后直接在启动文件中运行
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
/*按键管脚初始化*/
void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

       RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
	/********************按键输入***************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);	

}
/*检测是否有按键按下*/
void  GetKey(void)
{
        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10))
        {
                Delay(1000000);//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)){ ; }//等待按键释放
                       can1_tx(0x11,0xaa); 
					   LED1_OFF;	LED2_OFF;	LED3_OFF;
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11))
        {
                Delay(1000000);//去抖动//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)){ ; }//等待按键释放                        
                        can2_tx(0x22,0xbb); 
						LED1_OFF;	LED2_OFF;	LED3_OFF;
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12))
        {
                 Delay(1000000);//去抖动//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)){ ; }//等待按键释放                        
                        
						LED1_OFF;	LED2_OFF;	LED3_OFF;
                }
        }       

      
}