#include "../Inc/stm32f1xx.h"
#include "../Inc/io.h"

//  arm-softmmu/qemu-system-arm -machine stm32-f103c8 -kernel image.bin -s

#define byte unsigned char
#define uint32 unsigned int
#define _PMV(p,m,v) ((p&(~m))|(v&m)) // установить значение по маске

const byte digits[16] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 
    0x7f, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint32 mskA = 0xff,
             mskB = 0x3f;

void outDigit(byte d,int pos);

int main(void){

    uint32 i; 

    IO_Init(); 
    while (1)
    { 
        for (int j=0; j<6; j++){
            outDigit(digits[j],j); 
            for(i=0;i<200;i++){} 
        }
    }
}

void outDigit(byte d, int pos){
    // GPIOB->ODR |= mskB;  // тушим все выходы
    for (int i=0; i<6; i++){
        IO_SetLine(io_Back0+i,ON);  // зажигаем нужный выход 
    }
    GPIOA->ODR = _PMV(GPIOA->IDR, mskA, (uint32)d);
    IO_SetLine(io_Back0+pos,OFF);  // зажигаем нужный выход
}

