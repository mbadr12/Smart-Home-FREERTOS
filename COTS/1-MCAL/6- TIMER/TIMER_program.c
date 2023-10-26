/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	TIMER 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"

void TIMER0_voidInit(void)
{
	/*choose Wave Generation Mode*/
#if TIMER0_GENERATION_MODE == TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);
	/*Over Flow Interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_TOIE0);
#elif TIMER0_GENERATION_MODE == TIMER0_PWM_PHASE_CORRECT_MODE
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
#elif TIMER0_GENERATION_MODE == TIMER0_CTC_MODE
	SET_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);
	/*Output Compare Match Interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);
#elif TIMER0_GENERATION_MODE == TIMER0_FAST_PWM_MODE
	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);
#else
#error "Wrong Generation mode"
#endif
	/*Compare match output mode*/
	TCCR0&=COMP_OPMODE_MASK;
	TCCR0|=TIMER0_COMPARE_OUTPUT_MODE;
	/*Prescaler*/
	TCCR0&=TIMER_PRESCALER_MASK;
	TCCR0|=TIMER0_PRESCALER;
}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

void TIMER2_voidInit(void)
{
	/*choose Wave Generation Mode*/
#if TIMER2_GENERATION_MODE == TIMER2_NORMAL_MODE
	CLR_BIT(TCCR2,TCCR2_WGM21);
	CLR_BIT(TCCR2,TCCR2_WGM20);
	/*Overflow Interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_TOIE2);
#elif TIMER2_GENERATION_MODE == TIMER2_PWM_PHASE_CORRECT_MODE
	SET_BIT(TCCR2,TCCR0_WGM20);
	CLR_BIT(TCCR2,TCCR0_WGM21);
#elif TIMER2_GENERATION_MODE == TIMER2_CTC_MODE
	SET_BIT(TCCR2,TCCR2_WGM21);
	CLR_BIT(TCCR2,TCCR2_WGM20);
	/*Output Compare Match Interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCIE2);
#elif TIMER2_GENERATION_MODE == TIMER2_FAST_PWM_MODE
	SET_BIT(TCCR2,TCCR2_WGM21);
	SET_BIT(TCCR2,TCCR2_WGM20);
#else
#error "Wrong Generation mode"
#endif
	/*Compare match output mode*/
	TCCR2&=COMP_OPMODE_MASK;
	TCCR2|=TIMER2_COMPARE_OUTPUT_MODE;
	/*Prescaler*/
	TCCR2&=TIMER_PRESCALER_MASK;
	TCCR2|=TIMER2_PRESCALER;
}

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value)
{
	OCR2=Copy_u8Value;
}
