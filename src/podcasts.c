#include "podcasts.h"
#include "playlist.h"
#include "song.h"
#include <mrss.h>

#include <string.h>
#include <Elementary.h>
#include <Eina.h>

struct _podcasts_struct
{
  Eina_List *feeds;
};

typedef struct _podcasts_struct podcasts_struct;

struct _podcast_data
{
  char *title;
  char *feed;
  Eina_List *episodes;
};

typedef struct _podcast_data podcast_data;

struct _episode_data
{
  char *url;
  int new;
  int downloaded;
  char *pub_data;
  song_data *data;
};

typedef struct _episode_data episode_data;

podcasts_struct *podcasts = NULL;

void init_podcasts()
{
  if(!podcasts)
    {
      podcasts = malloc(sizeof(podcasts_struct));
      podcasts->feeds = NULL;
    }
}

void podcast_add(char *url)
{
  char *tmp;
  mrss_item_t *item;
  mrss_t *feed;
  mrss_error_t error;
  podcast_data *new_podcast;

  error = mrss_parse_url(url, &feed);
  if(error)
    {
      printf("download failed: %s", mrss_strerror(error));
      return;
    }

  if(!podcasts)
    init_podcasts();

  new_podcast = malloc(sizeof(podcast_data));
  printf("title: %s\n", feed->title);
  
  new_podcast->feed = url;
  new_podcast->title = strdup(feed->title);
  new_podcast->episodes = NULL;

  podcasts->feeds = eina_list_append(podcasts->feeds, new_podcast);

  item = feed->item;
  while(item){
    episode_data *new_episode = malloc(sizeof(episode_data));
    song_data       *new_song = malloc(sizeof(song_data));
    fprintf (stdout, "\tpubDate: %s\n", item->pubDate);
    fprintf (stdout, "\tauthor: %s\n", item->author);
    fprintf (stdout, "\tenclosure: %s\n", item->enclosure);
    fprintf (stdout, "\tenclosure_url: %s\n", item->enclosure_url);

    item = item->next;
  }
  
  mrss_free(feed);
}

void add_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  char *url = "http://feeds.feedburner.com/bitsundso/audio?format=mp3";
  podcast_add(url);
}

void refresh_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  
}
void download_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
}


int podcast_win_show()
{
  Evas_Object *win, *bg, *list, *main_bx, *bt_bx, *add_bt, *refresh_bt, *download_bt;

  win = elm_win_add(NULL, "podcasts", ELM_WIN_BASIC);
  elm_win_title_set(win, "Podcasts");
  elm_win_autodel_set(win, 1);
  
   /* add a standard bg */
  bg = elm_bg_add(win);
  evas_object_size_hint_weight_set(bg, 1.0, 1.0);
  elm_win_resize_object_add(win, bg);
  evas_object_show(bg);

  /* add a box object - default is vertical. a box holds children in a row,
   * either horizontally or vertically. nothing more. */
  main_bx = elm_box_add(win);
  evas_object_size_hint_weight_set(main_bx, 1.0, 1.0);
  elm_win_resize_object_add(win, main_bx);
  evas_object_show(main_bx);

  list = elm_list_add(win);
  evas_object_size_hint_align_set(list, -1.0, -1.0);
  evas_object_size_hint_weight_set(list, 1.0, 1.0);
  elm_box_pack_end(main_bx, list);

  evas_object_show(list);

  bt_bx = elm_box_add(win);
  evas_object_size_hint_weight_set(bt_bx, 1.0, 0.0);
  elm_box_pack_end(main_bx, bt_bx);
  elm_box_horizontal_set(bt_bx, 1);
  evas_object_show(bt_bx);

  add_bt = elm_button_add(win);
  refresh_bt = elm_button_add(win);
  download_bt = elm_button_add(win);

  elm_button_label_set(add_bt, "Add");
  elm_button_label_set(refresh_bt, "Refresh");
  elm_button_label_set(download_bt, "Download");

  elm_box_pack_end(bt_bx, add_bt);
  elm_box_pack_end(bt_bx, refresh_bt);
  elm_box_pack_end(bt_bx, download_bt);

  evas_object_smart_callback_add(add_bt, "clicked", add_bt_cb, NULL);
  evas_object_smart_callback_add(refresh_bt, "clicked", refresh_bt_cb, NULL);
  evas_object_smart_callback_add(download_bt, "clicked", download_bt_cb, NULL);
  

  evas_object_show(add_bt);
  evas_object_show(refresh_bt);
  evas_object_show(download_bt);

  evas_object_resize(win, 480, 640);

  evas_object_show(win);
}
