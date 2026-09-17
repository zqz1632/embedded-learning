CC = gcc
CFLAGS = -fdiagnostics-color=always -g
SRCS = main.c circle.c
TARGET = main.exe

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean
clean:
	del $(TARGET)