#ifndef _SRC_CONTROLLER_PWM_SW_HPP_
#define _SRC_CONTROLLER_PWM_SW_HPP_

#include <pwm.hpp>

using emblocks::components::pwm::tl::PWM;

class PWM_SW : public PWM<PWM_SW>
{
public:
    void init() {
        // sw inplementation        
    }

    void deinit() {
        
    }

    void run() {
        // that one might need some threading
    }

    void stop() {
        
    }

    void set() {
        // freq & duty set in a base class, make use of:
        // this->frequency
        // this->duty
    }
};

#endif /* _SRC_CONTROLLER_PWM_SW_HPP_ */