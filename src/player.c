#include <player.h>

#include <gst/gst.h>
#include <Ecore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GstElement *gst_player = NULL;


static void
handle_gst_message(GstMessage *message)
{
   switch (GST_MESSAGE_TYPE (message)) 
     {
        case GST_MESSAGE_ERROR: {
          GError *err;
          gchar *debug;
          gst_message_parse_error (message, &err, &debug);
          printf("Error code: %d, error message:  %s\n", err->code, err->message);
          //_mkk_send_event(MKK_EVENT_TYPE_ERROR, err->code, err->message);
          g_error_free (err);
          g_free (debug);
          break;
        }
        case GST_MESSAGE_EOS:
          printf("message EOS\n");
          //mokoko_media_play_next();
          break;
        case GST_MESSAGE_STATE_CHANGED: {
          GstState oldState;
          GstState newState;
          GstState pending;
          gst_message_parse_state_changed(message, &oldState, &newState, &pending);
          switch (newState)
            {
               case GST_STATE_VOID_PENDING:
               case GST_STATE_NULL:
               case GST_STATE_READY:
               case GST_STATE_PAUSED:
               case GST_STATE_PLAYING:
                 break;
            }
          break;
        }
        default:
          break;
     }
}

static GstElement *
_pipeline_instance()
{
   static GstElement *pipeline = NULL;
   if(!pipeline)
     pipeline = gst_element_factory_make ("playbin", "player");

   return pipeline;
}

static GstBus *
_bus_instance()
{
   static GstBus *bus = NULL;
   if(!bus)
     bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline_instance()));
   return bus;
}


static int
poll_gst(void *data)
{
   GstMessage *message;
   while( (message = gst_bus_poll(_bus_instance(), GST_MESSAGE_ANY, 0)) != 0)
     {
        handle_gst_message(message);
     }
   return TRUE;
}




void init_player(int *argc, char ***argv)
{

  if(!gst_player)
    {
      
      Ecore_Timer *poll_gst_timer;
      
      
      poll_gst_timer = ecore_timer_add(1.0, poll_gst, NULL);
      
      gst_init(argc, argv);
      gst_player = _pipeline_instance();
      
      printf("gstreamer playing\n");
    }
}


void player_file_load(char *file)
{
  char *uri = NULL;
  char *prefix = "file://";
  uri = malloc(strlen(prefix)+strlen(file)+1);

  sprintf(uri, "file://%s", file); 
	       

  printf("switching to file: %s", file);
 
  
  gst_element_set_state (gst_player, GST_STATE_NULL);
  g_object_set(G_OBJECT(gst_player), 
	       "uri",
	       uri,
	       NULL);
}

void player_state_set(int state)
{
  if(state == PLAYER_STATE_PLAYING){
    gst_element_set_state(gst_player, GST_STATE_PLAYING);
  }
  else if(state == PLAYER_STATE_STOP){
    gst_element_set_state (gst_player, GST_STATE_NULL);
  }
}

void player_position_set(double position)
{
  //TODO: Make it work
}

double player_position_get()
{
  return 0.0;
}
