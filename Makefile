# Source files listing variables
SRCS = main.c startup_gcc.c

# All the files will be generated with this name (.elf .bin .txt)
PROJ_NAME=main

# Location of the Libraries folder

# Location of the Linker Scripts
LDSCRIPT_INC = Device/ldscripts

# Location of the OpenOCD Board configuration file

# Flashing tool
FLASH_TOOL = lm4flash

##############################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

# These are the typical compilation GCC flags
CFLAGS = -Wall -g -std=c99 -Os

# Machine dependant options for ARM 
CFLAGS += -mcpu=cortex-m4 -mthumb 

# Optimization flags
CFLAGS += -ffunction-sections -fdata-sections

# Linking option flags
CFLAGS += -Wl,--gc-sections

##############################################################################

ROOT=$(shell pwd)

# Set search path for header and source files
vpath %.c src

CFLAGS += -I $(ROOT)/inc -I inc
CFLAGS += -include stdint.h

OBJS=$(SRCS:.c=.o)

##############################################################################

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LDSCRIPT_INC) -T tm4c123g.ld
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf > $(PROJ_NAME).lst
	$(FLASH_TOOL) $(PROJ_NAME).bin

flash:
	$(FLASH_TOOL) $(PROJ_NAME).bin

clean:
	rm -f *.o
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).lst