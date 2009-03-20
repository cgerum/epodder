#include <Elementary.h>
#include <Emotion.h>
#include <Evas.h>

#include <stdlib.h>
#include <stdio.h>

#include "playlist.h"
#include "podcasts.h"
#include "config_files.h"

static void
destroy_main_window(void *data, Evas_Object *obj, void *event_info)
{
  /* called when my_win_main is requested to be deleted */
  playlist_serialize();
  elm_exit(); /* exit the program's main loop that runs in elm_run() */
}


typedef struct _Pginfo Pginfo;

struct _Pginfo
{
   Evas_Object *pager, *pg1, *pg2, *pg3;
};


void pause_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  playlist_pause();
}

void stop_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  playlist_stop();
}

void play_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  playlist_play();
}

void pl_add_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  file_dlg_show();
}

void pl_rem_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
  playlist_remove_selected();
}

static void init_main_window()
{
  Evas_Object *win, *bg, *pg, *player_bx, *main_bx, *play_bt, *pause_bt, *stop_bt;
  Evas_Object *time_lb, *playlist, *plctrl_bx;
  Evas_Object *pl_add_bt, *pl_rem_bt;
  static Pginfo player;
   

  win = elm_win_add(NULL, "main", ELM_WIN_BASIC);

  elm_win_title_set(win, "EPodder");

  evas_object_smart_callback_add(win, "delete-request", destroy_main_window, NULL);
   
  bg = elm_bg_add(win);

  evas_object_size_hint_weight_set(bg, 1.0, 1.0);
  
  elm_win_resize_object_add(win, bg);
   
  evas_object_show(bg);

  main_bx = elm_box_add(win);
  evas_object_size_hint_weight_set(main_bx, 1.0, 1.0);
  elm_win_resize_object_add(win, main_bx);
  evas_object_show(main_bx);


  player_bx = elm_box_add(win);
  elm_box_horizontal_set(player_bx, 1);
  elm_box_pack_end(main_bx, player_bx);
  evas_object_show(player_bx);


  play_bt = elm_button_add(win);
  stop_bt = elm_button_add(win);
  pause_bt = elm_button_add(win);

  elm_button_label_set(play_bt, "Play");
  elm_button_label_set(stop_bt, "Stop");
  elm_button_label_set(pause_bt, "Pause");

  elm_box_pack_end(player_bx, play_bt);
  elm_box_pack_end(player_bx, pause_bt);
  elm_box_pack_end(player_bx, stop_bt);

  evas_object_smart_callback_add(play_bt, "clicked", play_bt_cb, NULL);
  evas_object_smart_callback_add(pause_bt, "clicked", pause_bt_cb, NULL);
  evas_object_smart_callback_add(stop_bt, "clicked", stop_bt_cb, NULL);
  

  evas_object_show(play_bt);
  evas_object_show(stop_bt);
  evas_object_show(pause_bt);
  
  time_lb = elm_label_add(win);
  
  elm_label_label_set(time_lb, "--:--:--/--:--:--");
  
  elm_box_pack_end(player_bx, time_lb);

  evas_object_show(time_lb);

  playlist = playlist_add(win);
  elm_box_pack_end(main_bx, playlist);
  evas_object_show(playlist);  

  plctrl_bx = elm_box_add(win);
  elm_box_horizontal_set(plctrl_bx, 1);
  elm_box_pack_end(main_bx, plctrl_bx);
  evas_object_show(plctrl_bx);

  pl_add_bt = elm_button_add(win);
  pl_rem_bt = elm_button_add(win);

  elm_button_label_set(pl_add_bt, "Add");
  elm_button_label_set(pl_rem_bt, "Remove");

  elm_box_pack_end(plctrl_bx, pl_add_bt);
  elm_box_pack_end(plctrl_bx, pl_rem_bt);

  evas_object_smart_callback_add(pl_add_bt, "clicked", pl_add_bt_cb, NULL);
  evas_object_smart_callback_add(pl_rem_bt, "clicked", pl_rem_bt_cb, NULL);

  evas_object_show(pl_add_bt);
  evas_object_show(pl_rem_bt);

  evas_object_resize(win, 480, 640);
  evas_object_show(win); 

  podcast_win_show();
}



/* this is your elementary main function - it MUSt be called IMMEDIATELY
 * after elm_init() and MUSt be passed argc and argv, and MUST be called
 * elm_main and not be static - must be a visible symbol with EAPI infront */
EAPI int
elm_main(int argc, char **argv)
{
  init_files();
   /* put ere any init specific to this app like parsing args etc. */
   init_main_window(); /* create main window */
   elm_run(); /* and run the program now  and handle all events etc. */
   /* if the mainloop that elm_run() runs exist - we exit the app */
   elm_shutdown(); /* clean up and shut down */
   /* exit code */
   return 0;
}
/* all emeentary apps should use this. but it right after elm_main() */
ELM_MAIN()
