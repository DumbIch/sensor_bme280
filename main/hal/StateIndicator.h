#ifndef STATEINDICATOR_H_
#define STATEINDICATOR_H_

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

namespace HAL {

  class StateIndicator {
    public:
      static StateIndicator& getInstance();
      void prepare(gpio_num_t pin);
      void on(uint32_t time_ms);
      void off(uint32_t time_ms);
    protected:
    private:
      gpio_num_t _pin;
      StateIndicator(){};
      StateIndicator(const StateIndicator& indicator) = delete;
      const StateIndicator& operator=(const StateIndicator& indicator) = delete;
  };
      
  StateIndicator& StateIndicator::getInstance() {
    static StateIndicator instance;
    instance._pin = GPIO_NUM_NC;
    return instance;
  }
  void StateIndicator::prepare(gpio_num_t pin) {
    if (pin != GPIO_NUM_NC) {
      _pin = pin;
      gpio_set_direction(_pin, GPIO_MODE_OUTPUT);
      gpio_set_pull_mode(_pin, GPIO_FLOATING);
    }        
  }
  void StateIndicator::on(uint32_t time_ms) {
    if (_pin != GPIO_NUM_NC) {
      gpio_set_level(_pin, 0);
      vTaskDelay(pdMS_TO_TICKS(time_ms));
    }        
  }
  void StateIndicator::off(uint32_t time_ms) {
    if (_pin != GPIO_NUM_NC) {
      gpio_set_level(_pin, 1);
      vTaskDelay(pdMS_TO_TICKS(time_ms));
    }        
  }
  typedef struct {
    char* name;
    uint32_t timeLedOn;
    uint32_t timeLedOff;
    StateIndicator& indicator;
  } state_indicator_task_params_t;
  void switchStateIndicator(void* pvParams) {
    state_indicator_task_params_t* params = (state_indicator_task_params_t*) pvParams;
    while (true) {
      params->indicator.on(params->timeLedOn);
      params->indicator.off(params->timeLedOff);
    }  
  }

}

#endif
