/*
 * main.c
 *
 *  Created on: Feb 25, 2023
 *      Author: mbadr
 */
#include "COTS/4-LIB/STD_TYPES.h"

#include "COTS/FreeRTOS_SourceFiles/FreeRTOS.h"
#include "COTS/FreeRTOS_SourceFiles/task.h"
#include "COTS/FreeRTOS_SourceFiles/semphr.h"

#include "COTS/1-MCAL/1-DIO/DIO_interface.h"
#include "COTS/1-MCAL/2-PORT/PORT_interface.h"
#include "COTS/1-MCAL/4-GIE/GIE_interface.h"
#include "COTS/1-MCAL/5-ADC/ADC_interface.h"
#include "COTS/1-MCAL/6- TIMER/TIMER_interface.h"

#include "COTS/2-HAL/4-CLCD/CLCD_interface.h"
#include "COTS/2-HAL/5-KEYPAD/KEYPAD_interface.h"
#include "COTS/2-HAL/6-MOTORS/MOTORS_interface.h"

void KeypadTask(void *pv);

void TempTask(void *pv);

void BuzzerTask(void *pv);

void DoorTask(void *pv);

void FanTask(void *pv);

void TempNotificaton(void);

u32 ConvertPass(u8* PassArr,u8 PassLen);

u16 CorrectPass=1234;

u8 EnteredPass[4]={0};

u16 Temp;

u8 CorrectFlag=0;

u8 BuzzerFlag=0;

u8 TempFlag=0;

xSemaphoreHandle LCDSem;

xSemaphoreHandle DoorSem;

xSemaphoreHandle TempSem;

int main(void)
{
	PORT_voidInit();
	ADC_voidInit();
	CLCD_void_Init();
	GIE_voidEnable();
	TIMER2_voidInit();
	CLCD_voidSendString("welcome");
	LCDSem=xSemaphoreCreateCounting(1,1);
	DoorSem=xSemaphoreCreateCounting(1,0);
	TempSem=xSemaphoreCreateCounting(1,0);
	xTaskCreate(KeypadTask,NULL,250,NULL,5,NULL);
	xTaskCreate(DoorTask,NULL,150,NULL,3,NULL);
	xTaskCreate(FanTask,NULL,150,NULL,2,NULL);
	xTaskCreate(TempTask,NULL,150,NULL,4,NULL);
	xTaskCreate(BuzzerTask,NULL,150,NULL,5,NULL);
	vTaskStartScheduler();
	while(1);
}

void KeypadTask(void *pv)
{
	u32 Pass=0;
	u8 Entered=0;
	u8 SemState=0;
	while(1)
	{
		static u8 Local_Trails=0;
		static u8 Local_Counter=0;
		Entered=KPD_u8GetPressedKey();
		SemState=xSemaphoreTake(LCDSem,35);
		if(Entered!=0xff)
		{
			EnteredPass[Local_Counter]=Entered;
			if(SemState == pdTRUE)
			{
				CLCD_voidGoToXY(0,Local_Counter);
				CLCD_voidSendData('*');
				xSemaphoreGive(LCDSem);
			}
			Local_Counter++;
		}
		if(Local_Counter==4)
		{
			Local_Counter=0;
			Pass=ConvertPass(EnteredPass,4);
			if(Pass == CorrectPass)
			{
				xSemaphoreGive(DoorSem);
			}
			else
			{
				Local_Trails++;
			}
			if(Local_Trails==3)
			{
				BuzzerFlag=1;
			}
		}
		vTaskDelay(100);
	}
}

void TempTask(void *pv)
{
	u8 SemState=0;
	while(1)
	{
		SemState=xSemaphoreTake(TempSem,25);
		if(SemState == pdPASS)
		{
			ADC_u8StartConversionAsynch(5,&Temp,TempNotificaton);
			Temp*=2;
			TempFlag=1;
		}
		vTaskDelay(250);
	}
}

void BuzzerTask(void *pv)
{
	while(1)
	{
		static u8 Counter=0;
		if(BuzzerFlag==1)
		{
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendString("Warning");
			DIO_u8TogglePinValue(DIO_u8PORTA,DIO_u8PIN4);
			DIO_u8TogglePinValue(DIO_u8PORTA,DIO_u8PIN5);
			Counter++;
		}
		if(Counter==10)
		{
			BuzzerFlag=0;
			Counter=0;
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8Pin_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8Pin_LOW);
		}
		vTaskDelay(500);
	}
}

void DoorTask(void *pv)
{
	DC_MOTOR Motor={DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN2};
	u8 SemState=0;
	while(1)
	{
		SemState= xSemaphoreTake(DoorSem,35);
		static u8 Index=0;
		static u8 Close=4;
		if((SemState == pdPASS) && ( Index==0 ))
		{
			Index++;
			DC_u8Rotate(&Motor,CW);
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendString("Door Opening");
		}
		else if((Index>0)&&(Index<8))
		{
			Index++;
		}
		if(Index==8)
		{
			CorrectFlag=0;
			Close--;
			DC_u8Rotate(&Motor,CCW);
			if(Close==0)
			{
				DC_u8Stop(&Motor);
				Index=0;
				CLCD_voidCLR();
				CLCD_voidSendString("Door Closed");
				Close=4;
			}
		}
		vTaskDelay(1000);
	}
}

void FanTask(void *pv)
{
	u8 SemState=0;
	while(1)
	{
		if(TempFlag==1)
		{
			SemState=xSemaphoreTake(LCDSem,35);
			if(SemState==pdTRUE)
			{
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Temp=");
				CLCD_void_SendNumber(Temp);
				CLCD_voidGoToXY(1,8);
				if((Temp>27) && (Temp<=30))
				{
					TIMER2_voidSetCompMatchValue(85);
					CLCD_voidSendString(" Fan 33%");
				}
				else if((Temp>30) && (Temp<=35))
				{
					TIMER2_voidSetCompMatchValue(170);
					CLCD_voidSendString(" Fan 67%");
				}
				else if(Temp>35)
				{
					TIMER2_voidSetCompMatchValue(255);
					CLCD_voidSendString("Fan 100%");
				}
				else
				{
					TIMER2_voidSetCompMatchValue(0);
					CLCD_voidSendString(" Fan OFF");
				}
				TempFlag=0;
				xSemaphoreGive(LCDSem);
			}
		}
		vTaskDelay(1000);
	}
}

void TempNotificaton(void)
{
	xSemaphoreGive(TempSem);
}

u32 ConvertPass(u8* PassArr,u8 PassLen)
{
	u32 Pass=0;
	u32 Temp=0;
	for(u8 Index=0;Index<PassLen;Index++)
	{
		Temp=PassArr[Index]-'0';
		for(u8 Power=0;Power<(PassLen-Index-1);Power++)
		{
			Temp*=10;
		}
		Pass += Temp;
	}
	return Pass;
}
