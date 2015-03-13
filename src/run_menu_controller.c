#include <pebble.h>
#include "run_menu_controller.h"

static RunMenuController* active_controller;
SimpleMenuSection sections[1];
SimpleMenuItem sectionItems[3];  

void show_menu_prompt();

RunMenuController* new_run_menu_controller() {
  //singleton pattern enforement 
  if (active_controller) {
    window_stack_push(active_controller->window, true);
    return active_controller;
  }
  
  RunMenuController* self = malloc(sizeof(RunMenuController));
  self->window = window_create();
  active_controller = self;
  show_menu_prompt();
  
  window_stack_push(self->window, true);
  return self;
}

void destroy_run_menu_controller(RunMenuController* self) {
  if (active_controller == 0) {
    return;
  }
  
  simple_menu_layer_destroy(active_controller->menu);
  window_stack_remove(self->window, false);
  window_destroy(self->window);  

  active_controller = 0;
  
  free(self);
}

void run_home_select(int index, void* context) {
  destroy_run_menu_controller(active_controller);  
}

void end_run(int index, void* context) {
  destroy_run_menu_controller(active_controller);
  window_stack_pop_all(true);  
}

void cancel_menu(int index, void* context) {
  destroy_run_menu_controller(active_controller);
}

void on_menu_select() {
  //NOOP
}

void show_menu_prompt() {
  if (active_controller == 0) {
    return;
  }
  
  Layer *window_layer = window_get_root_layer(active_controller->window);
  GRect bounding_frame = layer_get_frame(window_layer);
                                          
  sectionItems[0] = (SimpleMenuItem){.title="Run Home", .callback=(SimpleMenuLayerSelectCallback) &run_home_select};
  sectionItems[1] = (SimpleMenuItem){.title="End Run", .callback=(SimpleMenuLayerSelectCallback) &end_run};
  sectionItems[2] = (SimpleMenuItem){.title="Cancel", .callback=(SimpleMenuLayerSelectCallback) &cancel_menu};
  sections[0] = (SimpleMenuSection) {.items=sectionItems, .num_items=3};
  
  active_controller->menu = simple_menu_layer_create(
    bounding_frame, 
    active_controller->window, sections, 1, on_menu_select);
  
  layer_add_child(window_layer, 
                  menu_layer_get_layer(simple_menu_layer_get_menu_layer(active_controller->menu)));
}