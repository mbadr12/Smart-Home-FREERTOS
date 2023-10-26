/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	ADC 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#ifndef COTS_1_MCAL_5_ADC_ADC_INTERFACE_H_
#define COTS_1_MCAL_5_ADC_ADC_INTERFACE_H_

typedef struct
{
	u8 *Channel;
	u8 Size;
	void(*NotificationFunc)(void);
	u16 *Result;
}Chain_t;

typedef struct
{
	s16 Copy_u16InputMini;
	s16 Copy_u16InputMax;
	s16 Copy_u16outMini;
	s16 Copy_u16outMax;
}Map;

s16 ADC_S16ReadingMap(Map *Map,s16 Copy_u16InputValue);

void ADC_voidInit(void);

u16 ADC_u16StartConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Reading);

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Reading,void (*Copy_pvNotififcationFunc)(void));

u8 ADC_u8startChainConversionAsynch(Chain_t *Copy_Chain);

#endif /* COTS_1_MCAL_5_ADC_ADC_INTERFACE_H_ */
