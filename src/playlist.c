#include "playlist.h"
#include "song.h"
#include "config_files.h"
#include "player.h"

#include <stdio.h>
#include <Eet.h>


#define savefile config_file_get("data.eet")

Evas_Object* playlist = NULL;
Evas_Object* player = NULL; 

Elm_List_Item* current_song = NULL;

   

Evas_Object* playlist_add(Evas_Object *win)
{ 
  if (! playlist)
    {
      playlist = elm_list_add(win);

      playlist_deserialize();
      
      elm_list_go(playlist);
      //elm_win_resize_object_add(win, playlist);
      evas_object_size_hint_align_set(playlist, -1.0, -1.0);
      evas_object_size_hint_weight_set(playlist, 1.0, 1.0);
    }
      
  return playlist;
}

void playlist_append(song_data *song)
{
  elm_list_item_append(playlist, song->title, NULL, NULL, NULL, (void*)song);

  elm_list_go(playlist);
}


void playlist_delete_selected()
{
  //Eina_List *items = elm_list_selected_items_get(playlist);
  
}

void playlist_append_file(char* filename){
  song_data *song = (song_data*) malloc(sizeof(song_data));
  
  song->position = 0.0;
  song->length = 0.0;
  song->file = filename;
  song->title = filename;
  song->artist="test";
  song->album="test";

  playlist_append(song);
}

void playlist_pause(){
  if(current_song){
    song_data *data = (song_data*)elm_list_item_data_get(current_song);
    
    data->position = player_position_get(); 
    printf("Pausing at: %f\n", data->position);
  }
  player_state_set(PLAYER_STATE_STOP);
}

void playlist_stop(){
  if(current_song){
    song_data *data = (song_data*)elm_list_item_data_get(current_song);
    data->position = 0.0; 
  }

  current_song = NULL;

  player_state_set(PLAYER_STATE_STOP);
}

void playlist_play(){
  playlist_pause();
  current_song = elm_list_selected_item_get(playlist);
  if(! current_song){
    Eina_List *items = (Eina_List*)elm_list_items_get(playlist);
    if(!items){
      printf("Empty Playlist nothing to play\n");
      return;
    }
    current_song = (Elm_List_Item*)eina_list_data_get(items);
  }

  song_data *data = (song_data*)elm_list_item_data_get(current_song);
  
  player_file_load(data->file);
  printf("playing %s at %f\n", data->title, data->position);
  player_position_set(data->position);
  printf("playing %s at %f\n", data->title, data->position);
  player_state_set(PLAYER_STATE_PLAYING);
}


void playlist_remove_selected()
{
  Elm_List_Item *selected =  elm_list_selected_item_get(playlist);

  //printf("Removing: selected=%x, current=%x\n", selected, current_song);

  if(!selected){
    printf("nothing selected!\n");
    return;
  }

  if (selected == current_song){
    playlist_stop();
    current_song = NULL;
  }

  song_data *data = (song_data*)elm_list_item_data_get(selected);

  
  //FIXME: free song_data

  elm_list_item_del(selected);
  elm_list_go(playlist);
}

struct _playlist_holder {
  Eina_List *playlist;
};

typedef struct _playlist_holder playlist_holder;

Eet_Data_Descriptor *playlist_des_get()
{
  Eet_Data_Descriptor *song_data_des, *playlist_des;

  song_data_des = song_des_get();

  
  playlist_des = eet_data_descriptor_new("playlist_holder", sizeof(playlist_holder),
					 eina_list_next,
					 eina_list_append,
					 eina_list_data_get,
					 eina_list_free,
					 eina_hash_foreach,
					 NULL,
					 NULL);

  EET_DATA_DESCRIPTOR_ADD_LIST(playlist_des, playlist_holder, "playlist", playlist, song_data_des);

  return playlist_des;
}



void playlist_serialize()
{
  Eet_File *pl_file = NULL;
  Eina_List *items = NULL;
  Eina_List *i = NULL;
  Elm_List_Item *item = NULL;
  
  Eina_List *encode = NULL;
  Eet_Data_Descriptor *pd;
  playlist_holder ph;
  playlist_pause();
  
  pd = playlist_des_get();

  pl_file = eet_open(savefile, EET_FILE_MODE_WRITE);
  if(!pl_file)
    {
      printf("Could not create file!\n");
      return;
    }
  
  items = (Eina_List*)elm_list_items_get(playlist);
  if(items){
    EINA_LIST_FOREACH(items, i, item)
      {
	song_data *data;
	data = (song_data*)elm_list_item_data_get(item);
	encode = eina_list_append(encode, data);

	printf("Encoding %f, %s, %s, %s \n", data->position, data->title, data->album, data->artist, data->file);
      }
  }
  ph.playlist = encode;

  eet_data_write_cipher(pl_file, 
			pd, 
			"Playlist", 
			"/epodder/playlist",
			&ph,
			0);

  eet_close(pl_file);
}


void playlist_deserialize()
{
  Eet_File *pl_file = NULL;
  Eina_List *items = NULL;
  Eina_List *i = NULL;
  
  song_data *data; 
  Eet_Data_Descriptor *pd;
  playlist_holder *ph;

  pl_file = eet_open(savefile, EET_FILE_MODE_READ);
 
  pd = playlist_des_get();
  if(!pl_file)
    {
      printf("Could not open file!\n");
      return;
    }

  ph = (playlist_holder*)eet_data_read_cipher(pl_file, 
			pd, 
			"Playlist", 
			"/epodder/playlist");

  
  
  items = ph->playlist;
  if(items){
    EINA_LIST_FOREACH(items, i, data)
      {
	playlist_append(data);
      }
  }

  

  eet_close(pl_file);
}

song_data* playlist_current_song_data_get()
{
  song_data *data = NULL;
  if(current_song)
    {
      data = (song_data*)elm_list_item_data_get(current_song);
      data->position = player_position_get();
      if(data->length == 0.0)
	data->length = player_length_get();
      //printf("length3: %f\n", data->length);
    }

  return data;
}
