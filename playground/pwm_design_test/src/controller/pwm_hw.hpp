#ifndef _SRC_CONTROLLER_PWM_HW_HPP_
#define _SRC_CONTROLLER_PWM_HW_HPP_

#include <pwm.hpp>

using emblocks::components::pwm::tl::PWM;

class PWM_HW : public PWM<PWM_HW> {
public:
  void init() {
    // implementation, use of HAL driver, etc.
  }

  void deinit() {}

  void run() {}

  void stop() {}

  void set() {
    // freq & duty set in a base class, make use of:
    // this->frequency
    // this->duty
  }
};

#endif /* _SRC_CONTROLLER_PWM_HW_HPP_ */