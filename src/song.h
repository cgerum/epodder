#ifndef SONG_H
#define SONG_H
struct _song_data 
{
  double position;
  double length;

  char* title;
  char* album;
  char* artist;

  char* file;
};

typedef struct _song_data song_data;

Eet_Data_Descriptor *song_des_get();
#endif
