#include "../Inc/stm32f1xx.h"
#include "../Inc/io.h"

// проверка записи слова в порт GPIOx_ODR
// структуры для работы с портами
// выбрать порты из распиновки для входов и выходов

//  arm-softmmu/qemu-system-arm -machine stm32-f103c8 -kernel image.bin -s
// массив цифр для индикатора, расширенный до 16 значений
#define byte unsigned char
const byte digits[16] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 
    0x7f, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int main(void){

    uint32_t i;
    IO_Init();

    while (1)
    {
        IO_SetLine(io_LedOut,ON);
        IO_SetLine(io_LedIn,ON);
        for(i=0;i<200000;i++){}
        IO_SetLine(io_LedOut,OFF);
        IO_SetLine(io_LedIn,OFF);
        for(i=0;i<200000;i++){}

    }
    


    // // Включаем тактирование портов A и B 
    // RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // // Устанавливаем режимы для портов A и B 
    

    // RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // GPIOC->CRH &= ~GPIO_CRH_CNF13;
    // GPIOC->CRH |= GPIO_CRH_MODE13_0;

    // RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // GPIOA->CRH &= ~GPIO_CRH_CNF12;
    // GPIOA->CRH |= GPIO_CRH_MODE12_0;

    // while (1){
    //     GPIOC->BSRR = GPIO_BSRR_BR13;
    //     GPIOA->BSRR = GPIO_BSRR_BR12;
    //     for(i=0;i<200000;i++){}
    //     GPIOC->BSRR = GPIO_BSRR_BS13;
    //     GPIOA->BSRR = GPIO_BSRR_BS12;
    //     for(i=0;i<200000;i++){}
    // }
}