#pragma once
#include <pebble.h>
  
typedef struct {
  Window *window;
  int run_distance;
  TextLayer *distance_text_layer;
  TextLayer *distance_action_text_layer;
  TextLayer *distance_inc_text_layer;
  TextLayer *distance_dec_text_layer;
  Layer *distance_background_layer;
  char distance_str[3];
  void (*onSubmitRunDistance)(int);
} RunPlanViewController;

RunPlanViewController* newRunPlanViewController(void (*onSubmitRunDistance)(int));
void destroy_run_plan(RunPlanViewController* self);