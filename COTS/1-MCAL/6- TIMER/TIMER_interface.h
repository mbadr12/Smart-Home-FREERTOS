/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	TIMER 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/
#ifndef COTS_1_MCAL_6__TIMER_TIMER_INTERFACE_H_
#define COTS_1_MCAL_6__TIMER_TIMER_INTERFACE_H_

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

#define ICU_RaisingEdge 	1
#define ICU_FallingEdge 	0

#define OVERFLOW_INT 		0
#define CTC_INT				1
#define ICU_INT				2

#define TIMER0_OVF_INT		0
#define TIMER0_COMP_INT		1
#define TIMER1_OVF_INT		2
#define TIMER1_COMPA_INT	3
#define TIMER1_COMPB_INT	4
#define TIMER1_CAPT_INT		5
#define TIMER2_OVF_INT		6
#define TIMER2_COMP_INT		7

#define SERVO_CHANNEL1		1
#define SERVO_CHANNEL2		2

void TIMER0_voidInit(void);

void TIMER1_voidInit(void);

void TIMER2_voidInit(void);

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value);

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value);

#endif /* COTS_1_MCAL_6__TIMER_TIMER_INTERFACE_H_ */
