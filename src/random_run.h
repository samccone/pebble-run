void fill_top_rect(Layer *m, GContext *ctx);
void draw_top_rect();
void timer_tick(struct tm* tick_time, TimeUnits units_changed);

void in_received_handler(DictionaryIterator *iter, void *context);
void in_dropped_handler(AppMessageResult reason, void *context);

void set_time_display(Layer *window_layer);
void set_distance_display(Layer *window_layer);

void init();
void deinit();
