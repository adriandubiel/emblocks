# Find Zephyr. This also loads Zephyr's build system.
cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr)
project(my_zephyr_app)

set(BOARD_FLASH_RUNNER jlink)

# Add your source file to the "app" target. This must come after
# find_package(Zephyr) which defines the target.
target_sources(app PRIVATE src/main.cpp
            ../../zmodules/pwm/PWM.cpp)

target_include_directories(app PRIVATE 
            ../../modules/pwm/
            ../../zmodules/pwm/)
