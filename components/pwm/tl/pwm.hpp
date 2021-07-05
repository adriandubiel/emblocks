#ifndef _COMPONENTS_PWM_TL_PWM_HPP_
#define _COMPONENTS_PWM_TL_PWM_HPP_

#include <tuple>

namespace emblocks::components::pwm::tl
{
	template<typename Controller, size_t PwmId=0U>
	class PWM {
	public:
		PWM() : frequency(0), duty(0), _pwmId(PwmId) {}

		PWM(int freq, int duty) : frequency(freq), duty(duty) { }

		void init() {
			static_cast<Controller*>(this)->init();
		}

		void deinit() {
			static_cast<Controller*>(this)->deinit();
		}

		void run() {
			static_cast<Controller*>(this)->run();
		}

		void stop() {
			static_cast<Controller*>(this)->stop();
		}

		void set(int freq, int duty) {
			this->frequency = freq;
        	this->duty = duty;
			static_cast<Controller*>(this)->set();
		}

		size_t pwmId(){
			return _pwmId;
		}

		auto operator()() const {
			return std::tuple(frequency, duty, _pwmId);
		}

		auto operator()() {
			return std::tuple(frequency, duty, _pwmId);
		}

	protected:
		int frequency;
		int duty;
        size_t _pwmId;
	};

}

#endif /* _COMPONENTS_PWM_TL_PWM_HPP_ */
