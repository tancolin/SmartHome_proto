#include "delay.h"
#include "usart.h"	 
#include "dht11.h" 
#include "sys.h"
#include "relay.h"
#include "onenet.h"
#include "esp8266.h"

/************************************
*          智能家居系统

*                  date：2018-06-30
**CSDN Blog:https://blog.csdn.net/qq_33475105
*************************************/

void hardware_init(void)
{
		  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
   delay_init();	    	 //延时函数初始化
	 uart_init(115200);	//串口初始化为115200	
	 Usart2_Init(115200);							//串口2，驱动ESP8266用
	 while(DHT11_Init())	//DHT11初始化	
	{
		printf( "DTH11 error!\r\n");
		delay_ms(200);
	 }	
   relay_init();//继电器初始化
	 ESP8266_Init();					//初始化ESP8266
	 UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	
}


 int main(void)
 {	 
	unsigned char *dataPtr = NULL;
	unsigned short timeCount = 0;	//发送间隔变量	
	 
  hardware_init(); //硬件初始化
	
	while(OneNet_DevLink())		//接入OneNET
		DelayXms(500);
							   	 
	while(1)
	{
		
		
		if(++timeCount >= 500)									//发送间隔5s
		{
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
			OneNet_SendData();									//发送数据
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		OneNet_RevPro(dataPtr);
		
		DelayXms(10);
	
	}
}

