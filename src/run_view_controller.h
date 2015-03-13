#pragma once
#include <pebble.h>
  
typedef struct {
  Window *window;
  SimpleMenuLayer *menu_layer;
  Layer *menu_background_layer;
  TextLayer *split_text_layer;
  TextLayer *time_text_layer;
  TextLayer *distance_text_layer;
} RunViewController;

RunViewController *new_run_view_controller();
void destroy_run_view(RunViewController* self);