#include <Elementary.h>

#include "song.h"

Evas_Object* playlist_add(Evas_Object *win);
void playlist_pause();
void playlist_stop();
void playlist_play();
void playlist_append_file(char* filename);
void playlist_serialize();
void playlist_deserialize();
song_data *playlist_current_song_data_get();
