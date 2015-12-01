#include "wtfpm.h"
#include <pebble.h>

#define RESETTED 1
#define RUNNING 2
#define PAUSED 3
static int state = RESETTED;
static int wtf_count = 0;
static int seconds = 0;

//forward declaration
//void click_config_provider(Window *window);
void click_config_provider(void *context);
void handle_reset_click(ClickRecognizerRef recognizer, void *context);
void handle_start_pause_click(ClickRecognizerRef recognizer, void *context);
void handle_wtf_click(ClickRecognizerRef recognizer, void *context);
void handle_wtf_click_minus(ClickRecognizerRef recognizer, void *context);
void handle_ticks(struct tm *tick_time, TimeUnits units_changed);
void update_time(void);
void update_wtfpm(void);

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_icon_play;
static GBitmap *s_res_icon_pause;
static GBitmap *s_res_icon_stop;
static GBitmap *s_res_icon_cloud;
static GFont s_res_gothic_28_bold;
static ActionBarLayer *s_actionbarlayer;
static TextLayer *s_time;
static TextLayer *s_label_time;
static TextLayer *s_label_wtf;
static TextLayer *s_wtf;
static TextLayer *s_label_wtfpm;
static TextLayer *s_wtfpm;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_icon_play = gbitmap_create_with_resource(RESOURCE_ID_ICON_PLAY);
  s_res_icon_pause = gbitmap_create_with_resource(RESOURCE_ID_ICON_PAUSE);
  s_res_icon_stop = gbitmap_create_with_resource(RESOURCE_ID_ICON_STOP);
  s_res_icon_cloud = gbitmap_create_with_resource(RESOURCE_ID_ICON_CLOUD);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_actionbarlayer
  s_actionbarlayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer, GColorWhite);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_UP, s_res_icon_play);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_icon_stop);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_DOWN, s_res_icon_cloud);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer);
  
  // s_time
  s_time = text_layer_create(GRect(0, 13, 110, 30));
  text_layer_set_background_color(s_time, GColorClear);
  text_layer_set_text_color(s_time, GColorWhite);
  text_layer_set_text(s_time, "0:00");
  text_layer_set_text_alignment(s_time, GTextAlignmentRight);
  text_layer_set_font(s_time, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_time);
  
  // s_label_time
  s_label_time = text_layer_create(GRect(0, 3, 110, 16));
  text_layer_set_background_color(s_label_time, GColorClear);
  text_layer_set_text_color(s_label_time, GColorWhite);
  text_layer_set_text(s_label_time, "Time");
  text_layer_set_text_alignment(s_label_time, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_label_time);
  
  // s_label_wtf
  s_label_wtf = text_layer_create(GRect(0, 102, 110, 16));
  text_layer_set_background_color(s_label_wtf, GColorClear);
  text_layer_set_text_color(s_label_wtf, GColorWhite);
  text_layer_set_text(s_label_wtf, "WTF count");
  text_layer_set_text_alignment(s_label_wtf, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_label_wtf);
  
  // s_wtf
  s_wtf = text_layer_create(GRect(0, 112, 110, 30));
  text_layer_set_background_color(s_wtf, GColorClear);
  text_layer_set_text_color(s_wtf, GColorWhite);
  text_layer_set_text(s_wtf, "0");
  text_layer_set_text_alignment(s_wtf, GTextAlignmentRight);
  text_layer_set_font(s_wtf, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_wtf);
  
  // s_label_wtfpm
  s_label_wtfpm = text_layer_create(GRect(0, 52, 110, 16));
  text_layer_set_background_color(s_label_wtfpm, GColorClear);
  text_layer_set_text_color(s_label_wtfpm, GColorWhite);
  text_layer_set_text(s_label_wtfpm, "WTF/Minute");
  text_layer_set_text_alignment(s_label_wtfpm, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_label_wtfpm);
  
  // s_wtfpm
  s_wtfpm = text_layer_create(GRect(0, 62, 110, 49));
  text_layer_set_background_color(s_wtfpm, GColorClear);
  text_layer_set_text_color(s_wtfpm, GColorWhite);
  text_layer_set_text(s_wtfpm, "0");
  text_layer_set_text_alignment(s_wtfpm, GTextAlignmentRight);
  text_layer_set_font(s_wtfpm, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_wtfpm);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer);
  text_layer_destroy(s_time);
  text_layer_destroy(s_label_time);
  text_layer_destroy(s_label_wtf);
  text_layer_destroy(s_wtf);
  text_layer_destroy(s_label_wtfpm);
  text_layer_destroy(s_wtfpm);
  gbitmap_destroy(s_res_icon_play);
  gbitmap_destroy(s_res_icon_pause);
  gbitmap_destroy(s_res_icon_stop);
  gbitmap_destroy(s_res_icon_cloud);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_wtfpm(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  action_bar_layer_set_click_config_provider(s_actionbarlayer, click_config_provider);
  action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_SELECT);
  action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_DOWN);
  window_stack_push(s_window, true);
}

void hide_wtfpm(void) {
  window_stack_remove(s_window, true);
}

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, handle_start_pause_click);
  window_single_click_subscribe(BUTTON_ID_SELECT, handle_reset_click);
  window_single_click_subscribe(BUTTON_ID_DOWN, handle_wtf_click);
  window_long_click_subscribe(BUTTON_ID_DOWN, 1000, handle_wtf_click_minus, NULL);
}

void handle_reset_click(ClickRecognizerRef recognizer, void *context) {
    state = RESETTED;
    wtf_count=0;
    seconds=0;
    text_layer_set_text(s_time, "0:00");    
    text_layer_set_text(s_wtfpm, "0");    
    text_layer_set_text(s_wtf, "0");
    action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_DOWN);
    action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_SELECT);    
}

void handle_start_pause_click(ClickRecognizerRef recognizer, void *context) {
  switch (state) {
    case RESETTED:
    case PAUSED:
      state = RUNNING; //resetted->running
      tick_timer_service_subscribe(SECOND_UNIT, handle_ticks);
      action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_UP, s_res_icon_pause);
      action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_SELECT);        
      action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_DOWN, s_res_icon_cloud);
      break;
    case RUNNING:
      state = PAUSED; //runnung->paused
      tick_timer_service_unsubscribe();
      action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_UP, s_res_icon_play);
      action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_icon_stop);
      action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_DOWN);
      break;
  }
}

void handle_wtf_click(ClickRecognizerRef recognizer, void *context) {
  static char counter[]="123456789";
  wtf_count++;
  snprintf(counter, sizeof(counter), "%d", wtf_count);
  text_layer_set_text(s_wtf, counter);    
}

void handle_wtf_click_minus(ClickRecognizerRef recognizer, void *context) {
  static char counter[]="123456789";
  wtf_count--;
  snprintf(counter, sizeof(counter), "%d", wtf_count);
  text_layer_set_text(s_wtf, counter);    
}

void handle_ticks(struct tm *tick_time, TimeUnits units_changed) {
  seconds++;
  update_time();
  update_wtfpm();
}

void update_wtfpm(void) {
  float f_wtfpm = wtf_count/(seconds/60.0)+0.5; //+0.5 for correct rounding
  static char wtfpm[]="123456789";
  snprintf(wtfpm, sizeof(wtfpm), "%d", (int)f_wtfpm);
  text_layer_set_text(s_wtfpm, wtfpm);  
}

void update_time(void) {
  static char time[]="123456789";
  snprintf(time, sizeof(time), "%d:%.2d", seconds/60, seconds%60);
  text_layer_set_text(s_time, time);
}