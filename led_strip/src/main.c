/* File: main.c 
 * Date: 22.07.2026
 * Board: STM32G474
 * IDE: VSCode + platformio.
 * Purpose: WS2812 LED strip control (push-pull 3V3).
 * Protocol: 1 = (0.8us HIGH + 0.45us LOW); 0 = (0.4us HIGH + 0.85us LOW).
 * Press RESET to turn on.
 */
#include <inttypes.h>
#include "stm32g4xx.h"

// TIM16 bus, 16MHz
#define APB2_FREQ       (16000000U)
#define HIGH_FOR_LOGIC1 (0.8f * 0.000001f) //us
#define LOW_FOR_LOGIC1  (0.45f * 0.000001f) //us
#define PWM_PERIOD      (HIGH_FOR_LOGIC1 + LOW_FOR_LOGIC1)
#define PWM_FREQ        (1 / PWM_PERIOD)
#define PWM_duty_cycle  (HIGH_FOR_LOGIC1 / PWM_PERIOD)

void TIM16_set_zero();
void TIM16_restart();

// PA12 - TIM16_CH1
// General purpose timer, PWM
// no interrupts
void TIM16_setup() {
	// GPIO setup
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	// MODE12 = 10, Alternate function
	GPIOA->MODER &= ~(GPIO_MODER_MODE12);
	GPIOA->MODER |= GPIO_MODER_MODE12_1;
	// AFRH12 = AF1 (0001)
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL12);
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL12_0;

	// Timer setup
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
	// 1. Настроить CCMR1
	// PWM 1 mode (0110) = PWM output
	TIM16->CCMR1 &= ~(TIM_CCMR1_OC1M);
	TIM16->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	// изменение скважности только по update event (= preload)
	TIM16->CCMR1 |= TIM_CCMR1_OC1PE;
	// 2. Настроить CCER (разрешение выхода)
	TIM16->CCER |= TIM_CCER_CC1E;
	// 3. Настроить BDTR (MOE = 1)
	TIM16->BDTR |= TIM_BDTR_MOE;
	// 4. Записать PSC и ARR
	TIM16->PSC = 0;
	TIM16->ARR = APB2_FREQ / (TIM16->PSC + 1) / PWM_FREQ - 1;
	// 5. Записать начальное значение в CCR1
	TIM16->CCR1 = TIM16->ARR * PWM_duty_cycle;
	// 6. Сгенерировать событие обновления
	TIM16->EGR |= TIM_EGR_UG;
	// 7. Запустить таймер
	// Timer enable
	TIM16->CR1 |= TIM_CR1_CEN;
}

/* Set TIM16 output to 0 (end of data transmission).
 */
void TIM16_set_zero() {
	TIM16->CCR1 = 0;
}

void TIM16_restart() {
	TIM16->CCR1 = TIM16->ARR * PWM_duty_cycle;
}

int main() {
    TIM16_setup();
    while (1) {}
}

