#include "../Inc/stm32f1xx.h"

int main(void){

    uint32_t i;

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13_0;

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH &= ~GPIO_CRH_CNF12;
    GPIOA->CRH |= GPIO_CRH_MODE12_0;

    while (1){
        GPIOC->BSRR = GPIO_BSRR_BR13;
        GPIOA->BSRR = GPIO_BSRR_BR12;
        for(i=0;i<200000;i++){}
        GPIOC->BSRR = GPIO_BSRR_BS13;
        GPIOA->BSRR = GPIO_BSRR_BS12;
        for(i=0;i<200000;i++){}
    }
}