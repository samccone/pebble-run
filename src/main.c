#include <pebble.h>

Window *distance_window;
TextLayer *distance_text_layer;
TextLayer *distance_inc_text_layer;
TextLayer *distance_dec_text_layer;

int run_distance = 1;
char *run_distance_str = "";

void handle_init(void) {
}


void handle_deinit(void) {
  text_layer_destroy(distance_text_layer);
  text_layer_destroy(distance_inc_text_layer);
  text_layer_destroy(distance_dec_text_layer);
  window_destroy(distance_window);
}

void update_distance_display(void) {
  snprintf(run_distance_str, 2, "%d", run_distance);
  
  text_layer_set_text(distance_text_layer, run_distance_str);   
  layer_mark_dirty(text_layer_get_layer(distance_text_layer));
}

void run_distance_inc(ClickRecognizerRef recognizer, void *context) {
  run_distance += 1;
  update_distance_display();
}

void run_distance_dec(ClickRecognizerRef recognizer, void *context) {
  if (run_distance > 1) {
    run_distance -= 1;
    update_distance_display();    
  }
}

void distance_config_provider(Window *window) {
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 600, run_distance_inc);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 600, run_distance_dec);  
}

void show_distance_select(void) {  
  distance_window = window_create();  
  window_stack_push(distance_window, true);
  
  Layer *distance_window_layer = window_get_root_layer(distance_window);

  GSize window_rect = layer_get_frame(distance_window_layer).size;

  distance_text_layer = text_layer_create(GRect(0, window_rect.h/2, window_rect.w, 20));
  
  text_layer_set_text_alignment(distance_text_layer, GTextAlignmentCenter);
  
  distance_inc_text_layer = text_layer_create(GRect(window_rect.w - 20, 0, 20, 20));
  text_layer_set_text(distance_inc_text_layer, "U");

  distance_dec_text_layer = text_layer_create(GRect(window_rect.w - 20, window_rect.h - 20, 20, 20));
  text_layer_set_text(distance_dec_text_layer, "D");
  
  layer_add_child(distance_window_layer, text_layer_get_layer(distance_text_layer));  
  layer_add_child(distance_window_layer, text_layer_get_layer(distance_inc_text_layer));
  layer_add_child(distance_window_layer, text_layer_get_layer(distance_dec_text_layer));
  
  update_distance_display();
    
  window_set_click_config_provider(distance_window, (ClickConfigProvider) distance_config_provider);
}

void destroy_distance_select(void) {

}

int main(void) {
  handle_init();
  show_distance_select();
  app_event_loop();
  handle_deinit();
}
