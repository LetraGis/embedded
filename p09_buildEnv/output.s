
output.elf:     file format elf32-littlearm


Disassembly of section .text:

08000000 <vectors>:
 8000000:	80 04 00 20 ed 01 00 08 71 02 00 08 71 02 00 08     ... ....q...q...
 8000010:	71 02 00 08 71 02 00 08 71 02 00 08 00 00 00 00     q...q...q.......
	...
 800002c:	71 02 00 08 71 02 00 08 00 00 00 00 71 02 00 08     q...q.......q...
 800003c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800004c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800005c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800006c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800007c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800008c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800009c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80000ac:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80000bc:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80000cc:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80000dc:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80000ec:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80000fc:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800010c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800011c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800012c:	71 02 00 08 71 02 00 08 00 00 00 00 00 00 00 00     q...q...........
 800013c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800014c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800015c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 800016c:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
	...
 8000184:	71 02 00 08 00 00 00 00 00 00 00 00 71 02 00 08     q...........q...
	...
 800019c:	71 02 00 08 00 00 00 00 00 00 00 00 00 00 00 00     q...............
 80001ac:	71 02 00 08 71 02 00 08 71 02 00 08 71 02 00 08     q...q...q...q...
 80001bc:	71 02 00 08 71 02 00 08                             q...q...

080001c4 <main>:
const uint8_t constant_data = 200;
uint32_t uninitialized_data;
uint16_t initialized_data = 150;

