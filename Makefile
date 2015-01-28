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
	update-rc.d udev_shutdown.sh  remove
	rm /etc/init.d/udev_shutdown.sh

install: $(TARGET)
	install -o root -g root -m 4111 $(TARGET) /opt/$(TARGET)


install_init: $(TARGET)
	install -o root -g root -m 4111 $(TARGET) /opt/$(TARGET)
	install -o root -g root -m 0755 udev_shutdown.sh /etc/init.d/udev_shutdown.sh
	update-rc.d udev_shutdown.sh defaults
