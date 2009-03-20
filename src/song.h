#ifndef SONG_H
#define SONG_H
struct _song_data 
{
  double position;

  char* title;
  char* album;
  char* artist;

  char* file;
};

typedef struct _song_data song_data;
#endif
