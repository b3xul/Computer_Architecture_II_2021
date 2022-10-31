;            Computer Architectures - 02LSEOV 02LSEOQ            ;
; author: 		Paolo BERNARDI - Politecnico di Torino           ;
; creation: 	11 November 2018								 ;
; last update:  13 November 2018								 ;
; functionalities:												 ;
;		nothing but bringing to the reset handler				 ;

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
				SPACE   Stack_Size/2
Stack_Mem       SPACE   Stack_Size/2
__initial_sp




; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

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
					
					
				AREA 	DATI, DATA, READONLY
StartAddressA	DCW		0xDEAD
StartAddressB	DCW		0xCAFE

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
				
				; your code here
				
				MOV		R0, #3
				MSR		CONTROL, R0
				LDR		SP, =Stack_Mem
				
				nop
				
				MOV R0, #0xdead
				MOV R1, #0xcafe
				MOV R2, #0xabba
				MOV R3, #0xdead
				MOV R4, #0xcafe
				MOV R5, #0xbaba
				MOV R6, #0xcafe
				MOV R7, #0xcafe
				
				;MOV R0, #0x00000300
				;MOV R1, #0x00000302
				LDR R0, =StartAddressA
				LDR R1, =StartAddressB
				
				SVC		0x64
				
InfLoop         B      	InfLoop
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
				
				; STMFD SP!, {R0-R12, LR}
				; A questo punto, essendo nell'handler della SVC sono passato in thread mode con priviliegi e MSP. Lo stack frame generato
				; all'invocazione della SVC però è stato salvato nello stack che era in utilizzo in quel momento. Per capire quale era faccio
				; un test ( = AND) bit a bit tra l'LR, che ora conterrà 0xFFFFFFF1, 0xFFFFFFF9 o 0xFFFFFFFD, in modo da capire quale stack usare
				TST LR, #1
				MRSEQ R11, MSP
				MRSNE R11, PSP
				LDR R10, [R11, #24] ; R1 + 24 = PC
				LDR R10, [R10,#-4] ; PC - 4 = opcode della SVC
				BIC R10, #0xFF000000
				LSR R10, #16
				
				; a questo punto R10 contiene nei sui 8 LSB valori tra 0x00 e 0xFF. Di fatto i controlli sui bit 6 e 7 sono eseguiti implicitamente
				; in quanto, se non viene eseguito nessun salto END_HANDLER, il valore contenuto è compreso tra 64 e 128. Ciò significa che se il
				; arriva alla linea 219 dobbiamo per forza implementare la MEMCMP
				
				MOV R8, #0x0
				CMP R10, #0
				STREQ R8, [R11]
				BEQ END_HANDLER
				CMP R10, #1
				STREQ R8, [R11, #4]
				BEQ END_HANDLER
				CMP R10, #2
				STREQ R8, [R11, #8]
				BEQ END_HANDLER
				CMP R10, #3
				STREQ R8, [R11, #12]
				BEQ END_HANDLER
				CMP R10, #4
				MOVEQ R4, R8
				BEQ END_HANDLER
				CMP R10, #5
				MOVEQ R5, R8
				BEQ END_HANDLER
				CMP R10, #6
				MOVEQ R6, R8
				BEQ END_HANDLER
				CMP R10, #7
				MOVEQ R7, R8
				BEQ END_HANDLER
				
				; si poteva usare una STM per i registri r0-r3, decidendo magari di resettare più registri alla volta. Così invece si resetta
				; solamente il registro desiderato
				
				CMP R10, #15 ; arrivati qua R0 è sicuramente >= 8
				NOPLO
				BLO END_HANDLER
				
				CMP R10, #128
				NOPHS
				BHS END_HANDLER
				
				; arrivati a questo punto dobbiamo necessariamente implementare la MEMCMP. Si utilizza una maschera per resettare i bit che non
				; vanno confrontati
				
				BIC R10, #0xFFFFFFC0 ; reset di tutti i bit tranne gli ultimi 6 in R10. A questo punto uso R10 come contatore e confronto byte per
									 ; byte i valori puntati da R0 ed R1. Per fare un confronto byte per byte uso due registri di appoggio per 
									 ; caricare i valori, poi carico in R0 ed R1, facendo iterativamente uno shift verso destra e rimuovendo i 24 MSB
									 ; con una maschera
									 
				; prima iterazione del loop gestita a parte, poiché non deve essere eseguito lo shift logico a destra di 4 posizioni
				LDR R2, [R0]
				LDR R3, [R1]
				MOV R4, R2
				MOV R5, R3
				BIC R4, #0xFFFFFFF0
				BIC R5, #0xFFFFFFF0
				CMP R4, R5
				BHI HIGH
				BLO LOW
				ADD R10, #-1
				
LOOP			MOV R4, R2
				MOV R5, R3
				LSR R4, #4
				LSR R5, #5
				BIC R4, #0xFFFFFFF0
				BIC R5, #0xFFFFFFF0
				CMP R4, R5
				BHI HIGH
				BLO LOW
				ADD R10, #-1
				CMP R10, #0
				BNE LOOP
				
				MOV R0, #0
				STR R0, [R11]
				B END_HANDLER
				
HIGH			MOV R0, #1
				STR R0, [R11]
				B   END_HANDLER
				
LOW				MOV R0, #-1
				STR R0, [R11]
				B	END_HANDLER
				
				; LDMFD SP!, {R0-R12, PC}
END_HANDLER		BX LR
				
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
