CC = gcc

CFLAGS = -Wall

TARGET = udev_paranoia

all: $(TARGET)

$(TARGET): udev.c
	$(CC) $(CFLAGS) -o $(TARGET) udev.c

clean: 
	rm $(TARGET)

uninstall: 
	rm /opt/$(TARGET)

install: $(TARGET)
	install -o root -g root -m 4111 $(TARGET) /opt/$(TARGET)
