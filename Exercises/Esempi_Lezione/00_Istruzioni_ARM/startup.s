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

				;Per riservare porzione di memoria Read-Write
				AREA	MyDATA, DATA, READWRITE
vector_3		space 10	;Risultato
flags			space 10

                AREA    |.text|, CODE, READONLY
				;N.B. Se riserviamo memoria qua siamo in memoria di codice: Read-Only
vector_1		DCB 1,2,3,4,5,6,7,8,9,10
vector_2		DCB 1,2,3,4,5,6,7,8,9,10


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
                ;LDR     R0, =Reset_Handler
				
				; your code here
				;;;Esempio Istruzioni condizionali
				SUBS	R4,R4,R3
				MOVEQ	R0,R1
				MOVNE	R0,R2
				
				;;;Esempio 2 Istruzioni condizionali
				MOV R0, #01
				MOV R1, #02
				CMP R0, R1
				;ITEET GE	;IF (R0 > R1) THEN SUBGE ELSE SUBLT ELSE SUBLT -> INSERITO AUTOMATICAMENTE DAL COMPILATORE
				SUBGE R1, R0, R1
				SUBLT R2, R0, R1
				SUBLT R3, R1, R0
				SUBGE R1, R0, R1
				SUBLT R1, R0, R1	;IT LT SUBLT
				SUBLE R1, R1, R0	;IT LE SUBLE
				
				;;;Esempio formati MOV
				MOV R1, #0x0000001B	;F04F 011B
				MOV R1, #0x001B001B ;F04F 111B
				MOV R1, #0x1B001B00 ;F04F 211B
				MOV R1, #0x1B1B1B1B ;F04F 311B
				;MOV R1, #0x1000001B Non ammesso
				
				;;;Esercizio vettori 8bit v1 e v2 input, v3 risultato, v4 flags (non si possono chiamare v1 perchè usato come alias dei registri a1-a4=r0-r3 v1-v8=r4-r14)
				MOV R8, #10	;R8 Contatore elementi 10-0
				
				;Accedere ai dati nei vettori
				LDR R9, =vector_1	;Load address inside
				LDR R10, =vector_2
				LDR R11, =vector_3
				LDR R12, =flags
				
				;(Salvare numero grosso in registro)
				LDR R3, =0x08	; -> MOV R3, #0x08
				LDR R3, =0xC90137D2	; -> LDR R3, [PC, #96] (Impossibile con una MOV!)
				
				;Fare somma e elaborazione
ciclo			LDRB R0, [R9], #1	;Carico 8 bit dall'indirizzo contenuto in r9 in r0
				LDRB R1, [R10], #1
				
				
				;Somma di 2 numeri a 8 bit contenuti in R0 e R1, identificare Carry, Overflow, Negative
				;Carry -> R4[0] = 1
				;Overflow -> R4[1] = 1
				;Negative -> R4[2] = 1
				MOV R4, #0
				ADD R2, R1, R0
			    	
				;if (R2[8] = 1) Carry = 1
				TST  R2, #0x0100 ; Se c'è il carry (R2 AND 2_1000000 (0x0100) == ...1..) Ottavo bit a 1 -> Z=0
				ORRNE R4, R4, #1	;if (Z==0) R4=R4 OR 1 (001)
				
				;if ( (R1[7]==R0[7]) == R2[7]!=R0[7](o R1[7]) ) Overflow = 1
				AND R5, R0, #0x0080	;R5=R0[7]=1/0
				AND R6, R1, #0x0080 ;R6=R1[7]=1/0
				TEQ R5, R6	;XOR R5,R6 -> se Z=1:R5==R6 -> Potrei avere overflow
				BNE fine	;Se Z=0 Non posso avere overflow
				
				AND R7, R2, #0x0080 ;R7=R2[7]=1/0
				TEQ R7, R6	;XOR R5,R6 -> se Z=1:R7==R6 -> R2[7]==R0[7]==R1[7] -> No overflow
				ORRNE R4, R4, #2	;if (R2[7]!=R0[7])
				
				;N.B. E' necessario inserire il salto perchè la ORR prenderà sempre i valori attuali dei flag, indipendentemente dal fatto
				;che siano stati aggiornati dalla TEQ2 o dalla TEQ1, non ho modo di fare 2 if innestati perchè posso specificare un'unica condizione
				
				;if (R2[7] =1) Negative = 1
				TST R2, #0x0080 ; Se il numero è negativo (R2 AND 2_1000000 (0x0100) == ...1..) Settimo bit a 1 -> Z=0
				ORRNE R4, R4, #4	;if (Z==0) R4=R4 OR 4 (100)
                
				;Version 2
;				AND R5, R0, #0x0080	;R5=R0[7]=1/0
;				AND R6, R1, #0x0080 ;R6=R1[7]=1/0
;				AND R7, R2, #0x0080 ;R7=R2[7]=1/0
;				SUBS R8, R5, R6
;				SUBEQ R4, R5, R7
;				SUBNE R4, R7, R7
;				MOV R4, R4, LSR#7
;				AND R4, R4, #0x01

				;Salvare risultati
				STRB R2, [R11], #1	;Salvo 1 Byte dall'indirizzo contenuto in R11 nel risultato R2 e incrementa di 1B il contenuto di R11 (puntatore punta al successivo)
				STRB R4, [R12], #1	;Flags
				SUBS R8, R8, #1	;Diminuisco contatore
				BNE ciclo	;if R8!=0 ciclo
				
fine			B       .
                ;BX      R0
                ENDP

				LTORG	;Inizio literal pool

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
