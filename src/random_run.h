static void fill_top_rect(Layer *m, GContext *ctx);
static void draw_top_rect();
static void timer_tick(struct tm* tick_time, TimeUnits units_changed);

static void in_received_handler(DictionaryIterator *iter, void *context);
static void in_dropped_handler(AppMessageResult reason, void *context);

static void set_time_display(Layer *window_layer);
static void set_distance_display(Layer *window_layer);

void format_time(uint16_t timer_time, bool showHours, char* str, int str_len);
