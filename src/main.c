#include <pebble.h>
#include "main.h"
#include "timer.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_condensed_21;
static TextLayer *s_time;
static BitmapLayer *s_menubar;
static TextLayer *s_start1;
static TextLayer *s_start2;
static TextLayer *s_start3;
static TextLayer *s_set;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // s_time
  s_time = text_layer_create(GRect(0, 0, 144, 25));
  text_layer_set_background_color(s_time, GColorClear);
  text_layer_set_text_color(s_time, GColorWhite);
  text_layer_set_text(s_time, "12:34");
  text_layer_set_text_alignment(s_time, GTextAlignmentCenter);
  text_layer_set_font(s_time, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_time);
  
  // s_menubar
  s_menubar = bitmap_layer_create(GRect(109, 0, 35, 168));
  bitmap_layer_set_background_color(s_menubar, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_menubar);
  
  // s_start1
  s_start1 = text_layer_create(GRect(108, 15, 35, 21));
  text_layer_set_background_color(s_start1, GColorClear);
  text_layer_set_text(s_start1, "45");
  text_layer_set_text_alignment(s_start1, GTextAlignmentRight);
  text_layer_set_font(s_start1, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_start1);
  
  // s_start2
  s_start2 = text_layer_create(GRect(108, 70, 35, 21));
  text_layer_set_background_color(s_start2, GColorClear);
  text_layer_set_text(s_start2, "60");
  text_layer_set_text_alignment(s_start2, GTextAlignmentRight);
  text_layer_set_font(s_start2, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_start2);
  
  // s_start3
  s_start3 = text_layer_create(GRect(108, 129, 35, 21));
  text_layer_set_background_color(s_start3, GColorClear);
  text_layer_set_text(s_start3, "75");
  text_layer_set_text_alignment(s_start3, GTextAlignmentRight);
  text_layer_set_font(s_start3, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_start3);
  
  // s_set
  s_set = text_layer_create(GRect(0, 143, 144, 25));
  text_layer_set_background_color(s_set, GColorClear);
  text_layer_set_text_color(s_set, GColorWhite);
  text_layer_set_text(s_set, "Set: 0");
  text_layer_set_font(s_set, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_set);
  
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_time);
  bitmap_layer_destroy(s_menubar);
  text_layer_destroy(s_start1);
  text_layer_destroy(s_start2);
  text_layer_destroy(s_start3);
  text_layer_destroy(s_set);
}
// END AUTO-GENERATED UI CODE

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  show_timer(45);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  show_timer(60);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  show_timer(75);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}


static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void tickhandler(struct tm *tick_time, TimeUnits units_changed) {
  static char timeDisplay[10];
  clock_copy_time_string(timeDisplay, 10);
  // Dodgy assumption - always has AM/PM
  int index = strlen(timeDisplay);
  timeDisplay[index - 2] = 0;
  text_layer_set_text(s_time, timeDisplay);
  timer_update_time(timeDisplay);
}

void show_main(void) {
  initialise_ui();
  
  window_set_click_config_provider(s_window, click_config_provider);
  tick_timer_service_subscribe(MINUTE_UNIT, tickhandler);
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main(void) {
  window_stack_remove(s_window, true);
}
