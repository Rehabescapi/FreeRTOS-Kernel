# nRF application makefile
PROJECT_NAME = $(shell basename "$(realpath ./)")

# Configurations
NRF_IC = nrf52832
SDK_VERSION = 15
SOFTDEVICE_MODEL = blank

# Source and header files
APP_HEADER_PATHS += ./include
APP_HEADER_PATHS += ./build/include
APP_SOURCE_PATHS += .
APP_SOURCES = $(notdir $(wildcard ./*.c)) 

# APP_SOURCES+= $(notdir ./portable/MemMang/heap_2.c)
#APP_SOURCES += ~/FreeRTOS-Kernel/portable/MemMang/heap_2.c
APP_SOURCES+= $(notdir $(wildcard ./portable/GCC/nrf52/*.c))


# Path to base of nRF52-base repo
NRF_BASE_DIR = ../buckler/software/nrf52x-base/

$(info $$APP_SOURCES IS [${APP_SOURCES}])
# Include board Makefile (if any)
include ../buckler/software/boards/buckler_revC/Board.mk
#include ./Board.mk
# Include main Makefile
include $(NRF_BASE_DIR)make/AppMakefile.mk