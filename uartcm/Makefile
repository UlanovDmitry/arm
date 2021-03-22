
TOOLCHAIN_PATH = $(ARM_TOOLCHAIN)
BIN_PATH = $(TOOLCHAIN_PATH)/bin
INCLUDE_PATH = $(TOOLCHAIN_PATH)/include
PREFIX = arm-none-eabi-

PROJECT_NAME = uartcm
BUILD_DIR = build

CC = $(BIN_PATH)/$(PREFIX)gcc
AS = $(BIN_PATH)/$(PREFIX)gcc -x assembler-with-cpp
LD = $(BIN_PATH)/$(PREFIX)ld
CP = $(BIN_PATH)/$(PREFIX)objcopy
SZ = $(BIN_PATH)/$(PREFIX)size
DP = $(BIN_PATH)/$(PREFIX)objdump
NM = $(BIN_PATH)/$(PREFIX)nm --print-size -a -n
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

CFLAGS = -c -std=gnu99 -mcpu=cortex-m3 -mthumb -Wall -g3 
C_DEFS = -DSTM32F103xB
C_INCLUDES = 
#-IInc
C_SOURCES = \
	src/main.c 
# src/startup.c


LDSCRIPT = scripts/stm32f103c8.ld 

LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = -g -T$(LDSCRIPT)

all: build

compile: 
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/main.o src/main.c

link: compile
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/$(PROJECT_NAME).elf $(BUILD_DIR)/main.o

list: link
	$(NM) $(BUILD_DIR)/main.o 
	$(NM) $(BUILD_DIR)/$(PROJECT_NAME).elf 

build: link
	$(BIN) $(BUILD_DIR)/$(PROJECT_NAME).elf $(BUILD_DIR)/$(PROJECT_NAME).bin 

clean: 
	-rm -fR $(BUILD_DIR)/*

flash: build 
	st-flash write $(BUILD_DIR)/$(PROJECT_NAME).bin 0x08000000 

backup:
	st-flash read $(BUILD_DIR)/backup.bin 0x08000000 0x20000


PHONY: compile link list build clean flash backup all
