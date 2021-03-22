#include <stdint.h>
 
#define APB2ENR   (*(uint32_t*)(0x40021000+0x18))
#define APB2ENR_ENIOC (1u<<4u)
 
#define GPIOC_CRH (*(uint32_t*)(0x40011000+0x04))
#define xGPIO_CRH_MODE13_0 (1u <<20u)
#define xGPIO_CRH_MODE13_1 (1u <<21u)
 
#define GPIOC_ODR (*(uint32_t*)(0x40011000+0x0c))
#define GPIO_ODR_PIN_13 (1u<<13u)

__attribute__((unused)) int var_a;
__attribute__((unused)) int var_b= 0;
__attribute__((unused)) int var_c= 0x1234;

__attribute__((noreturn))
void Reset_Handler(){
    //Импортируем символы, которые мы создали в скрпите линковки
    extern uint8_t __data_start__, 
           __data_end__, __data_rom__, 
           __bss_start__, __bss_end__;
    uint8_t *dst;
    uint32_t i;

    //Обнулим сецию BSS
    dst = &__bss_start__;
    while (dst < &__bss_end__)
        *dst++ = 0;

    //Инициализируем переменные в .data данным из флеш-памяти
    uint8_t *src = &__data_rom__;
    dst = &__data_start__;
    while (dst < &__data_end__)
        *dst++ = *src++;

    //Разрешаем тактировать GPIOC на шине APB2
    APB2ENR |= APB2ENR_ENIOC;
    // Настраиваем GPIO Pin 13 как выход Push-Pull на максимальной частоте
    GPIOC_CRH |= xGPIO_CRH_MODE13_0 | xGPIO_CRH_MODE13_1;
    while(1){
        // Переключаем пин 13 на порте C
        GPIOC_ODR ^= GPIO_ODR_PIN_13;
        for(i=0;i<200000;i++){}  // пауза 
    }
}
 
 
// Объявим тип - указатель на прерывание
typedef void (*isr_routine)(void);
 
// Опишем структуру таблицы векторов прерываний
typedef struct  {
    const uint32_t * stack_top;
    const isr_routine reset;
} ISR_VECTOR_t;
 
//Получим адрес указателья на стек из скрипта линковки
extern const uint32_t __stack_top__;
 
//Укажем линковщику, что эту константу нужно положить в секцию .isr_vector
__attribute__((section(".isr_vector"), __unused__))
const ISR_VECTOR_t  isr_vector = {
       .stack_top = &__stack_top__,
       .reset  = &Reset_Handler,
};
