#include "pwm_hw.hpp"
#include "pwm_sw.hpp"
#include <iostream>

using emblocks::components::pwm::tl::PWM;

constexpr auto printTuple = [](auto &&...args) {
  const size_t sz = sizeof...(args);
  size_t k = 0;

  ((std::cout << std::forward<decltype(args)>(args)
              << (++k != sz ? ", " : "\n")),
   ...);
};

int main() {
  PWM<PWM_HW> hwPwm0;
  PWM<PWM_HW, 1> hwPwm1;
  PWM<PWM_SW, 2> swPwm(400, 50);

  hwPwm0.set(1000, 50);

  std::apply(printTuple, hwPwm0());
  std::apply(printTuple, hwPwm1());
  std::apply(printTuple, swPwm());

  return 0;
}
