#include <pebble.h>
#include <run_plan_view_controller.h>

Window *distance_window;
Window *run_window;
RunPlanViewController* runPlanController;

void handle_deinit(void) {
  destroy_run_plan(runPlanController);
}

void show_distance_select(void) {  
}

void destroy_distance_select(void) {

}

void onSubmitRunDistance(int distance) {
  Window *run_window = window_create();  
  window_stack_push(run_window, true);
}

int main(void) {
  runPlanController = newRunPlanViewController(onSubmitRunDistance);
  
  window_stack_push(runPlanController->window, true);
  app_event_loop();
  handle_deinit();
}
