/* File: main.c
 * Date: 07.08.2026
 * Board: STM32G030J6
 * Purpose: LED stripe control.
 */
#include "stm32g0xx.h"

#define SYS_CLK (16000000U)
#define TIM1_PSC (16U)
// frequency for LED stripe control count
#define HIGH_FOR_LOGIC1 (0.8f * 0.000001f) //us
#define LOW_FOR_LOGIC1  (0.45f * 0.000001f) //us
#define PWM_PERIOD      (HIGH_FOR_LOGIC1 + LOW_FOR_LOGIC1)
#define PWM_FREQ        (1 / PWM_PERIOD)
#define PWM_DUTY_CYCLE  (HIGH_FOR_LOGIC1 / PWM_PERIOD)

/* Start PWM on PA8.
 * Frequency: PWM_FREQ.
 * Duty cycle: PWM_DUTY_CYCLE.
 */
void TIM1_setup() {
    RCC->IOPENR   |= RCC_IOPENR_GPIOAEN;
    // PA8 MODE: AF (10)
    GPIOA->MODER &= ~GPIO_MODER_MODE8_Msk;
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODE8_Pos); 
    // AF2 (TIM1_CH1)
    // AFR high
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL8);
    GPIOA->AFR[1] |= (2 << GPIO_AFRH_AFSEL8_Pos);
    // timer setup
    RCC->APBENR2  |= RCC_APBENR2_TIM1EN;
    TIM1->PSC = TIM1_PSC - 1;
    uint32_t tim1_arr = SYS_CLK / TIM1_PSC / PWM_FREQ - 1;
    TIM1->ARR = tim1_arr;
    // high level time
    TIM1->CCR1 = (tim1_arr + 1) * PWM_DUTY_CYCLE;
    // PWM mode 1: 0b110
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_Msk;
    TIM1->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos);
    // CCR1 preload
    TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
    // capture-compare enable
    TIM1->CCER |= TIM_CCER_CC1E;
    // main output enable
    TIM1->BDTR |= TIM_BDTR_MOE;
    // timer enable
    TIM1->CR1  |= TIM_CR1_CEN;
}

int main() {
    TIM1_setup();
    while (1) {
    }
}