int main(void)
{
 80001c4:	b580      	push	{r7, lr}
 80001c6:	b082      	sub	sp, #8
 80001c8:	af00      	add	r7, sp, #0
    Gpio_Init();
 80001ca:	f000 f855 	bl	8000278 <Gpio_Init>

    while (1)
    {
		/* Input pin is configured as active-low */
		gpioState inputButtonSt = Gpio_ReadPinState();
 80001ce:	f000 f893 	bl	80002f8 <Gpio_ReadPinState>
 80001d2:	4603      	mov	r3, r0
 80001d4:	71fb      	strb	r3, [r7, #7]

		if (GPIO_HIGH == inputButtonSt)
 80001d6:	79fb      	ldrb	r3, [r7, #7]
 80001d8:	2b01      	cmp	r3, #1
 80001da:	d103      	bne.n	80001e4 <main+0x20>
		{
			Gpio_SetPinState(GPIO_LOW);
 80001dc:	2000      	movs	r0, #0
 80001de:	f000 f86f 	bl	80002c0 <Gpio_SetPinState>
 80001e2:	e7f4      	b.n	80001ce <main+0xa>
		}
		else
		{
			Gpio_SetPinState(GPIO_HIGH);
 80001e4:	2001      	movs	r0, #1
 80001e6:	f000 f86b 	bl	80002c0 <Gpio_SetPinState>
    {
 80001ea:	e7f0      	b.n	80001ce <main+0xa>

080001ec <Reset_Handler>:
 *                  zeros.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Reset_Handler(void)
{
 80001ec:	b580      	push	{r7, lr}
 80001ee:	b086      	sub	sp, #24
 80001f0:	af00      	add	r7, sp, #0
    /* Calculate .data section size */
    uint32_t section_size = (uint32_t)&_edata - (uint32_t)&_sdata;
 80001f2:	4a1a      	ldr	r2, [pc, #104]	; (800025c <Reset_Handler+0x70>)
 80001f4:	4b1a      	ldr	r3, [pc, #104]	; (8000260 <Reset_Handler+0x74>)
 80001f6:	1ad3      	subs	r3, r2, r3
 80001f8:	607b      	str	r3, [r7, #4]
    
    /* Destination is SRAM memory */
    uint8_t *pDest = (uint8_t *)&_sdata;
 80001fa:	4b19      	ldr	r3, [pc, #100]	; (8000260 <Reset_Handler+0x74>)
 80001fc:	617b      	str	r3, [r7, #20]
    /* Source is Flash memory */
    uint8_t *pSrc = (uint8_t *)&_etext;
 80001fe:	4b19      	ldr	r3, [pc, #100]	; (8000264 <Reset_Handler+0x78>)
 8000200:	613b      	str	r3, [r7, #16]

    /* Copies content from Flash to RAM */
    for (uint32_t i = 0; i < section_size; i++)
 8000202:	2300      	movs	r3, #0
 8000204:	60fb      	str	r3, [r7, #12]
 8000206:	e00a      	b.n	800021e <Reset_Handler+0x32>
    {
        *pDest++ = *pSrc++; 
 8000208:	693a      	ldr	r2, [r7, #16]
 800020a:	1c53      	adds	r3, r2, #1
 800020c:	613b      	str	r3, [r7, #16]
 800020e:	697b      	ldr	r3, [r7, #20]
 8000210:	1c59      	adds	r1, r3, #1
 8000212:	6179      	str	r1, [r7, #20]
 8000214:	7812      	ldrb	r2, [r2, #0]
 8000216:	701a      	strb	r2, [r3, #0]
    for (uint32_t i = 0; i < section_size; i++)
 8000218:	68fb      	ldr	r3, [r7, #12]
 800021a:	3301      	adds	r3, #1
 800021c:	60fb      	str	r3, [r7, #12]
 800021e:	68fa      	ldr	r2, [r7, #12]
 8000220:	687b      	ldr	r3, [r7, #4]
 8000222:	429a      	cmp	r2, r3
 8000224:	d3f0      	bcc.n	8000208 <Reset_Handler+0x1c>
    }

    /* Calculate .bss section size */
    section_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
 8000226:	4a10      	ldr	r2, [pc, #64]	; (8000268 <Reset_Handler+0x7c>)
 8000228:	4b10      	ldr	r3, [pc, #64]	; (800026c <Reset_Handler+0x80>)
 800022a:	1ad3      	subs	r3, r2, r3
 800022c:	607b      	str	r3, [r7, #4]
    pDest = (uint8_t *)&_sbss;
 800022e:	4b0f      	ldr	r3, [pc, #60]	; (800026c <Reset_Handler+0x80>)
 8000230:	617b      	str	r3, [r7, #20]

    /* Initialize .bss section to 0's */
    for (uint32_t i = 0; i < section_size; i++)
 8000232:	2300      	movs	r3, #0
 8000234:	60bb      	str	r3, [r7, #8]
 8000236:	e007      	b.n	8000248 <Reset_Handler+0x5c>
    {
        *pDest++ = 0; 
 8000238:	697b      	ldr	r3, [r7, #20]
 800023a:	1c5a      	adds	r2, r3, #1
 800023c:	617a      	str	r2, [r7, #20]
 800023e:	2200      	movs	r2, #0
 8000240:	701a      	strb	r2, [r3, #0]
    for (uint32_t i = 0; i < section_size; i++)
 8000242:	68bb      	ldr	r3, [r7, #8]
 8000244:	3301      	adds	r3, #1
 8000246:	60bb      	str	r3, [r7, #8]
 8000248:	68ba      	ldr	r2, [r7, #8]
 800024a:	687b      	ldr	r3, [r7, #4]
 800024c:	429a      	cmp	r2, r3
 800024e:	d3f3      	bcc.n	8000238 <Reset_Handler+0x4c>
    }

    /* Branches to main() */
    main();
 8000250:	f7ff ffb8 	bl	80001c4 <main>
    
}
 8000254:	bf00      	nop
 8000256:	3718      	adds	r7, #24
 8000258:	46bd      	mov	sp, r7
 800025a:	bd80      	pop	{r7, pc}
 800025c:	20000004 	.word	0x20000004
 8000260:	20000000 	.word	0x20000000
 8000264:	0800031c 	.word	0x0800031c
 8000268:	20000008 	.word	0x20000008
 800026c:	20000004 	.word	0x20000004

08000270 <Default_Handler>:
 *                  the source is not available.
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Default_Handler(void)
{
 8000270:	b480      	push	{r7}
 8000272:	af00      	add	r7, sp, #0
    while(1);
 8000274:	e7fe      	b.n	8000274 <Default_Handler+0x4>
 8000276:	bf00      	nop

08000278 <Gpio_Init>:
 *                  of pins as output (pin 5, GPIOA) and input (pin 13, GPIOC).
 * @param[in]      	void    No input parameters.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Gpio_Init(void)
{
 8000278:	b480      	push	{r7}
 800027a:	af00      	add	r7, sp, #0
    RCC_AHB1ENR |= (GPIOC_EN_MSK | GPIOA_EN_MSK);
 800027c:	4b0d      	ldr	r3, [pc, #52]	; (80002b4 <Gpio_Init+0x3c>)
 800027e:	681b      	ldr	r3, [r3, #0]
 8000280:	4a0c      	ldr	r2, [pc, #48]	; (80002b4 <Gpio_Init+0x3c>)
 8000282:	f043 0305 	orr.w	r3, r3, #5
 8000286:	6013      	str	r3, [r2, #0]
    GPIOA_MODE  &= ~(GPIOA_5_CLR_MSK);
 8000288:	4b0b      	ldr	r3, [pc, #44]	; (80002b8 <Gpio_Init+0x40>)
 800028a:	681b      	ldr	r3, [r3, #0]
 800028c:	4a0a      	ldr	r2, [pc, #40]	; (80002b8 <Gpio_Init+0x40>)
 800028e:	f423 6340 	bic.w	r3, r3, #3072	; 0xc00
 8000292:	6013      	str	r3, [r2, #0]
    GPIOA_MODE  |= (GPIOA_5_OUT_MODE_MSK);
 8000294:	4b08      	ldr	r3, [pc, #32]	; (80002b8 <Gpio_Init+0x40>)
 8000296:	681b      	ldr	r3, [r3, #0]
 8000298:	4a07      	ldr	r2, [pc, #28]	; (80002b8 <Gpio_Init+0x40>)
 800029a:	f443 6380 	orr.w	r3, r3, #1024	; 0x400
 800029e:	6013      	str	r3, [r2, #0]
    GPIOC_MODE  &= ~(GPIOC_13_IN_MODE_MSK);
 80002a0:	4b06      	ldr	r3, [pc, #24]	; (80002bc <Gpio_Init+0x44>)
 80002a2:	681b      	ldr	r3, [r3, #0]
 80002a4:	4a05      	ldr	r2, [pc, #20]	; (80002bc <Gpio_Init+0x44>)
 80002a6:	f023 4388 	bic.w	r3, r3, #1140850688	; 0x44000000
 80002aa:	6013      	str	r3, [r2, #0]
}
 80002ac:	bf00      	nop
 80002ae:	46bd      	mov	sp, r7
 80002b0:	bc80      	pop	{r7}
 80002b2:	4770      	bx	lr
 80002b4:	40023830 	.word	0x40023830
 80002b8:	40020000 	.word	0x40020000
 80002bc:	40020800 	.word	0x40020800

080002c0 <Gpio_SetPinState>:
 *                  parameter.
 * @param[in]      	state   Holds the pin state.
 * @return         	void    No output parameters.
 ******************************************************************************/
void Gpio_SetPinState(gpioState state)
{
 80002c0:	b480      	push	{r7}
 80002c2:	b083      	sub	sp, #12
 80002c4:	af00      	add	r7, sp, #0
 80002c6:	4603      	mov	r3, r0
 80002c8:	71fb      	strb	r3, [r7, #7]
    if (GPIO_HIGH == state)
 80002ca:	79fb      	ldrb	r3, [r7, #7]
 80002cc:	2b01      	cmp	r3, #1
 80002ce:	d106      	bne.n	80002de <Gpio_SetPinState+0x1e>
    {
        GPIOA_ODR |= (uint32_t)GPIOA_5_OUT_ST_MSK;
 80002d0:	4b08      	ldr	r3, [pc, #32]	; (80002f4 <Gpio_SetPinState+0x34>)
 80002d2:	681b      	ldr	r3, [r3, #0]
 80002d4:	4a07      	ldr	r2, [pc, #28]	; (80002f4 <Gpio_SetPinState+0x34>)
 80002d6:	f043 0320 	orr.w	r3, r3, #32
 80002da:	6013      	str	r3, [r2, #0]
    }
    else
    {
        GPIOA_ODR &= (uint32_t)~GPIOA_5_OUT_ST_MSK;
    }
}
 80002dc:	e005      	b.n	80002ea <Gpio_SetPinState+0x2a>
        GPIOA_ODR &= (uint32_t)~GPIOA_5_OUT_ST_MSK;
 80002de:	4b05      	ldr	r3, [pc, #20]	; (80002f4 <Gpio_SetPinState+0x34>)
 80002e0:	681b      	ldr	r3, [r3, #0]
 80002e2:	4a04      	ldr	r2, [pc, #16]	; (80002f4 <Gpio_SetPinState+0x34>)
 80002e4:	f023 0320 	bic.w	r3, r3, #32
 80002e8:	6013      	str	r3, [r2, #0]
}
 80002ea:	bf00      	nop
 80002ec:	370c      	adds	r7, #12
 80002ee:	46bd      	mov	sp, r7
 80002f0:	bc80      	pop	{r7}
 80002f2:	4770      	bx	lr
 80002f4:	40020014 	.word	0x40020014

080002f8 <Gpio_ReadPinState>:
 * 					implementation needs to be designed by the developer.
 * @param[in]      	void    No input parameters.
 * @return         	retVal  Pin state (HIGH/LOW).
 ******************************************************************************/
gpioState Gpio_ReadPinState(void)
{
 80002f8:	b480      	push	{r7}
 80002fa:	af00      	add	r7, sp, #0
    return ((GPIOC_IDR >> 13) & 1);
 80002fc:	4b05      	ldr	r3, [pc, #20]	; (8000314 <Gpio_ReadPinState+0x1c>)
 80002fe:	681b      	ldr	r3, [r3, #0]
 8000300:	0b5b      	lsrs	r3, r3, #13
 8000302:	b2db      	uxtb	r3, r3
 8000304:	f003 0301 	and.w	r3, r3, #1
 8000308:	b2db      	uxtb	r3, r3
}
 800030a:	4618      	mov	r0, r3
 800030c:	46bd      	mov	sp, r7
 800030e:	bc80      	pop	{r7}
 8000310:	4770      	bx	lr
 8000312:	bf00      	nop
 8000314:	40020810 	.word	0x40020810

08000318 <constant_data>:
 8000318:	000000c8                                ....
