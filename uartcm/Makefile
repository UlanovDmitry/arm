
TOOLCHAIN_PATH = $(ARM_TOOLCHAIN)
BIN_PATH = $(TOOLCHAIN_PATH)/bin
PREFIX = arm-none-eabi-

GCC = $(BIN_PATH)/$(PREFIX)gcc
OBJCOPY = $(BIN_PATH)/$(PREFIX)objcopy
OBJDUMP = $(BIN_PATH)/$(PREFIX)objdump
NM = $(BIN_PATH)/$(PREFIX)nm

all:
	echo $(TOOLCHAIN_PATH)
	echo $(BIN_PATH)
	$(GCC) --version
	$(OBJCOPY) --version
	$(OBJDUMP) --version
	$(NM) --version


PHONY: all
