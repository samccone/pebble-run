#include <pebble.h>
#include <run_plan_view_controller.h>
#include "run_view_controller.h"

RunPlanViewController *runPlanController;
RunViewController *runViewController;

void handle_deinit(void) {
  destroy_run_plan(runPlanController);
  destroy_run_view(runViewController);
}

void onSubmitRunDistance(int distance) {
  runViewController = new_run_view_controller();
  destroy_run_plan(runPlanController);
  window_stack_push(runViewController->window, true);
}

int main(void) {
  runPlanController = newRunPlanViewController(onSubmitRunDistance);
  
  window_stack_push(runPlanController->window, true);
  app_event_loop();
  handle_deinit();
}
