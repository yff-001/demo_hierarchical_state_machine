# AVR-GCC Compiler and flags
CC = avr-gcc
CFLAGS = \
	-mmcu=$(MCU) \
	-DF_CPU=16000000UL \
	-Werror \
	-Os
# LDFLAGS = -Wl,--gc-sections \

# AVRDUDE settings
BAUDRATE = 115200
PROGRAMMER = arduino
MCU = atmega328p
PORT = /dev/ttyUSB0
RM = rm

# Directories
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC = $(shell dir /s /b $(SRC_DIR)\*.c)
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC:.c=.o))

all:
	@echo $(OBJ_DIR)
	@echo $(SRC)

# Executable
# TARGET = $(BIN_DIR)/app.elf
# HEX = $(BIN_DIR)/app.hex

# all: $(TARGET) $(HEX)

# $(TARGET): $(OBJ) $(LIBOBJ)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# $(HEX): $(TARGET)
# 	avr-objcopy -O ihex -R .eeprom $(TARGET) $(HEX)

# upload: $(HEX)
# 	avrdude -b$(BAUDRATE) -c$(PROGRAMMER) -P$(PORT) -p$(MCU) -D -v -V -U flash:w:$(HEX)

# size: $(TARGET)
# 	avr-size --mcu=$(MCU) --format=avr $(TARGET)

# clean:
# 	$(RM) -r $(OBJ_DIR)/*
# 	$(RM) $(BIN_DIR)/*

# .PHONY: all clean upload size
