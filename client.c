#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "common.h"


#define DEFAULT_TIME 10

void read_perms(int perms){
  if ( perms == 0 )
    perms = get_permissoins();
  printf("Set permissions: \n");
  if ( perms & BLOCK_ALL ) printf("\t BLOCK_ALL\n");
  if ( perms & ALLOW_ALL ) printf("\t ALLOW_ALL\n");
  if ( perms & BLOCK_USBHID ) printf("\t BLOCK_USBHID\n");
}

void set_perm_wrapper(int perms){
  int ret = set_permissoins(perms);
  if ( ret ){
    fprintf(stderr, "[!!] Failed to set permissions!!!");
    read_perms(0);
    exit(1);
  }
  read_perms(perms);
}

void sig_handler(int signo){
  if (signo == SIGTERM) printf("received SIGSTERM\n");
  else if (signo == SIGINT) printf("\nreceived SIGINT\n");
  set_perm_wrapper(BLOCK_ALL);
  exit(0);
}

void help_menu( const char *pname, int err){
  FILE *fp = stdout;
  if ( err ) fp = stderr;
  fprintf(fp, "Usage: \n");
  fprintf(fp, "%s [FLAGS]\n", pname);
  fprintf(fp, "FLAGS:\n");
  fprintf(fp, "\t-h:   help menu\n");
  fprintf(fp, "\t-a:   allow all EVERYTHING\n");
  fprintf(fp, "\t-i:   block only input/hid/hidraw devices\n");
  fprintf(fp, "\t-b:   block EVERYTHING\n");
  fprintf(fp, "\t-r:   read current permissions\n");
  fprintf(fp, "\t-t:   temp permission change wait time (0 for permanent))\n");
  exit(err);
}

int main(int argc, char *argv[]) {
  int perms = 0;
  int time = DEFAULT_TIME;

  if ( argc != 1 ) {
    /* parse commands */
    int c; // for command line parsing
    while ((c = getopt (argc, argv, "habirt:")) != -1){
      switch (c) {
        case 'h':   // help menu
          help_menu(argv[0], 0);
          break;
        case 'a':   // allow all
          if ( perms ){
            fprintf(stderr, "[!!] cain't set other values with -a\n");
            help_menu(argv[0], 1);
          }
          perms |= ALLOW_ALL;
          break;
        case 'b': // block all
          if ( perms ){
            fprintf(stderr, "[!!] cain't set other values with -b\n");
            help_menu(argv[0], 1);
          }
          perms |= BLOCK_ALL;
          break;
        case 'i': // block input/hid only
          if ( perms & ALLOW_ALL || perms & BLOCK_ALL ){
            fprintf(stderr, "[!!] can't use -u with -a or -b\n");
            help_menu(argv[0], 1);
          }
          perms |= BLOCK_USBHID;
          break;
        case 't': // set a time for a temporary change
          if ( sscanf(optarg, "%d", &time) != 1 ){
            fprintf(stderr, "[!!] invalid wait time\n");
            help_menu(argv[0], 1);
          }
          break;
        case 'r':
          read_perms(0);
          return 0;
          break;
      default:
        help_menu(argv[0], 1);
        break;
      }
    }
  }

  if ( ! perms ) help_menu(argv[0], 0);

  set_perm_wrapper(perms);

  if ( perms == BLOCK_ALL || time == 0) return 0;

  // catch signals for temp rule change
  if (
        signal(SIGTERM, sig_handler) == SIG_ERR ||
        signal(SIGINT, sig_handler) == SIG_ERR  ||
        signal(SIGUSR1, sig_handler) == SIG_ERR
    ) 
    printf("[!!] Warning: could not set signal handler\n");

  for (int t = time; t>=0; t--){
    printf("\e[2K\e[G sleeping: %3d  ", t);
    fflush(stdout);
    sleep(1);
  }
  printf("\n");
  set_perm_wrapper(BLOCK_ALL);

  return 0;
}
