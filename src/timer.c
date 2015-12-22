#include <pebble.h>
#include "timer.h"

static int s_duration1 = 0;
static int s_duration2 = 0;
static int s_duration3 = 0;
static int s_selectedDuration = 0;
static int s_currentTimer = 0;
static int s_setCount = 0;

static AppTimer *s_timer;
static bool s_timerActive = false;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_bold_subset_49;
static GFont s_res_roboto_condensed_21;
static TextLayer *s_time = NULL;
static TextLayer *s_countdown;
static TextLayer *s_countup;
static TextLayer *s_set;
static BitmapLayer *s_menubar;
static TextLayer *s_restart1;
static TextLayer *s_restart2;
static TextLayer *s_restart3;

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
  
  // s_menubar
  s_menubar = bitmap_layer_create(GRect(112, 0, 32, 168));
  bitmap_layer_set_background_color(s_menubar, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_menubar);
  
  // s_restart1
  s_restart1 = text_layer_create(GRect(108, 15, 35, 21));
  text_layer_set_background_color(s_restart1, GColorClear);
  text_layer_set_text_color(s_restart1, GColorWhite);
  text_layer_set_text(s_restart1, "1");
  text_layer_set_text_alignment(s_restart1, GTextAlignmentRight);
  text_layer_set_font(s_restart1, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_restart1);
  
  // s_restart2
  s_restart2 = text_layer_create(GRect(108, 70, 35, 21));
  text_layer_set_background_color(s_restart2, GColorClear);
  text_layer_set_text_color(s_restart2, GColorWhite);
  text_layer_set_text(s_restart2, "2");
  text_layer_set_text_alignment(s_restart2, GTextAlignmentRight);
  text_layer_set_font(s_restart2, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_restart2);
  
  // s_restart3
  s_restart3 = text_layer_create(GRect(108, 129, 35, 21));
  text_layer_set_background_color(s_restart3, GColorClear);
  text_layer_set_text_color(s_restart3, GColorWhite);
  text_layer_set_text(s_restart3, "3");
  text_layer_set_text_alignment(s_restart3, GTextAlignmentRight);
  text_layer_set_font(s_restart3, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_restart3);
  
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_time);
  text_layer_destroy(s_countdown);
  text_layer_destroy(s_countup);
  text_layer_destroy(s_set);
  bitmap_layer_destroy(s_menubar);
  text_layer_destroy(s_restart1);
  text_layer_destroy(s_restart2);
  text_layer_destroy(s_restart3);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  app_timer_cancel(s_timer);
  text_layer_set_background_color(s_time, GColorClear);
  text_layer_set_text_color(s_time, GColorWhite);
  
  destroy_ui();
  s_time = NULL;
  s_timerActive = false;
}

static void setHiddenRestarts(bool hide) {
  layer_set_hidden((Layer *)s_restart1, hide);
  layer_set_hidden((Layer *)s_restart2, hide);
  layer_set_hidden((Layer *)s_restart3, hide);
  layer_set_hidden((Layer *)s_menubar, hide);
}

static void printInt(TextLayer *layer, int value, char *buffer) {
  snprintf(buffer, 4, "%d", value);
  text_layer_set_text(layer, buffer);
}

static void updateMenu(int time) {
  s_duration1 = time;
  s_duration2 = time + 15; 
  s_duration3 = time + 30; 
  if(s_duration3<100) {
    layer_set_frame((Layer *)s_menubar, GRect(120, 0, 24, 168));
  } else {
    layer_set_frame((Layer *)s_menubar, GRect(112, 0, 32, 168));
  }
  static char b1[4];
  static char b2[4];
  static char b3[4];
  printInt(s_restart1, s_duration1, b1);
  printInt(s_restart2, s_duration2, b2);
  printInt(s_restart3, s_duration3, b3);
  
  setHiddenRestarts(false);
}

static void updateSets() {
  static char bSet[30];
  s_setCount++;
  snprintf(bSet, 30, "Set: %d", s_setCount);
  text_layer_set_text(s_set, bSet);
}


void timerTick(void *data) {
  s_timer = app_timer_register(500, timerTick, NULL);
  s_currentTimer++;
  if(s_currentTimer%2 == 0) {
    static char bUp[4];
    static char bDown[4];
    static int elapsed = 0;
    static int countdown = 0;
    
    elapsed = s_currentTimer/2;
    countdown = s_selectedDuration - elapsed;
    if(countdown > 0) {
      printInt(s_countup, elapsed, bUp);
      printInt(s_countdown, countdown, bDown);
    } else {
      printInt(s_countup, elapsed - s_selectedDuration, bUp);
    }
    
    if(countdown == 10) {
      window_set_background_color(s_window, GColorRed);
      vibes_double_pulse();
    } else if(countdown == 3) {
      vibes_long_pulse();
    } else if(countdown == 2 || countdown == 1) {
      vibes_short_pulse();
    } else if(countdown == 0) {
      window_set_background_color(s_window, GColorWhite);
      vibes_long_pulse();
      s_timerActive = false;
      updateMenu(s_selectedDuration);
      text_layer_set_text(s_countdown, "");
      text_layer_set_text(s_countup, "");
      updateSets();
    }
  }
  if(s_currentTimer == s_selectedDuration) {
    window_set_background_color(s_window, GColorOrange);
    vibes_double_pulse();
  }
}

void startTimer(int duration) {
  if(s_timerActive)
    return;
  
  s_timerActive = true;
  
  app_timer_cancel(s_timer);
  s_currentTimer = -1;
  s_selectedDuration = duration;
  window_set_background_color(s_window, GColorGreen);
  setHiddenRestarts(true);
  timerTick(NULL);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  startTimer(s_duration1);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  startTimer(s_duration2);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  startTimer(s_duration3);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static char *s_timeBuf;
void timer_update_time(char *value) {
  if(s_time == NULL)
    s_timeBuf = value;
  else
    text_layer_set_text(s_time, value);
}

void show_timer(int duration) {
  initialise_ui();
  window_set_click_config_provider(s_window, click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  timer_update_time(s_timeBuf);
  s_setCount = 0;
  updateSets();
  startTimer(duration);
}

//void hide_timer(void) {
  //window_stack_remove(s_window, true);
//}
