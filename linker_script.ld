ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 10K
FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 32K
}

_start_of_stack = ORIGIN(RAM) + LENGTH(RAM);
_min_heap_size = 0x200;      /* required amount of heap  */
_min_stack_size = 0x400; /* required amount of stack */

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ORIGIN(FLASH);
    LONG(_start_of_stack);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ctor :
  {
    . = ALIGN(4);
    _sctor = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    . = ALIGN(4);
    _ector = .;
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH

  
  /* Uninitialized data section */
  .bss :
  {
    . = ALIGN(4);
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  .ram_usage_check :
  {
    . = ALIGN(8);
    . = . + _min_stack_size;
    . = . + _min_heap_size;
    . = ALIGN(8);
  } >RAM

}


PROVIDE(SVCall_Handler = Default_Handler);
PROVIDE(Debug_Monitor_Handler = Default_Handler);;
PROVIDE(PendSV_Handler = Default_Handler);;
PROVIDE(SysTick_Handler = Default_Handler);;
PROVIDE(WWDG_Handler = Default_Handler);;
PROVIDE(PVD_Handler = Default_Handler);;
PROVIDE(Tamper_Handler = Default_Handler);;
PROVIDE(RTC_Handler = Default_Handler);;
PROVIDE(Flash_Handler = Default_Handler);;
PROVIDE(RCC_Handler = Default_Handler);;
PROVIDE(EXTI0_Handler = Default_Handler);;
PROVIDE(EXTI1_Handler = Default_Handler);;
PROVIDE(EXTI2_Handler = Default_Handler);;
PROVIDE(EXTI3_Handler = Default_Handler);;
PROVIDE(EXTI4_Handler = Default_Handler);;
PROVIDE(DMA1_Channel1_Handler = Default_Handler);;
PROVIDE(DMA1_Channel2_Handler = Default_Handler);;
PROVIDE(DMA1_Channel3_Handler = Default_Handler);;
PROVIDE(DMA1_Channel4_Handler = Default_Handler);;
PROVIDE(DMA1_Channel5_Handler = Default_Handler);;
PROVIDE(DMA1_Channel6_Handler = Default_Handler);;
PROVIDE(DMA1_Channel7_Handler = Default_Handler);;
PROVIDE(ADC1_2_Handler = Default_Handler);;
PROVIDE(USB_HP_CAN_TX_Handler = Default_Handler);;
PROVIDE(USB_LP_CAN_RX0_Handler = Default_Handler);;
PROVIDE(CAN_RX1_Handler = Default_Handler);;
PROVIDE(CAN_SCE_Handler = Default_Handler);;
PROVIDE(EXTI9_5_Handler = Default_Handler);;
PROVIDE(TIM1_BRK_Handler = Default_Handler);;
PROVIDE(TIM1_BRK_UP_Handler = Default_Handler);;
PROVIDE(TIM1_TRG_COM_Handler = Default_Handler);;
PROVIDE(TIM1_CC_Handler = Default_Handler);;
PROVIDE(TIM2_Handler = Default_Handler);;
PROVIDE(TIM3_Handler = Default_Handler);;
PROVIDE(TIM4_Handler = Default_Handler);;
PROVIDE(I2C1_EV_Handler = Default_Handler);;
PROVIDE(I2C1_ER_Handler = Default_Handler);;
PROVIDE(I2C2_EV_Handler = Default_Handler);;
PROVIDE(I2C2_ER_Handler = Default_Handler);;
PROVIDE(SPI1_Handler = Default_Handler);;
PROVIDE(SPI2_Handler = Default_Handler);;
PROVIDE(USART1_Handler = Default_Handler);;
PROVIDE(USART2_Handler = Default_Handler);;
PROVIDE(USART3_Handler = Default_Handler);;
PROVIDE(EXTI15_10_Handler = Default_Handler);;
PROVIDE(RTCAlarm_Handler = Default_Handler);;
PROVIDE(USBWakeup_Handler = Default_Handler);;
PROVIDE(TIM8_BRK_Handler = Default_Handler);;
PROVIDE(TIM8_UP_Handler = Default_Handler);;
PROVIDE(TIM8_TRG_COM_Handler = Default_Handler);;
PROVIDE(TIM8_CC_Handler = Default_Handler);;
PROVIDE(ADC3_Handler = Default_Handler);;
PROVIDE(FSMC_Handler = Default_Handler);;
PROVIDE(SDIO_Handler = Default_Handler);;
PROVIDE(TIM5_Handler = Default_Handler);;
PROVIDE(SPI3_Handler = Default_Handler);;
PROVIDE(UART4_Handler = Default_Handler);;
PROVIDE(UART5_Handler = Default_Handler);;
PROVIDE(TIM6_Handler = Default_Handler);;
PROVIDE(TIM7_Handler = Default_Handler);;
PROVIDE(DMA2_Channel1_Handler = Default_Handler);;
PROVIDE(DMA2_Channel2_Handler = Default_Handler);;
PROVIDE(DMA2_Channel3_Handler = Default_Handler);;
PROVIDE(DMA2_Channel4_5_Handler = Default_Handler);;