#include <pebble.h>

Window *distance_window;
TextLayer *distance_text_layer;
TextLayer *distance_action_text_layer;
TextLayer *distance_inc_text_layer;
TextLayer *distance_dec_text_layer;
Layer *distance_background_layer;

int run_distance = 1;
char str[3];

void handle_init(void) {
}

void handle_deinit(void) {
  text_layer_destroy(distance_text_layer);
  text_layer_destroy(distance_inc_text_layer);
  text_layer_destroy(distance_dec_text_layer);
  text_layer_destroy(distance_action_text_layer);
  layer_destroy(distance_background_layer);

  window_destroy(distance_window);
}

void update_distance_background(Layer *layer, GContext *ctx) {
  GRect bounding = layer_get_frame(layer);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(0, 0, bounding.size.w, bounding.size.h), 0, GCornerNone); 
}

void update_distance_display(void) {
  snprintf(str, 3 * sizeof(char), "%d", run_distance);
  
  text_layer_set_text(distance_text_layer, str);   
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

  distance_text_layer = text_layer_create(GRect(window_rect.w/2-30, window_rect.h/2 - 25, 50, 50));

  text_layer_set_font(distance_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));

  text_layer_set_text_alignment(distance_text_layer, GTextAlignmentCenter);
  
  distance_inc_text_layer = text_layer_create(GRect(window_rect.w - 20, 0, 28, 20));
  text_layer_set_font(distance_inc_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(distance_inc_text_layer, "+");
  text_layer_set_background_color(distance_inc_text_layer, GColorClear);
  text_layer_set_text_color(distance_inc_text_layer, GColorWhite);

  distance_dec_text_layer = text_layer_create(GRect(window_rect.w - 20, window_rect.h - 20, 28, 20));
  text_layer_set_font(distance_dec_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(distance_dec_text_layer, "-");
  text_layer_set_background_color(distance_dec_text_layer, GColorClear);
  text_layer_set_text_color(distance_dec_text_layer, GColorWhite);

  distance_action_text_layer = text_layer_create(GRect(window_rect.w - 23 , window_rect.h/2-10, 28, 20));
  text_layer_set_font(distance_action_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(distance_action_text_layer, "GO");
  text_layer_set_background_color(distance_action_text_layer, GColorClear);
  text_layer_set_text_color(distance_action_text_layer, GColorWhite);  

  distance_background_layer = layer_create(GRect(window_rect.w-30, 0, 30, window_rect.h));
  layer_set_update_proc(distance_background_layer, update_distance_background);
  layer_add_child(distance_window_layer, distance_background_layer);
  
  
  layer_add_child(distance_window_layer, text_layer_get_layer(distance_action_text_layer));  
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
