#define  PROTO_FILE "/tmp/udev_paranoia_protection"
#define  ALLOW_ALL            1  <<  0
#define  BLOCK_ALL            1  <<  1
#define  BLOCK_USBHID         1  <<  2
#define  BLOCK_USB_INTERFACE  1  <<  3

int get_permissoins();
int set_permissoins(int prot);
