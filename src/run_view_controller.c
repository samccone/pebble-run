#include "run_view_controller.h"

SimpleMenuSection sections[1];
SimpleMenuItem sectionItems[3];  
void setup_run_view(RunViewController *self);
static RunViewController *activeController;

RunViewController* new_run_view_controller(void) {
  RunViewController* self = malloc(sizeof(RunViewController));
  
  setup_run_view(self);
  activeController = self;

  return self;
}

void destroy_run_view(RunViewController* self) {
  if (activeController == 0) {
    return;
  }
  
  simple_menu_layer_destroy(self->menu_layer);
  layer_destroy(self->menu_background_layer);
  
  text_layer_destroy(self->split_text_layer);
  text_layer_destroy(self->time_text_layer);
  text_layer_destroy(self->distance_text_layer);

  window_destroy(self->window);
  window_stack_remove(self->window, false);
  activeController = 0;
  
  free(self);
}

void on_menu_select() {
  
}

void set_background_frame(Layer *layer, GContext *ctx) {
  GRect bounding_frame = layer_get_frame(window_get_root_layer(activeController->window));  
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, bounding_frame, 0, GCornerNone);
}

void return_home_prompt() {
  if (activeController == 0) {
    return;
  }
  
  Layer *window_layer = window_get_root_layer(activeController->window);
  GRect bounding_frame = layer_get_frame(window_layer);
                                          
  activeController->menu_background_layer = layer_create(bounding_frame);
  
  layer_set_update_proc(activeController->menu_background_layer, set_background_frame);

  sectionItems[0] = (SimpleMenuItem){.title="Run Home"};
  sectionItems[1] = (SimpleMenuItem){.title="End Run"};
  sectionItems[2] = (SimpleMenuItem){.title="Cancel"};
  sections[0] = (SimpleMenuSection) {.items=sectionItems, .num_items=3};
  
  activeController->menu_layer = simple_menu_layer_create(
    bounding_frame, 
    activeController->window, sections, 1, on_menu_select);
  
  layer_add_child(window_layer, activeController->menu_background_layer);

  layer_add_child(window_layer, 
                  menu_layer_get_layer(simple_menu_layer_get_menu_layer(activeController->menu_layer)));
}

void run_view_config_provider(Window *window) {
  window_single_click_subscribe(BUTTON_ID_SELECT, return_home_prompt);
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