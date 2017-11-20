#include <stdio.h>
#include "common.h"
#include <errno.h>
#include <string.h>

int get_permissoins(){
  FILE *fp;
  int ret;
  if ( (fp = fopen(PROTO_FILE, "r")) == NULL)
    return ALLOW_ALL; // assume file does not exist

  if ( fread(&ret, sizeof(ret), 1, fp) != 1 ){
    ret = ALLOW_ALL;
  }

  fclose(fp);
  return ret;
}

int set_permissoins(int prot){
  FILE *fp;
  int ret=0;
  if ( (fp = fopen(PROTO_FILE, "w")) == NULL){
    return 1;
  }

  if ( fwrite(&prot, sizeof(prot), 1, fp) != 1 ){
    ret = 1;
  }

  fclose(fp);
  return ret;
}

