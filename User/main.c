#include "delay.h"
#include "usart.h"	 
#include "dht11.h" 
#include "sys.h"
#include "relay.h"
#include "onenet.h"
#include "esp8266.h"

/************************************
*          ���ܼҾ�ϵͳ

*                  date��2018-06-30
**CSDN Blog:https://blog.csdn.net/qq_33475105
*************************************/

void hardware_init(void)
{
		  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
   delay_init();	    	 //��ʱ������ʼ��
	 uart_init(115200);	//���ڳ�ʼ��Ϊ115200	
	 Usart2_Init(115200);							//����2������ESP8266��
	 while(DHT11_Init())	//DHT11��ʼ��	
	{
		printf( "DTH11 error!\r\n");
		delay_ms(200);
	 }	
   relay_init();//�̵�����ʼ��
	 ESP8266_Init();					//��ʼ��ESP8266
	 UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	
}


 int main(void)
 {	 
	unsigned char *dataPtr = NULL;
	unsigned short timeCount = 0;	//���ͼ������	
	 
  hardware_init(); //Ӳ����ʼ��
	
	while(OneNet_DevLink())		//����OneNET
		DelayXms(500);
							   	 
	while(1)
	{
		
		
		if(++timeCount >= 500)									//���ͼ��5s
		{
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
			OneNet_SendData();									//��������
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		OneNet_RevPro(dataPtr);
		
		DelayXms(10);
	
	}
}

