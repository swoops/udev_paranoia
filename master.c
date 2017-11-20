#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h> // strcmp
#include "common.h"
#define ALLOW 1
#define DENY  0

int check_device(){
  // decides if the USB device will be blocked
  int ret = ALLOW;
  int perms = get_permissoins();
  if ( perms & ALLOW_ALL ) return ALLOW;
  if ( perms & BLOCK_ALL ) return DENY;

  if ( perms & BLOCK_USBHID && strcmp(getenv("DRIVER"), "usbhid") == 0)
    return DENY;

  return ret;
}

#ifdef DEBUG
void log_tmp(const char *msg){
  FILE *fp;
  if ( (fp = fopen("/tmp/udev_log", "a")) == NULL){
    fprintf(stderr, "[!!] Failed to log\n");
    exit(1);
  }
  fprintf(fp, "%s\n", msg);
  fclose(fp);
}

void log_env(int blk){
  extern char **environ;
  int i = 1;
  char *s = *environ;
  int perms = get_permissoins();
  FILE *fp;
  if ( (fp = fopen("/tmp/udev_log", "a")) == NULL){
    fprintf(stderr, "[!!] Failed to log\n");
    exit(1);
  }

  fprintf(fp, "===========\n");
  for (; s; i++) {
    fprintf(fp, "%s\n", s);
    s = *(environ+i);
  }

  if ( perms & BLOCK_ALL )     fprintf(fp, "\t BLOCK_ALL\n");
  if ( perms & ALLOW_ALL )     fprintf(fp, "\t ALLOW_ALL\n");
  if ( perms & BLOCK_USBHID ) fprintf(fp, "\t BLOCK_USBHID\n");

  if ( blk == ALLOW )
    fprintf(fp, "ALLOW\n");
  else
    fprintf(fp, "DENY\n");


  fprintf(fp, "-----------\n");
  fclose(fp);
}
#endif

void error(const char *msg){
  fprintf(stderr, 
    "This is to be run by UDEV only!\n"
    "%s\n", msg
    );
    exit(1);
}
 
int main(int argc, char *argv[]) {
  // double check this is being run by udev
  if ( argc != 1 )
    error("Invalid args");
  if ( getuid() != 0 ) 
    error("Failed root test");
  if ( getenv("PATH") )
    error("Failed env test");
  if ( getenv("PATH") )
    error("Only run on ADD event");

  #ifdef DEBUG
    int ret = check_device();
    log_env(ret);
    return ret;
  #else
    return check_device();
  #endif
}
