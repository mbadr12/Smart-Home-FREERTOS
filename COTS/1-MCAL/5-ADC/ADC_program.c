/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	ADC 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_register.h"

static u16* ADC_pu16Reading=NULL;
static void (*ADC_pvCallBackNotificationFunc)(void)=NULL;
static u8 ADC_u8BusyState=IDLE;
static u8 *ADC_pu8chainChannelArr=NULL;
static u8 ADC_u8ChainSize=0;
static u16 *ADC_pu16ChainResultArr=NULL;
static u8 ADC_u8ChainConversionIndex=0;
static u8 ADC_u8ISRSource;

void ADC_voidInit(void)
{
	/*AVCC as reference voltage*/
#if ADC_REF_VOLTAGE==AREF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_REF_VOLTAGE==AVCC
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_REF_VOLTAGE==INTERNAL
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error "Wrong Voltage Reference"
#endif
#if ADC_RES==EIGHT_BIT
	/*Activate left adjust result*/
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_RES==TEN_BIT
	/*SET Right Adjust Result*/
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong Resolution"
#endif
	/*SET pre-scaler to divide by 128*/
	ADCSRA&=PRE_SCALERMASK;
	ADCSRA|=ADC_PRE_SCALER;
	/*Enable ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#if ADC_CONVERSION_MODE==AUTO_TRIGGER
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	/*Setting Auto Trigger Source*/
	SFIOR&=SOURCE_MASK;
	SFIOR|=(AUTO_TRIGGER_SOURCE<<5);
	/*Start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);
#elif ADC_CONVERSION_MODE==SINGLE_MODE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#else
#error "Wrong Conversion Mode"
#endif
}

u16 ADC_u16StartConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Reading)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		/*ADC is now Busy*/
		ADC_u8BusyState=BUSY;
		/*Clear The MUX bits in ADmux register*/
		ADMUX &=ADMUX_MASK;
		/*Set the required channel into the MUX bits*/
		ADMUX|=Copy_u8Channel;
		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/*polling (Busy waiting) until the conversion complete flag is set*/
		while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) && (Local_u32Counter != ADC_u32TIMEOUT))
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter==ADC_u32TIMEOUT)
		{
			/*Loop is broken as the time out is reached*/
			Local_u8ErrorState=NOK;
		}
		else
		{
			/*Loop is broken as flag is raised*/
			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);
			#if ADC_RES==EIGHT_BIT
				*Copy_pu16Reading = ADCH;
			#elif ADC_RES==TEN_BIT
				*Copy_pu16Reading = ADC;
			#else
			#error "Wrong Conversion Mode"
			#endif
			/*ADC is finished, return it to IDLE*/
			ADC_u8BusyState=IDLE;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Reading,void (*Copy_pvNotififcationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		if((Copy_pu16Reading == NULL) || (Copy_pvNotififcationFunc == NULL))
		{
			Local_u8ErrorState=NULL_POINTER;
		}
		else
		{
			ADC_u8BusyState=BUSY;
			ADC_u8ISRSource=SINGLE_CHANNEL_ASYNCH;
			/*Initialize the reading variable & CallBack Notification Function Globally*/
			ADC_pu16Reading=Copy_pu16Reading;
			ADC_pvCallBackNotificationFunc=Copy_pvNotififcationFunc;
			/*Clear The MUX bits in ADmux register*/
			ADMUX &=ADMUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX|=Copy_u8Channel;
			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*ADC Interrupt Enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
u8 ADC_u8startChainConversionAsynch(Chain_t *Copy_Chain)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_Chain==NULL)
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	else
	{
		if(ADC_u8BusyState==IDLE)
		{
			ADC_u8BusyState=BUSY;
			ADC_u8ISRSource=CHAIN_ASYNCH;
			/*Initialize the reading variable & CallBack Notification Function Globally*/
			ADC_pu8chainChannelArr=Copy_Chain->Channel;
			ADC_pvCallBackNotificationFunc=Copy_Chain->NotificationFunc;
			ADC_pu16ChainResultArr=Copy_Chain->Result;
			ADC_u8ChainSize=Copy_Chain->Size;
			ADC_u8ChainConversionIndex=0;
			/*Clear The MUX bits in ADmux register*/
			ADMUX &=ADMUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX|=ADC_pu8chainChannelArr[ADC_u8ChainConversionIndex];
			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*ADC Interrupt Enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=BUSY_FUNC;
		}
	}
	return Local_u8ErrorState;
}
void __vector_16 (void)  __attribute__((signal));

void __vector_16 (void)
{
	if(ADC_u8ISRSource==SINGLE_CHANNEL_ASYNCH)
	{
		/*Read ADC Reading*/
		#if ADC_RES==EIGHT_BIT
			*ADC_pu16Reading = ADCH;
		#elif ADC_RES==TEN_BIT
			*ADC_pu16Reading = ADC;
		#else
		#error "Wrong Conversion Mode"
		#endif
		/*Make ADC_u8BusyState Ideal*/
		ADC_u8BusyState=IDLE;
		/*Invoke the call Back Notification*/
		ADC_pvCallBackNotificationFunc();
		/*Disable ADC conversion Complete Interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource==CHAIN_ASYNCH)
	{
		#if ADC_RES==EIGHT_BIT
			ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADCH;
		#elif ADC_RES==TEN_BIT
			ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADC;
		#else
		#error "Wrong Conversion Mode"
		#endif
		ADC_u8ChainConversionIndex++;
		if(ADC_u8ChainConversionIndex==ADC_u8ChainSize)
		{
			/*Make ADC_u8BusyState Ideal*/
			ADC_u8BusyState=IDLE;
			/*Invoke the call Back Notification*/
			ADC_pvCallBackNotificationFunc();
			/*Disable ADC conversion Complete Interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*Clear The MUX bits in ADmux register*/
			ADMUX &=ADMUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX|=ADC_pu8chainChannelArr[ADC_u8ChainConversionIndex];
			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
s16 ADC_S16ReadingMap(Map *Map,s16 Copy_u16InputValue)
{
	u16 Local_u16MappedValue=0;
	Local_u16MappedValue=(Map->Copy_u16outMax-Map->Copy_u16outMini);
	Local_u16MappedValue/=(Map->Copy_u16InputMax-Map->Copy_u16InputMini);
	Local_u16MappedValue*=(Copy_u16InputValue-Map->Copy_u16InputMini);
	Local_u16MappedValue+=Map->Copy_u16outMini;
	return Local_u16MappedValue;
}
