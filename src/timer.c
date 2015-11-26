#include <pebble.h>
#include "timer.h"

static int s_startingDuration = 0;
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_bold_subset_49;
static GFont s_res_roboto_condensed_21;
static TextLayer *s_countdown;
static TextLayer *s_time;
static TextLayer *s_countup;
static TextLayer *s_set;
static TextLayer *s_restart1;
static TextLayer *s_restart2;
static TextLayer *s_restart3;
static BitmapLayer *s_tobzhaxx;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_roboto_bold_subset_49 = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // s_countdown
  s_countdown = text_layer_create(GRect(20, 40, 100, 49));
  text_layer_set_background_color(s_countdown, GColorClear);
  text_layer_set_text(s_countdown, "23");
  text_layer_set_text_alignment(s_countdown, GTextAlignmentCenter);
  text_layer_set_font(s_countdown, s_res_roboto_bold_subset_49);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_countdown);
  
  // s_time
  s_time = text_layer_create(GRect(0, 0, 144, 25));
  text_layer_set_text(s_time, "12:34");
  text_layer_set_text_alignment(s_time, GTextAlignmentCenter);
  text_layer_set_font(s_time, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_time);
  
  // s_countup
  s_countup = text_layer_create(GRect(20, 90, 100, 23));
  text_layer_set_background_color(s_countup, GColorClear);
  text_layer_set_text(s_countup, "37");
  text_layer_set_text_alignment(s_countup, GTextAlignmentCenter);
  text_layer_set_font(s_countup, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_countup);
  
  // s_set
  s_set = text_layer_create(GRect(0, 143, 144, 25));
  text_layer_set_text(s_set, "Sets: 1");
  text_layer_set_font(s_set, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_set);
  
  // s_restart1
  s_restart1 = text_layer_create(GRect(108, 15, 35, 21));
  text_layer_set_background_color(s_restart1, GColorClear);
  text_layer_set_text(s_restart1, "60");
  text_layer_set_text_alignment(s_restart1, GTextAlignmentRight);
  text_layer_set_font(s_restart1, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_restart1);
  
  // s_restart2
  s_restart2 = text_layer_create(GRect(108, 70, 35, 21));
  text_layer_set_background_color(s_restart2, GColorClear);
  text_layer_set_text(s_restart2, "75");
  text_layer_set_text_alignment(s_restart2, GTextAlignmentRight);
  text_layer_set_font(s_restart2, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_restart2);
  
  // s_restart3
  s_restart3 = text_layer_create(GRect(108, 129, 35, 21));
  text_layer_set_background_color(s_restart3, GColorClear);
  text_layer_set_text(s_restart3, "90");
  text_layer_set_text_alignment(s_restart3, GTextAlignmentRight);
  text_layer_set_font(s_restart3, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_restart3);
  
  // s_tobzhaxx
  s_tobzhaxx = bitmap_layer_create(GRect(0, 35, 20, 2));
  bitmap_layer_set_background_color(s_tobzhaxx, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_tobzhaxx);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_countdown);
  text_layer_destroy(s_time);
  text_layer_destroy(s_countup);
  text_layer_destroy(s_set);
  text_layer_destroy(s_restart1);
  text_layer_destroy(s_restart2);
  text_layer_destroy(s_restart3);
  bitmap_layer_destroy(s_tobzhaxx);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void setHiddenRestarts(bool hide) {
  layer_set_hidden((Layer *)s_restart1, hide);
  layer_set_hidden((Layer *)s_restart2, hide);
  layer_set_hidden((Layer *)s_restart3, hide);
}

void show_timer(int duration) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  s_startingDuration = duration;
  text_layer_set_text(s_countdown, "123");
  text_layer_set_text(s_countup, "@@");
  window_set_background_color(s_window, GColorGreen);
  setHiddenRestarts(true);
}

void hide_timer(void) {
  window_stack_remove(s_window, true);
}
