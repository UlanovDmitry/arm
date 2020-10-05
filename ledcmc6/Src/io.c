#include "../Inc/io.h"

// Структура конфигурации портов 
typedef struct {
	GPIO_TypeDef* GPIOx;	// Имя порта
	uint16_t GPIO_Pin;	    // Номер порта
	uint8_t MODE;		    // Режим
	uint8_t DefState;		// Стартовое значение (уйдет в бит ODR при инициализации)
} tGPIO_Line;

// Настройки портов 
const tGPIO_Line IOs[] = {
			{ GPIOA, 0,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 1,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 2,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 3,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 4,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 5,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 6,  OUT_10MHz + OUT_PP, LOW},	 
			{ GPIOA, 7,  OUT_10MHz + OUT_PP, LOW},	 

			{ GPIOB, 0,  OUT_10MHz + OUT_PP, HIGH},	 
			{ GPIOB, 1,  OUT_10MHz + OUT_PP, HIGH},	 
			{ GPIOB, 2,  OUT_10MHz + OUT_PP, HIGH},	 
			{ GPIOB, 3,  OUT_10MHz + OUT_PP, HIGH},	 
			{ GPIOB, 4,  OUT_10MHz + OUT_PP, HIGH},	 
			{ GPIOB, 5,  OUT_10MHz + OUT_PP, HIGH},	 

			{ GPIOC, 13,  OUT_10MHz + OUT_PP, HIGH}	 
    };
const uint32_t cIO_COUNT = sizeof(IOs)/sizeof(tGPIO_Line);

// Установить настройки порта 
void IO_ConfigLine(tIOLine Line, uint8_t Mode, uint8_t State) { 
	if(IOs[Line].GPIO_Pin < 8){ // Определяем в старший или младший регистр надо запихивать данные. 
		IOs[Line].GPIOx->CRL &=   ~(0x0F << (IOs[Line].GPIO_Pin * 4));	// Стираем биты
		IOs[Line].GPIOx->CRL |=  Mode<<(IOs[Line].GPIO_Pin * 4);		// Вносим нашу битмаску, задвинув ее на нужное место. 
	} else {
		IOs[Line].GPIOx->CRH &=   ~(0x0F << ((IOs[Line].GPIO_Pin - 8)* 4));	// Аналогично для старшего регистра. 
		IOs[Line].GPIOx->CRH |=    Mode<<((IOs[Line].GPIO_Pin - 8)* 4);
	} 
	IOs[Line].GPIOx->ODR &= ~(1<<IOs[Line].GPIO_Pin);				// Прописываем ODR, устанавливая состояние по умолчанию. 
	IOs[Line].GPIOx->ODR |= State<<IOs[Line].GPIO_Pin;
}

// Установить состояние порта
void IO_SetLine(tIOLine Line, bool State) {
	if (State)   
	{	 
	 IOs[Line].GPIOx->BSRR = 1 << IOs[Line].GPIO_Pin;
	}
	else
	{
	 IOs[Line].GPIOx->BRR = 1 << IOs[Line].GPIO_Pin;
	}
}

// Инвертировать состояние порта
void IO_InvertLine(tIOLine Line) {
    IOs[Line].GPIOx->ODR ^= 1 << IOs[Line].GPIO_Pin;
}

// Получить состояние порта
bool IO_GetLine(tIOLine Line) {
	if (Line < cIO_COUNT)
		return ((IOs[Line].GPIOx->IDR) & (1<<IOs[Line].GPIO_Pin));
	else
		return false;
}

// Инициализация портов
void IO_Init(void) {

    // uint32_t IOCNT = cIO_COUNT; 

    // Тактирование нужных портов 
    RCC->APB2ENR	|= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR 	|= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR	|= RCC_APB2ENR_IOPCEN;
    // RCC->APB2ENR	|= RCC_APB2ENR_IOPDEN;
    // RCC->APB2ENR	|= RCC_APB2ENR_IOPEEN;
    // RCC->APB2ENR	|= RCC_APB2ENR_IOPFEN;
    // RCC->APB2ENR	|= RCC_APB2ENR_IOPGEN; 
    // RCC->APB2ENR	|= RCC_APB2ENR_AFIOEN; 
    
    // Применение настроек 
    for (int Line = 0; Line < cIO_COUNT; Line++) {
        IO_ConfigLine(Line, IOs[Line].MODE, IOs[Line].DefState);
	}
}