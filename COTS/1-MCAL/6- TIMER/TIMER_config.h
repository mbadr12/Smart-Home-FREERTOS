/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	TIMER 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#ifndef COTS_1_MCAL_6__TIMER_TIMER_CONFIG_H_
#define COTS_1_MCAL_6__TIMER_TIMER_CONFIG_H_

/*choose Timer0 Waveform Generation Mode:
 * 1- TIMER0_NORMAL_MODE
 * 2- TIMER0_PWM_PHASE_CORRECT_MODE
 * 3- TIMER0_CTC_MODE
 * 4- TIMER0_FAST_PWM_MODE*/
#define TIMER0_GENERATION_MODE TIMER0_FAST_PWM_MODE

/*Choose Timer0 Compare Output Mode:
 * For Non-PWM mode:
 * 1- TIMER0_NORMAL: Normal port operation, OC0 disconnected
 * 2- TIMER0_TOGGLE_OC0: Toggle OC0 on compare match
 * 3- TIMER0_CLR_OC0: Clear OC0 on compare match
 * 4- TIMER0_SET_OC0: Set OC0 on compare match
 * For Fast PWM mode:
 * 1- TIMER0_NORMAL: Normal port operation, OC0 disconnected
 * 2- TIMER0_Reserved
 * 3- TIMER0_CLR_ON_COMP_SET_AT_TOP: Clear OC0 on compare match, set OC0 at TOP
 * 4- TIMER0_SET_ON_COMP_CLR_AT_TOP: Set OC0 on compare match, clear OC0 at TOP*/
#define TIMER0_COMPARE_OUTPUT_MODE TIMER0_CLR_ON_COMP_SET_AT_TOP

/*Choose Pre-scaler
 * 1- NO_CLK_SRC
 * 2- NO_DIV
 * 3- DIV_BY_8
 * 4- DIV_BY_64
 * 5- DIV_BY_256
 * 6- DIV_BY_1024
 * 7- EXT_CLK_FALL_EDGE
 * 8- EXT_CLK_RAIS_EDGESCALER DIV_BY_128 */
#define TIMER0_PRESCALER DIV_BY_8

#define TIMER2_PRESCALER DIV_BY_64

#define TIMER2_GENERATION_MODE TIMER2_FAST_PWM_MODE

/*Choose Timer2 Compare Output Mode:
 * For Non-PWM mode:
 * 1- TIMER2_NORMAL: Normal port operation, OC0 disconnected
 * 2- TIMER2_TOGGLE_OC0: Toggle OC0 on compare match
 * 3- TIMER2_CLR_OC0: Clear OC0 on compare match
 * 4- TIMER2_SET_OC0: Set OC0 on compare match
 * For Fast PWM mode:
 * 1- TIMER2_NORMAL: Normal port operation, OC0 disconnected
 * 2- TIMER2_Reserved
 * 3- TIMER2_CLR_ON_COMP_SET_AT_TOP: Clear OC0 on compare match, set OC0 at TOP
 * 4- TIMER2_SET_ON_COMP_CLR_AT_TOP: Set OC0 on compare match, clear OC0 at TOP*/
#define TIMER2_COMPARE_OUTPUT_MODE TIMER2_CLR_ON_COMP_SET_AT_TOP

#endif /* COTS_1_MCAL_6__TIMER_TIMER_CONFIG_H_ */
