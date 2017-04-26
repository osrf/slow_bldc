#include <stdio.h>
#include "stack.h"
#include "startup.h"

void unhandled_vector(void)
{
  //printf("\noh noes! tried to execute unhandled vector %d (0x%x)\n",
  while (1) { }
  //arm_trap_unhandled_vector();
}

// declare weak symbols for all interrupt so they can be overridden easily
#define WEAK_VECTOR __attribute__((weak, alias("unhandled_vector")))
void nmi_vector(void) WEAK_VECTOR;
void hard_fault_vector(void) WEAK_VECTOR;
void mem_manage_vector(void) WEAK_VECTOR;
void bus_fault_vector(void) WEAK_VECTOR;
void usage_fault_vector(void) WEAK_VECTOR;
void svcall_vector(void) WEAK_VECTOR;
void pendsv_vector(void) WEAK_VECTOR;
void systick_vector(void) WEAK_VECTOR;

void wwdg_vector(void) WEAK_VECTOR;
void pvd_vector(void) WEAK_VECTOR;
void tamper_stamp_vector(void) WEAK_VECTOR;
void rtc_wkup_vector(void) WEAK_VECTOR;
void flash_vector(void) WEAK_VECTOR;
void rcc_vector(void) WEAK_VECTOR;
void exti0_vector(void) WEAK_VECTOR;
void exti1_vector(void) WEAK_VECTOR;
void exti2_ts_vector(void) WEAK_VECTOR;
void exti3_vector(void) WEAK_VECTOR;
void exti4_vector(void) WEAK_VECTOR;
void dma1_ch1_vector(void) WEAK_VECTOR;
void dma1_ch2_vector(void) WEAK_VECTOR;
void dma1_ch3_vector(void) WEAK_VECTOR;
void dma1_ch4_vector(void) WEAK_VECTOR;
void dma1_ch5_vector(void) WEAK_VECTOR;
void dma1_ch6_vector(void) WEAK_VECTOR;
void dma1_ch7_vector(void) WEAK_VECTOR;
void adc1_2_vector(void) WEAK_VECTOR;
void usb_hp_can_tx_vector(void) WEAK_VECTOR;
void usb_lp_can_rx0_vector(void) WEAK_VECTOR;
void can_rx1_vector(void) WEAK_VECTOR;
void can_sce_vector(void) WEAK_VECTOR;
void exti9_5_vector(void) WEAK_VECTOR;
void tim1_brk_tim15_vector(void) WEAK_VECTOR;
void tim1_up_tim16_vector(void) WEAK_VECTOR;
void tim1_trg_com_tim17_vector(void) WEAK_VECTOR;
void tim1_cc_vector(void) WEAK_VECTOR;
void tim2_vector(void) WEAK_VECTOR;
void tim3_vector(void) WEAK_VECTOR;
void tim4_vector(void) WEAK_VECTOR;
void i2c1_ev_vector(void) WEAK_VECTOR;
void i2c1_er_vector(void) WEAK_VECTOR;
void i2c2_ev_vector(void) WEAK_VECTOR;
void i2c2_er_vector(void) WEAK_VECTOR;
void spi1_vector(void) WEAK_VECTOR;
void spi2_vector(void) WEAK_VECTOR;
void usart1_vector(void) WEAK_VECTOR;
void usart2_vector(void) WEAK_VECTOR;
void usart3_vector(void) WEAK_VECTOR;
void exti15_10_vector(void) WEAK_VECTOR;
void rtc_alarm_vector(void) WEAK_VECTOR;
void usb_wakeup_vector(void) WEAK_VECTOR;
void tim8_brk_vector(void) WEAK_VECTOR;
void tim8_up_vector(void) WEAK_VECTOR;
void tim8_trg_com_vector(void) WEAK_VECTOR;
void tim8_cc_vector(void) WEAK_VECTOR;
void adc3_vector(void) WEAK_VECTOR;
void fmc_vector(void) WEAK_VECTOR;
void spi3_vector(void) WEAK_VECTOR;
void uart4_vector(void) WEAK_VECTOR;
void uart5_vector(void) WEAK_VECTOR;
void tim6_dac_vector(void) WEAK_VECTOR;
void tim7_vector(void) WEAK_VECTOR;
void dma2_ch1_vector(void) WEAK_VECTOR;
void dma2_ch2_vector(void) WEAK_VECTOR;
void dma2_ch3_vector(void) WEAK_VECTOR;
void dma2_ch4_vector(void) WEAK_VECTOR;
void dma2_ch5_vector(void) WEAK_VECTOR;
void adc4_vector(void) WEAK_VECTOR;
void comp1_2_3_vector(void) WEAK_VECTOR;
void comp4_5_6_vector(void) WEAK_VECTOR;
void comp7_vector(void) WEAK_VECTOR;
void i2c3_ev_vector(void) WEAK_VECTOR;
void i2c3_er_vector(void) WEAK_VECTOR;
void usb_hp_rmp_vector(void) WEAK_VECTOR;
void usb_lp_rmp_vector(void) WEAK_VECTOR;
void usb_wakeup_rmp_vector(void) WEAK_VECTOR;
void tim20_brk_vector(void) WEAK_VECTOR;
void tim20_up_vector(void) WEAK_VECTOR;
void tim20_trg_com_vector(void) WEAK_VECTOR;
void tim20_cc_vector(void) WEAK_VECTOR;
void fpu_vector(void) WEAK_VECTOR;
void spi4_vector(void) WEAK_VECTOR;

