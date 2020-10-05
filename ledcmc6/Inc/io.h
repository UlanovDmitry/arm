#ifndef __IO_H
#define __IO_H

#include "../Inc/stm32f1xx.h"

#define bool unsigned char
#define true (0x01)
#define false (0x00)

// Режимы работы портов
#define IN (0x00)
#define OUT_10MHz (0x01)
#define OUT_2MHz  (0x02)
#define OUT_50MHz (0x03) 

#define OUT_PP   (0x00)
#define OUT_OD   (0x04)
#define OUT_APP  (0x08)
#define OUT_AOD  (0x0C) 

#define IN_ADC   (0x00)
#define IN_HIZ   (0x04)
#define IN_PULL  (0x08)

// Состояние портов
typedef enum {
	OFF = 0,
	ON = 1,
	LOW = 0,
	HIGH =1
} tIOState;

// Назначения портов
typedef enum {
	io_Led0 = 0, 
	io_Led1 = 1,
	io_Led2,
	io_Led3,
	io_Led4,
	io_Led5,
	io_Led6,
	io_Led7,

	io_Back0,
	io_Back1,
	io_Back2,
	io_Back3,
	io_Back4,
	io_Back5,

	io_Blink
} tIOLine;

// Функции работы с портами
void IO_ConfigLine(tIOLine Line, uint8_t Mode, uint8_t State); 
void IO_SetLine(tIOLine Line, bool State); 
void IO_InvertLine(tIOLine Line); 
bool IO_GetLine(tIOLine Line); 

// Инициализация портов
void IO_Init(void); 

#endif