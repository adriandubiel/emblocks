#include <iostream>
#include "pwm_sw.hpp"
#include "pwm_hw.hpp"

using emblocks::components::pwm::tl::PWM;

constexpr auto printTuple = [](auto&&... args) {
    const size_t sz = sizeof ...(args);
    size_t k = 0;
    
    ((std::cout << std::forward<decltype(args)>(args) << (  ++k!=sz?", ":"\n") ), ... );    
};

int main()
{    
    PWM<PWM_HW, 0> pwm0;
    PWM<PWM_HW, 1> pwm1;
    PWM<PWM_SW> pwm;

    pwm0.set(1000, 50);
    pwm.set(400, 75);

    std::cout << "PWM id: " << pwm0.pwmId() << std::endl;
    std::cout << "PWM id: " << pwm1.pwmId() << std::endl;

    std::apply(printTuple, pwm0());
      
    return 0;
}
