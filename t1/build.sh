#!/bin/bash

arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -g -o main.o main.s > main.log
arm-none-eabi-nm ./main.o >> main.log
arm-none-eabi-size -A ./main.o >> main.log
arm-none-eabi-ld -T link.ld main.o -o main.elf >> main.log
arm-none-eabi-objcopy -O binary ./main.elf ./main.bin >> main.log