void dummy_reset_vector(void) { }

typedef void (*vector_func_t)(void);
__attribute__((section(".vectors"))) vector_func_t g_vectors[] =
{
    (vector_func_t)(&g_stack[STACK_SIZE-8]), // initial stack pointer
    reset_vector,
    nmi_vector,
    hard_fault_vector,
    mem_manage_vector,
    bus_fault_vector,
    usage_fault_vector,
    0,  // 0x1c
    0, 0, 0,  // 0x20, 0x24, 0x28
    svcall_vector,
    0, 0,  // 0x30, 0x34
    pendsv_vector,  // 0x38
    systick_vector,  // 0x3c
    wwdg_vector,       // 0
    pvd_vector,  // 1
    tamper_stamp_vector,  // 2
    rtc_wkup_vector,  // 3
    flash_vector,  // 4
    rcc_vector,  // 5
    exti0_vector,  // 6
    exti1_vector,  // 7
    exti2_ts_vector, // 8
    exti3_vector,  // 9
    exti4_vector,  // 10
    dma1_ch1_vector,  // 11
    dma1_ch2_vector,  // 12
    dma1_ch3_vector,  // 13
    dma1_ch4_vector,  // 14
    dma1_ch5_vector,  // 15
    dma1_ch6_vector,  // 16
    dma1_ch7_vector,  // 17
    adc1_2_vector,  // 18
    usb_hp_can_tx_vector,  // 19
    usb_lp_can_rx0_vector,  // 20
    can_rx1_vector,  // 21
    can_sce_vector,  // 22
    exti9_5_vector,  // 23
    tim1_brk_tim15_vector,  // 24
    tim1_up_tim16_vector,  // 25
    tim1_trg_com_tim17_vector,  // 26
    tim1_cc_vector,  // 27
    tim2_vector,  // 28
    tim3_vector,  // 29
    tim4_vector,  // 30
    i2c1_ev_vector,  // 31
    i2c1_er_vector,  // 32
    i2c2_ev_vector,  // 33
    i2c2_er_vector,  // 34
    spi1_vector,  // 35
    spi2_vector,  // 36
    usart1_vector,  // 37
    usart2_vector,  // 38
    usart3_vector,  // 39
    exti15_10_vector,  // 40
    rtc_alarm_vector,  // 41
    usb_wakeup_vector,  // 42
    tim8_brk_vector,  // 43
    tim8_up_vector,  // 44
    tim8_trg_com_vector,  // 45
    tim8_cc_vector,  // 46
    adc3_vector,  // 47
    fmc_vector,  // 48
    0, 0,  // 49 and 50 = reserved
    spi3_vector,  // 51
    uart4_vector,  // 52
    uart5_vector,  // 53
    tim6_dac_vector,  // 54
    tim7_vector,  // 55
    dma2_ch1_vector,  // 56
    dma2_ch2_vector,  // 57
    dma2_ch3_vector,  // 58
    dma2_ch4_vector,  // 59
    dma2_ch5_vector,  // 60
    adc4_vector,  // 61
    0, 0,  // 62 and 63 = reserved
    comp1_2_3_vector,  // 64
    comp4_5_6_vector,  // 65
    comp7_vector,  // 66
    0, 0, 0, 0, 0,  // 67, 68, 69, 70, 71 = reserved
    i2c3_ev_vector,  // 72
    i2c3_er_vector,  // 73
    usb_hp_rmp_vector,  // 74 (remappable from lower interrupt)
    usb_lp_rmp_vector,  // 75 (remappable from lower interrupt)
    usb_wakeup_rmp_vector,  // 76 (remappable from lower interrupt)
    tim20_brk_vector,  // 77
    tim20_up_vector,  // 78
    tim20_trg_com_vector,  // 79
    tim20_cc_vector,  // 80
    fpu_vector,  // 81
    0, 0,  // 82, 83 = reserved
    spi4_vector  // 84
};

