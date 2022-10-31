/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to init, reset, enable disable, all timers and match registers
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer/timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0, 1, 2, 3
** Returned value:		None
**
******************************************************************************/
_Bool timer_status( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
		return (LPC_TIM0->TCR);
  }
  else if ( timer_num == 1 )
  {
		return (LPC_TIM0->TCR);
  }
	else if ( timer_num == 2 )
  {
		return (LPC_TIM0->TCR);
  }
	else if ( timer_num == 3 )
  {
		return (LPC_TIM0->TCR);
  }
	return 0;
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0, 1, 2, 3
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
		LPC_TIM0->TCR = 1;
  }
  else if ( timer_num == 1 )
  {
		LPC_TIM1->TCR = 1;
  }
	else if ( timer_num == 2 )
  {
		LPC_TIM2->TCR = 1;
  }
	else if ( timer_num == 3 )
  {
		LPC_TIM3->TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0, 1, 2, 3
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
		LPC_TIM0->TCR = 0;
  }
  else if ( timer_num == 1 )
  {
		LPC_TIM1->TCR = 0;
  }
	else if ( timer_num == 2 )
  {
		LPC_TIM2->TCR = 0;
  }
	else if ( timer_num == 3 )
  {
		LPC_TIM3->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timers counter without stopping it
**
** parameters:			timer number: 0, 1, 2, 3
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
	if ( timer_num == 0 )
  {
		LPC_TIM0->TC=0;
  }
  else if ( timer_num == 1 )
  {
		LPC_TIM1->TC=0;
  }
	else if ( timer_num == 2 )
  {
		LPC_TIM2->TC=0;
  }
	else if ( timer_num == 3 )
  {
		LPC_TIM3->TC=0;
  }
	
  return;
}

uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval0, uint32_t TimerInterval1, uint32_t TimerInterval2, uint32_t TimerInterval3, uint32_t PrescaleValue )
{
  if ( timer_num == 0 )
  {
		if( TimerInterval0 != 0)
			LPC_TIM0->MR0 = TimerInterval0;
		if( TimerInterval1 != 0)
			LPC_TIM0->MR1 = TimerInterval1;
		if( TimerInterval2 != 0)
			LPC_TIM0->MR2 = TimerInterval2;
		if( TimerInterval3 != 0)
			LPC_TIM0->MR3 = TimerInterval3;
		
	//*** <<< Use Configuration Wizard in Context Menu >>> ***
	// <h> timer0 MCR
	//   <e.0> MR0I
	//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.1> MR0R
	//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.2> MR0S
	//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.3> MR1I
	//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.4> MR1R
	//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.5> MR1S
	//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.6> MR2I
	//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.7> MR2R
	//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.8> MR2S
	//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.9> MR3I
	//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.10> MR3R
	//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.11> MR3S
	//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
		LPC_TIM0->MCR = 585;	/* MR01, MR1I, MR2I, MR3I */
	// </h>

		LPC_TIM0->PR = PrescaleValue;
		
		NVIC_SetPriority(TIMER0_IRQn, 4);		/* less priority than buttons */
		//NVIC_SetPriority(TIMER0_IRQn, 0);		/* more priority than buttons */
		NVIC_EnableIRQ(TIMER0_IRQn);

		return (1);
  }
  else if ( timer_num == 1 )
  {
		if( TimerInterval0 != 0)
			LPC_TIM1->MR0 = TimerInterval0;
		if( TimerInterval1 != 0)
			LPC_TIM1->MR1 = TimerInterval1;
		if( TimerInterval2 != 0)
			LPC_TIM1->MR2 = TimerInterval2;
		if( TimerInterval3 != 0)
			LPC_TIM1->MR3 = TimerInterval3;
		
	// <h> timer1 MCR
	//   <e.0> MR0I
	//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.1> MR0R
	//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.2> MR0S
	//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.3> MR1I
	//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.4> MR1R
	//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.5> MR1S
	//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.6> MR2I
	//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.7> MR2R
	//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.8> MR2S
	//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.9> MR3I
	//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.10> MR3R
	//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.11> MR3S
	//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
		LPC_TIM1->MCR = 585;	/* MR0I, MR1I */
	// </h>

		LPC_TIM1->PR = PrescaleValue;

		NVIC_SetPriority(TIMER1_IRQn, 4);		/* less priority than buttons */
		//NVIC_SetPriority(TIMER1_IRQn, 0);		/* more priority than buttons */
		NVIC_EnableIRQ(TIMER1_IRQn);

		return (1);
  }
	else if ( timer_num == 2 )
  {
		LPC_SC->PCONP     |=  (1<<22);	/* PCONP -> PCTIM2 = 1 */
		
		if( TimerInterval0 != 0)
			LPC_TIM2->MR0 = TimerInterval0;
		if( TimerInterval1 != 0)
			LPC_TIM2->MR1 = TimerInterval1;
		if( TimerInterval2 != 0)
			LPC_TIM2->MR2 = TimerInterval2;
		if( TimerInterval3 != 0)
			LPC_TIM2->MR3 = TimerInterval3;
		
	// <h> timer2 MCR
	//   <e.0> MR0I
	//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.1> MR0R
	//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.2> MR0S
	//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.3> MR1I
	//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.4> MR1R
	//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.5> MR1S
	//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.6> MR2I
	//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.7> MR2R
	//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.8> MR2S
	//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.9> MR3I
	//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.10> MR3R
	//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.11> MR3S
	//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
		LPC_TIM2->MCR = 0;	/* MR0I, MR1I, MR2I */
	// </h>

		LPC_TIM2->PR = PrescaleValue;
		
		NVIC_SetPriority(TIMER2_IRQn, 4);		/* less priority than buttons */
		//NVIC_SetPriority(TIMER2_IRQn, 0);		/* more priority than buttons */
		NVIC_EnableIRQ(TIMER2_IRQn);

		return (1);
  }
	else if ( timer_num == 3 )
  {
		LPC_SC->PCONP     |=  (1<<23);	/* PCONP -> PCTIM3 = 1 */
		
		if( TimerInterval0 != 0)
			LPC_TIM3->MR0 = TimerInterval0;
		if( TimerInterval1 != 0)
			LPC_TIM3->MR1 = TimerInterval1;
		if( TimerInterval2 != 0)
			LPC_TIM3->MR2 = TimerInterval2;
		if( TimerInterval3 != 0)
			LPC_TIM3->MR3 = TimerInterval3;
		
	// <h> timer3 MCR
	//   <e.0> MR0I
	//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.1> MR0R
	//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.2> MR0S
	//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.3> MR1I
	//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.4> MR1R
	//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.5> MR1S
	//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.6> MR2I
	//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.7> MR2R
	//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.8> MR2S
	//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.9> MR3I
	//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
	//	 <i> 0 This interrupt is disabled
	//   </e>
	//   <e.10> MR3R
	//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
	//	 <i> 0 Feature disabled.
	//   </e>
	//   <e.11> MR3S
	//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
	//	 <i> 0 Feature disabled.
	//   </e>
		LPC_TIM3->MCR = 0;
	// </h>

		LPC_TIM3->PR = PrescaleValue;
		
		//NVIC_SetPriority(TIMER3_IRQn, 4);		/* less priority than buttons */
		NVIC_SetPriority(TIMER3_IRQn, 0);		/* more priority than buttons */
		NVIC_EnableIRQ(TIMER3_IRQn);

		return (1);
  }
  return (0);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
