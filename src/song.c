#include <Eina.h>
#include <Eet.h>

#include "song.h"

Eet_Data_Descriptor *song_des_get()
{
  Eet_Data_Descriptor *song_data_des;
  
  song_data_des = eet_data_descriptor_new("song_data", sizeof(song_data),
			  eina_list_next,
			  eina_list_append,
			  eina_list_data_get,
			  eina_list_free,
			  eina_hash_foreach,
			  NULL,
			  NULL);

  
  EET_DATA_DESCRIPTOR_ADD_BASIC(song_data_des, song_data, "position", position, EET_T_DOUBLE);
  EET_DATA_DESCRIPTOR_ADD_BASIC(song_data_des, song_data, "title", title, EET_T_STRING);
  EET_DATA_DESCRIPTOR_ADD_BASIC(song_data_des, song_data, "album", album, EET_T_STRING);
  EET_DATA_DESCRIPTOR_ADD_BASIC(song_data_des, song_data, "artist", artist, EET_T_STRING);
  EET_DATA_DESCRIPTOR_ADD_BASIC(song_data_des, song_data, "file", file, EET_T_STRING);
  return song_data_des;
}
