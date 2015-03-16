#pragma once
#include "run_menu_controller.h"
#include <pebble.h>
  
typedef struct {
  Window *window;
  RunMenuController *run_menu_controller;
  TextLayer *split_text_layer;
  TextLayer *time_text_layer;
  TextLayer *distance_text_layer;
} RunViewController;

RunViewController *new_run_view_controller();
void destroy_run_view(RunViewController* self);