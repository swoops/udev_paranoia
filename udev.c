/*
*    udev_paranoia, Copyright (c) 2014-2015 Dennis Goodlett <dennis@hurricanelabs.com>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define  no_usb "# this rule does not allow any new usb devices, use script to disable\nACTION==\"add\", DRIVERS==\"usb\",  ATTR{authorized}=\"0\"\n"
#define fname "/etc/udev/rules.d/11-to_rule_all.rules"
#define wait 10 // wait 10 seconds for new usb device

static unsigned int euid, ruid;
void do_setuid (void);
void undo_setuid(void);
void make_file();
void sig_handler(int signo);

int main(int argc, char *argv[]){
  char * allow_rule;
  ruid = getuid();
  euid = geteuid();

  // allow only USB block devices
  char rule1[] = 
    "#tmp rule allows only block devices\n"
    "ACTION==\"add\", ATTRS{product}==\"USB-HID Keyboard\",  ATTR{authorized}=\"0\"\n";

  // rule to allow usb drives for a bit
  char rule2[] = 
    "#tmp allows all USB devices\n"
    "ACTION==\"add\", DRIVERS==\"usb\"\n";

  if (argc > 1)
    allow_rule = rule2;
  else
    allow_rule = rule1;

  // retore paranoid udev rule always
  if (signal(SIGTERM, sig_handler) == SIG_ERR) return 88;
  if (signal(SIGINT, sig_handler) == SIG_ERR) return 88;
  if (signal(SIGUSR1, sig_handler) == SIG_ERR) return 88;
  atexit(make_file);

  FILE *fp;
  do_setuid();
  fp = fopen(fname, "r+"); // open read/write, fails if no file exists
  undo_setuid();

  if (fp){
    fprintf(fp, "%s", allow_rule); // having opened the file rw we overwrite it with something longer...
    if (ftruncate(fileno(fp), strlen(allow_rule)) != 0) return 27;
    fclose(fp);
    sleep(wait);
  }
  return 0;
}

void do_setuid (void){
  int status;
#ifdef _POSIX_SAVED_IDS
  status = seteuid(euid);
#else
  status = setreuid(ruid, euid);
#endif
  if (status < 0){
    fprintf(stderr, "Couldn't set uid.\n");
    exit(status);
  }
}

void undo_setuid(void) {
  int status;
#ifdef _POSIX_SAVED_IDS
  status = seteuid(ruid);
#else
  status = setreuid(euid, ruid);
#endif
  if (status < 0){
    fprintf(stderr, "Couldn't set uid.\n");
    exit(status);
  }
}

void make_file(){
  /* printf("making the file now\n"); */
  FILE *fp;
  do_setuid();
  if (( fp = fopen(fname, "w") ))
    fprintf(fp, "%s", no_usb);
  else
    fprintf(stderr, "ERROR: could not make paranoid udev rules\n");
  undo_setuid();
}

void sig_handler(int signo){
  if (signo == SIGUSR1) printf("received SIGUSR1\n");
  else if (signo == SIGTERM) printf("received SIGSTERM\n");
  else if (signo == SIGINT) printf("\nreceived SIGINT\n");
  make_file();
}

