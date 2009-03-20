#include "podcasts.h"
#include "playlist.h"



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

  evas_object_show(add_bt);
  evas_object_show(refresh_bt);
  evas_object_show(download_bt);

  evas_object_resize(win, 480, 640);

  evas_object_show(win);
}
