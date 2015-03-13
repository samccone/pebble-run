#include "run_view_controller.h"

void setup_run_view(RunViewController *self);
static RunViewController *activeController;

RunViewController* new_run_view_controller(void) {
  RunViewController* self = malloc(sizeof(RunViewController));
  
  setup_run_view(self);
  activeController = self;
  
  return self;
}

void show_run_menu() {
  if (activeController == 0) {
    return;
  }
  
  activeController->run_menu_controller = new_run_menu_controller();
}

void run_view_config_provider(Window *window) {
  window_single_click_subscribe(BUTTON_ID_SELECT, show_run_menu);
}

void destroy_run_view(RunViewController* self) {
  if (activeController == 0) {
    return;
  }
  
  text_layer_destroy(self->split_text_layer);
  text_layer_destroy(self->time_text_layer);
  text_layer_destroy(self->distance_text_layer);
  
  destroy_run_menu_controller(self->run_menu_controller);
  
  window_destroy(self->window);
  window_stack_remove(self->window, false);
  activeController = 0;
  
  free(self);
}

void setup_run_view(RunViewController *self) {
  self->window = window_create();

  Layer *window_layer = window_get_root_layer(self->window);
  GRect window_bounds = layer_get_frame(window_layer);

    
  self->distance_text_layer = text_layer_create(GRect(0, 0, window_bounds.size.w, 44));
  text_layer_set_font(self->distance_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(self->distance_text_layer, GTextAlignmentCenter);
  text_layer_set_text(self->distance_text_layer, "33.2 mi");
 
  self->time_text_layer = text_layer_create(GRect(0, 60, window_bounds.size.w, 44));
  text_layer_set_font(self->time_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(self->time_text_layer, GTextAlignmentCenter);
  text_layer_set_text(self->time_text_layer, "11:11");

  self->split_text_layer = text_layer_create(GRect(0, 119, window_bounds.size.w, 44));
  text_layer_set_font(self->split_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(self->split_text_layer, GTextAlignmentCenter);
  text_layer_set_text(self->split_text_layer, "6:43 / mi");

  layer_add_child(window_layer, text_layer_get_layer(self->split_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(self->time_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(self->distance_text_layer));

  window_set_click_config_provider(self->window, (ClickConfigProvider) run_view_config_provider);  
}