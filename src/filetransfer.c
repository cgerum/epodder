#include "filetransfer.h"
#include <stdio.h>

int filetransfer_download(char* url, char* to)
{
  if(!url || !to)
    {
      printf("Cannot download!\n");
      return -1;
    }

  ecore_file_download(url, to, NULL, NULL, NULL);

  return 0;
}

