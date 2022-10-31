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

				SPACE   Stack_Size/2
Stack_Mem       ;PSP Initial addr

				SPACE   Stack_Size/2
__initial_sp	;MSP Initial addr  


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

				AREA	MyData, DATA, READONLY
				;Dati lunghi 63 in modo da poter usare ogni possibile valore di svc_number senza incorrere in problemi
Area1			DCB 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
Area2			DCB 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
Area3			DCB 1,2,4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
Area4			DCB 0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
                ;LDR     R0, =Reset_Handler
				
				;Thread Mode: CONTROL[1]=0 -> MSP. CONTROL[0]=0 -> Privileged Level
				
				MOV R0, #3	
				MSR CONTROL, R0	;Thread Mode: CONTROL[1]=1 -> PSP. CONTROL[0]=1 -> User Level
				LDR	SP, =Stack_Mem	;Inizializzo PSP
				
				;SVC -> HW Stacking:           +7 ,    +6 ,    +5 ,    +4 ,+3,+2,+1,PSP/MSP
				;					PUSH R15(xPSR),R14(PC),R13(LR),R12(IP),R3,R2,R1,R0

				;RESET
				MOV R0, #1
				MOV R1, #2
				MOV R2, #3
				MOV R3, #4
				MOV R4, #5
				MOV R5, #6
				MOV R6, #7
				MOV R7, #8
				
				SVC 0
				SVC 1
				SVC 2
				SVC 3
				SVC 4
				SVC 5
				SVC 6
				SVC 7
				
				;NOP
				SVC 8
				SVC 10
				SVC 15
				
				;UNDEFINED (NO ACTION)
				
				SVC 50
				
				SVC 128
				SVC 200
				SVC 255
				
				;MEMCMP
				LDR R0, =Area1
				LDR R1, =Area2
				SVC 64
				;Result in R0
				
				LDR R0, =Area1
				LDR R1, =Area2
				SVC 74
				
				LDR R0, =Area1
				LDR R1, =Area2
				SVC 127
				
				;-------------
				LDR R0, =Area1
				LDR R1, =Area3
				SVC 74
				
				;-------------
				LDR R0, =Area1
				LDR R1, =Area4
				SVC 74
				
                B		.
                ENDP

 
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
				
				;Handler Mode: CONTROL[1]=0 -> MSP. (Privileged Level)
                PUSH {R0-R12, LR}	;        +13 ,   +12 ,+11,+10,+9,+8,+7,+6,+5,+4,+3,+2,+1,MSP
									;PUSH R13(LR),R12(IP),R11,R10,R9,R8,R7,R6,R5,R4,R3,R2,R1,R0
				
				;Dato che servono comunque entrambi
				MRS R1, MSP
				MRS R2, PSP
				
				TST LR, #4		;TST= AND con 4=0100 -> Check dello stato del processore nel chiamante guardando ultimo B del LR=EXC_RETURN value
				MOVEQ R3, #14	;Caller is Privileged
				MOVNE R3, #0	;Caller is Unprivileged
				ALIAS R3, offset
				
				ADD R4, R3, #6
				ALIAS R4, target
				
				TST LR, #4
				LDREQ R0, [R1, target, LSL #2]	;R0=[MSP+((14+6)*4)]
				LDRNE R0, [R2, target, LSL #2]	;R0=[PSP+((0+6)*4)]
				;R0=Indirizzo di ritorno= ADDR(SVC)+4
				
				LDR R0, [R0,#-4]	;R0=SVC
				BIC R0, #0xFF000000
				LSR R0, #16	;R0=SVC Number
				
				;---------------------------------
				;NOP
				;---------------------------------
				TST R0, #128	;R0 AND 1--- ----
				NOPNE	;if(R0>=128) TST=1 -> NOP
				BNE return	;else R0<128
				
				;---------------------------------
				;MEMCMP
				;---------------------------------
				CMP R0, #64		;if(R0>=64 (AND R0<128)) TST=1 -> MEMCMP | R0 AND 01-- ---- (sono sicuro che l'ottavo bit è a zero altrimenti non sarei potuto arrivare qui)
				BLT next	;R0<64
				MOVEQ R11, #0	;se SVC Number=64 evito di eseguire il codice e ritorno direttamente che le due aree di memoria sono uguali dato che dovrei confrontare 0 bytes
				BEQ risultato
				
				SUB R5, R0, #64	;R5=Number of bytes to compare
				
				MOV target, offset	;Target=R0
				
				TST LR, #4
				LDREQ R6, [R1, target, LSL #2]	;R0=[MSP+((14)*4)]
				LDRNE R6, [R2, target, LSL #2]	;R0=[PSP+((0)*4)]
				;R6=Param1
				
				ADD target, target, #1	;Target=R1
				
				TST LR, #4
				LDREQ R7, [R1, target, LSL #2]	;R0=[MSP+((15)*4)]
				LDRNE R7, [R2, target, LSL #2]	;R0=[PSP+((1)*4)]
				;R7=Param2
				
				EOR R8, R8	;Indice da 0 a R5 
compare			LDRB R9, [R6, R8]
				LDRB R10, [R7, R8]
				CMP R9, R10
				MOVLT R11, #-1 
				MOVGT R11, #1
				BNE risultato
				ADD R8, R8, #1
				CMP R8, R5
				BNE compare
				;finito il ciclo senza uscire prima: sono uguali
				MOV R11, #0
				
				
risultato		MOV target, offset
				TST LR, #4
				STREQ R11, [R1, target, LSL #2]	;R0=[MSP+((14)*4)]
				STRNE R11, [R2, target, LSL #2]	;R0=[PSP+((0)*4)]
				B return
				
				;---------------------------------
				;NESSUNA SPECIFICA
				;---------------------------------
next			CMP R0, #16		;if(R0>=16 (AND R0<64)) -> Nessuna specifica data
				
				BCS return ;Unsigned >=	
				
				
				;---------------------------------
				;NOP
				;---------------------------------
				TST R0, #8		;if(R0>=8 (AND R0<15)) TST=1 -> NOP | R0 AND 0000 1---
				NOPNE
				BNE return
				
				;---------------------------------
				;RESET
				;---------------------------------
				;if(R0 \< 8) -> RESET
	
				EOR R5, R5	;Registro per fare reset
				
				TST R0, #4		;if(R0>=4) TST=1 -> R4-R7 -> In entrambi i casi si accede all'MSP
				STRNE R5, [R1, R0, LSL #2] 	;[R1 + R0*4] = 0 -> Resetta sullo stack l'indirizzo dove lo stacking aveva salvato il registro corrispondente
				BNE return
				
				;R0-R3
				ADD target, offset, R0
				TST LR, #4
				STREQ R5, [R1, target, LSL #2]	;R0=[MSP+((14+0,1,2,3)*4)]
				STRNE R5, [R2, target, LSL #2]	;R0=[PSP+((0+0,1,2,3)*4)]
				
				
return			POP {R0-R12, LR}
				BX LR
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
