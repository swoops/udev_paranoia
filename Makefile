CC = gcc
CFLAGS = -Wall

CLIENT = udev_paranoia
MASTER = udev_paranoia_master
RULE = 11-udev_paranoia.rules

CLIENT_INST = /opt/$(CLIENT)
MASTER_INST = /lib/udev/$(MASTER)
RULE_INST   = /etc/udev/rules.d/$(RULE)

all: $(CLIENT) $(MASTER)

common.o: common.c 
	$(CC) $(CFLAGS) -c common.c 

$(CLIENT): client.c common.o
	$(CC) $(CFLAGS) -o $(CLIENT) common.o client.c

$(MASTER): master.c common.o
	$(CC) $(CFLAGS) -o $(MASTER) common.o master.c

install: $(CLIENT) $(MASTER) $(RULE)
	install -o root -g root -m 111 $(CLIENT) $(CLIENT_INST)
	install -o root -g root -m 111 $(MASTER) $(MASTER_INST)
	install -o root -g root -m 611 $(RULE)   $(RULE_INST)
	udevadm control --reload

uninstall:
	rm $(CLIENT_INST)
	rm $(MASTER_INST)
	rm $(RULE_INST)
	udevadm control --reload

clean: 
	rm $(MASTER)
	rm $(CLIENT)
	rm common.o
