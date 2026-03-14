#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "./hal/StateIndicator.h"

HAL::StateIndicator& stateIndicator = HAL::StateIndicator::getInstance();

gpio_num_t built_led_pin = (gpio_num_t)8;
HAL::state_indicator_task_params_t stateIndicatorParams { 
  "STATE_INDICATOR", 
  3000, 
  3000,
  stateIndicator
 };


extern "C" void app_main() {
  stateIndicatorParams.indicator.prepare(built_led_pin);
  xTaskCreate(&HAL::switchStateIndicator, stateIndicatorParams.name, 512, &stateIndicatorParams, tskIDLE_PRIORITY+1, NULL);
}
