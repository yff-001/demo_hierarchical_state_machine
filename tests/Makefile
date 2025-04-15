CC = gcc
CFLAGS = -Wall -I../include -Iunity -DTESTING
SRC = test_log.c ../src/log.c unity/unity.c
TARGET = test_log

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
