# AVR-GCC Compiler and flags
CC = avr-gcc
CFLAGS = \
	-mmcu=$(MCU) \
	-DF_CPU=16000000UL \
	-Werror \
	-Os \
	-MMD -MP

LDFLAGS = -Wl,--gc-sections

# AVRDUDE settings
BAUDRATE ?= 115200
PROGRAMMER ?= arduino
MCU ?= atmega328p
PORT ?= /dev/ttyUSB0
RM = rm

# Directories
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

# Source files
SRC = $(shell find $(SRC_DIR) $(LIB_DIR) -name *.c)
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

# Executable
TARGET = $(BUILD_DIR)/app.elf
HEX = $(BUILD_DIR)/app.hex

all: $(TARGET) $(HEX)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(HEX): $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(HEX)

upload: $(HEX)
	avrdude -b$(BAUDRATE) -c$(PROGRAMMER) -P$(PORT) -p$(MCU) -D -v -V -U flash:w:$(HEX)

size: $(TARGET)
	avr-size --mcu=$(MCU) --format=avr $(TARGET)

clean:
	$(RM) -rf $(BUILD_DIR)

-include $(DEP)

.PHONY: all clean upload size
