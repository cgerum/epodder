#include "config_files.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *configdir_abs = NULL;


char *config_file_get(char *file){
  char *configfile_abs = malloc(sizeof(char)*(strlen(configdir_abs)+strlen(file)+1));

  sprintf(configfile_abs, "%s%s", configdir_abs, file);

  return configfile_abs;
}

void init_files()
{
  char *homedir = getenv("HOME");
  char *configdir = "/.epodder/"; 
  configdir_abs = malloc(sizeof(char)*(strlen(homedir)+strlen(configdir)+1));
  sprintf(configdir_abs, "%s%s", homedir, configdir);

  if(!ecore_file_exists(configdir_abs))
    {
      ecore_file_mkdir(configdir_abs);
    }

  printf("configdir: %s", configdir);

  //free(homedir);
}
