#pragma once
#include <pebble.h>
  
typedef struct {
  Window *window;
  SimpleMenuLayer *menu;
}(RunMenuController);

RunMenuController* new_run_menu_controller();
void destroy_run_menu_controller(RunMenuController* self);