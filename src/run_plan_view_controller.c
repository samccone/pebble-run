#include <pebble.h>
#include "run_plan_view_controller.h"

void loadView(RunPlanViewController* self);
void configure_layers(RunPlanViewController* self);

static RunPlanViewController *activeController;

RunPlanViewController* newRunPlanViewController(void (*onSubmitRunDistance)(int)) {
  RunPlanViewController* self = malloc(sizeof(RunPlanViewController));
  self->onSubmitRunDistance = onSubmitRunDistance;
  self->run_distance=1;
  loadView(self);
  return self;  
}

void destroy_run_plan(RunPlanViewController *self) {
  if (activeController == 0) {
    return;
  }
  
  text_layer_destroy(self->distance_text_layer);
  text_layer_destroy(self->distance_inc_text_layer);
  text_layer_destroy(self->distance_dec_text_layer);
  text_layer_destroy(self->distance_action_text_layer);
  layer_destroy(self->distance_background_layer);
  window_stack_remove(self->window, false);
  window_destroy(self->window);  
  activeController = 0;
  free(self);
}

void loadView(RunPlanViewController* self) {
  self->window = window_create();
  activeController = self;
  configure_layers(self);
}

void update_distance_background(Layer *layer, GContext *ctx) {
  GRect bounding = layer_get_frame(layer);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(0, 0, bounding.size.w, bounding.size.h), 0, GCornerNone); 
}

void update_distance_display(RunPlanViewController* self) {
  snprintf(self->distance_str, 3 * sizeof(char), "%d", self->run_distance);
  
  text_layer_set_text(self->distance_text_layer, self->distance_str);   
  layer_mark_dirty(text_layer_get_layer(self->distance_text_layer));
}

void run_distance_inc_method(RunPlanViewController *self, ClickRecognizerRef recognizer, void *context) {
   self->run_distance += 1;
   update_distance_display(self);
}

void run_distance_inc(ClickRecognizerRef recognizer, void *context) {
  if (activeController == 0) {
    return;
  }
  run_distance_inc_method(activeController, recognizer, context);
}

void run_distance_dec_method(RunPlanViewController *self, ClickRecognizerRef recognizer, void *context) {
 if (self->run_distance > 1) {
   self->run_distance -= 1;
    update_distance_display(self);
 }
}

void submit_run_distance_method(RunPlanViewController* self, ClickRecognizerRef recognizer, void *context) {
  if (self->onSubmitRunDistance == 0) {
    return;
  }
  
  self->onSubmitRunDistance(self->run_distance);
}

void run_distance_dec(ClickRecognizerRef recognizer, void *context) {
  if (activeController == 0) {
    return;
  }
  run_distance_dec_method(activeController, recognizer, context);
}     

void submit_run_distance(ClickRecognizerRef recognizer, void *context) {
  if (activeController == 0) {
    return;
  }
  submit_run_distance_method(activeController, recognizer, context);
}

void distance_config_provider(Window *window) {
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 600, run_distance_inc);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 600, run_distance_dec);  
  window_single_click_subscribe(BUTTON_ID_SELECT, submit_run_distance);
}


void configure_layers(RunPlanViewController* self) {    
  Layer *distance_window_layer = window_get_root_layer(self->window);

  GSize window_rect = layer_get_frame(distance_window_layer).size;

  self->distance_text_layer = text_layer_create(GRect(window_rect.w/2-30, window_rect.h/2 - 25, 50, 50));

  text_layer_set_font(self->distance_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));

  text_layer_set_text_alignment(self->distance_text_layer, GTextAlignmentCenter);
  
  self->distance_inc_text_layer = text_layer_create(GRect(window_rect.w - 20, 0, 28, 20));
  text_layer_set_font(self->distance_inc_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(self->distance_inc_text_layer, "+");
  text_layer_set_background_color(self->distance_inc_text_layer, GColorClear);
  text_layer_set_text_color(self->distance_inc_text_layer, GColorWhite);

  self->distance_dec_text_layer = text_layer_create(GRect(window_rect.w - 20, window_rect.h - 20, 28, 20));
  text_layer_set_font(self->distance_dec_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(self->distance_dec_text_layer, "-");
  text_layer_set_background_color(self->distance_dec_text_layer, GColorClear);
  text_layer_set_text_color(self->distance_dec_text_layer, GColorWhite);

  self->distance_action_text_layer = text_layer_create(GRect(window_rect.w - 23 , window_rect.h/2-10, 28, 20));
  text_layer_set_font(self->distance_action_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(self->distance_action_text_layer, "GO");
  text_layer_set_background_color(self->distance_action_text_layer, GColorClear);
  text_layer_set_text_color(self->distance_action_text_layer, GColorWhite);  

  self->distance_background_layer = layer_create(GRect(window_rect.w-30, 0, 30, window_rect.h));
  layer_set_update_proc(self->distance_background_layer, update_distance_background);
  layer_add_child(distance_window_layer, self->distance_background_layer);
  
  
  layer_add_child(distance_window_layer, text_layer_get_layer(self->distance_action_text_layer));  
  layer_add_child(distance_window_layer, text_layer_get_layer(self->distance_text_layer));  
  layer_add_child(distance_window_layer, text_layer_get_layer(self->distance_inc_text_layer));
  layer_add_child(distance_window_layer, text_layer_get_layer(self->distance_dec_text_layer));
  
  update_distance_display(self);
    
  window_set_click_config_provider(self->window, (ClickConfigProvider) distance_config_provider);
}
