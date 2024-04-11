# Compiler
CC = avr-gcc

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
SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBOBJ := $(LIB_DIR)/state_machine.o

CFLAGS = \
	-mmcu=$(MCU) \
	-DF_CPU=16000000UL \
	-Werror \
	-Os \
	-I$(LIB_DIR)

# LDFLAGS = -Wl,--gc-sections \

# Executable
TARGET = $(BIN_DIR)/app.elf
HEX = $(BIN_DIR)/app.hex

all: $(TARGET) $(HEX)

$(TARGET): $(OBJ) $(LIBOBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(LIB_DIR)/state_machine.o: $(LIB_DIR)/state_machine.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(HEX): $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(HEX)

upload: $(HEX)
	avrdude -b$(BAUDRATE) -c$(PROGRAMMER) -P$(PORT) -p$(MCU) -D -v -V -U flash:w:$(HEX)

size: $(TARGET)
	avr-size --mcu=$(MCU) --format=avr $(TARGET)

clean:
	$(RM) $(LIB_DIR)/*.o
	$(RM) -r $(OBJ_DIR)/*
	$(RM) $(BIN_DIR)/*

.PHONY: all clean upload size
