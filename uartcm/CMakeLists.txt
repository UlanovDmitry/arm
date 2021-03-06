CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# defines
ADD_DEFINITIONS(-DSTM32F103xB)

set(CMAKE_VERBOSE_MAKEFILE YES)
set(CMAKE_BUILD_TYPE Debug)

# toolchain 
include(stm32_toolchain.cmake)

PROJECT(uartcm)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../drivers/CMSIS/Include/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../drivers/CMSIS/Device/ST/STM32F1xx/Include/)

SET(PROJECT_SOURCES
        src/main.c
        #src/main.h
        #src/startup.c
        #src/startup.h
        )


#linker script
SET(LD_SCRIPT stm32f103c8.ld)
SET(LD_SCRIPTS_DIR ${PROJECT_SOURCE_DIR}/scripts/)
SET(CMAKE_EXE_LINKER_FLAGS "-L${LD_SCRIPTS_DIR} -T${LD_SCRIPT} ${CMAKE_EXE_LINKER_FLAGS}")


INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/src/
) 
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf
        ${PROJECT_SOURCES}
        )


# elf -> hex,bin 
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_SIZE} ARGS --format=sysv ${CMAKE_PROJECT_NAME}.elf)
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_SIZE} ARGS --format=berkeley ${CMAKE_PROJECT_NAME}.elf)


# make show-symbols 
ADD_CUSTOM_TARGET(show-symbols
	COMMAND ${CMAKE_NM} --print-size -a -n ${CMAKE_PROJECT_NAME}.elf
	DEPENDS ${CMAKE_PROJECT_NAME}.elf
	)

