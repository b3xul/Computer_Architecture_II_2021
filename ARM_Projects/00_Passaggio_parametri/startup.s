;/**************************************************************************//**
; * @file     startup_LPC17xx.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           NXP LPC17xx Device Series
; * @version  V1.10
; * @date     06. April 2011
; *
; * @note
; * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF

				AREA	my_data, DATA, READWRITE	;Se compilatore si lamenta aggiungiamo align

Riferimenti		SPACE 8	;salvo contenuto di 2 registri da 32 bit
 
                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                                              
				;1. Passaggio parametri usando Registri
				LDR R0, =my_list
				LDR R2, =size
				LDR R1, [R2]	;R1=5
				;R1, R2 = Parametri
				BL minimo
				;R2=result
				MOV R5, R2	;R5=result
				
				;2. Passaggio parametri by Reference
				LDR R0, =my_list
				LDR R2, =size
				LDR R1, [R2]
				LDR R3, =Riferimenti
				STMIA R3, {R0, R1}	;Store multiple increment after (salva R0 in values e R1 in values+4B)
				;[R3]=parametri in ordine
				BL massimo
				;[R3]=result
				LDR R6, [R3]
				
				;3. Passaggio parametri on the stack
				LDR R0, =my_list
				LDR R2, =size
				LDR R1, [R2]
				PUSH {R0, R1, R2}
				;R0, R1 = Parametri, R2=result
				BL media
				POP {R0, R1, R2}
				;r2=result
				MOV R7, R2
				
				B	.
                ENDP

;-------------------------------------------------------

my_list			DCD 10, 2, 3, 4, 5
size			DCD 5
 
;-------------------------------------------------------

minimo			PROC
				;1. Passaggio parametri tramite registri
				;LR=PC+(2 o 4)+1 (Per salti all'indietro lsb=1)
				PUSH {R3, LR}	;N.B. Dato che sporco R3 ed esso non è un valore di ritorno devo salvare il valore precedente e riportarlo (non so se serve o meno al chiamante)
								;I registri contenuti nella push (pop) vengono automaticamente ordinati in ordine crescente (decrescente) dal compilatore  
				LDR R2, [R0]	;R2=[R0]=[my_list]=10
				
ciclomin		LDR R3, [R0, #4]!	;R3=[R0+4]=2 , R0+=4 (Al primo giro prende 10, poi incrementa)  
				CMP R2, R3
				MOVGE R2, R3	;IF R2>R3 R2=R3 (R3 nuovo minimo)
				SUB R1, R1, #1	;Decremento contatore R1 -> deve andare da 5 a 1 -> NON DA 5 a 0 perchè il primo elemento l'ho già considerato prima del loop!
				CMP R1, #1	;Quando R1=1 esco dal ciclo
				BNE ciclomin 
				;R2=minimo
				
				POP {R3, PC}	;= pop r3, mov pc, lr 
				ENDP

;-------------------------------------------------------

massimo			PROC
				
				PUSH {R2, R4, R5, R6, LR}
				LDMIA R3, {R5,R6}	;R5=R0=my_list, R6=R1=5 ([size])
				LDR R2, [R5]	;R2=[my_list]=10
				
ciclomax		LDR R4, [R5, #4]!	;R3=[R0+4]=2 , R0+=4 (Al primo giro prende 10, poi incrementa)  
				CMP R2, R4
				MOVLT R2, R4	;IF R2<=R3 R2=R3 (R3 nuovo massimo)
				SUB R6, R6, #1	;Decremento contatore R6 -> deve andare da 5 a 1 -> NON DA 5 a 0 perchè il primo elemento l'ho già considerato prima del loop!
				CMP R6, #1	;Quando R6=1 esco dal ciclo
				BNE ciclomax 
				
				;R2=massimo
				STR R2, [R3]	;[R3]=risultato]=massimo
				
				POP {R2, R4, R5, R6, PC}	;= pop r3, mov pc, lr 
				ENDP

;-------------------------------------------------------
				
media			PROC
				;		+8, +7, +6, +5, +4, +3, +2, +1, SP
				;STACK: R2, R1, R0, LR, R5, R4, R3, R2, R1
				PUSH {R1, R2, R3, R4, R5, LR}
				LDR R4, [SP, #4*6]	;R4=R0=my_list
				LDR R5, [SP, #4*7]	;R5=R1=size
				
				LDR R2, [R4]	;R2=[my_list]=10
				
ciclomedia		LDR R3, [R4, #4]!	;R3=[R4+4]=2 , R4+=4 (Al primo giro prende 10, poi incrementa)  
				ADD R2, R2, R3
				SUB R5, R5, #1	;Decremento contatore R6 -> deve andare da 5 a 1 -> NON DA 5 a 0 perchè il primo elemento l'ho già considerato prima del loop!
				CMP R5, #1	;Quando R6=1 esco dal ciclo
				BNE ciclomedia
				
				LDR R5, [SP, #4*7]	;R5=R1=size
				UDIV R2, R2, R5
				
				;R2=media
				STR R2, [SP, #4*8]	;R2=risultato=media
				
				POP {R1, R2, R3, R4, R5, PC}	;= pop r3, mov pc, lr 
				ENDP

;-------------------------------------------------------

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit                

                END