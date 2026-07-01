
#include "log.hpp"

#ifdef ARDUINO

#include <Arduino.h>

#ifdef IS_M5
#include <M5Unified.h>
#endif  // IS_M5

#endif  // Arduino

namespace Config {
// delays
static constexpr uint16_t startup_delay = 2000;
static constexpr uint32_t loop_interval = 250000;
}  // namespace Config

namespace Global {
uint32_t loop_counter = 0;
}

#ifdef ARDUINO

void setup() {
#ifdef LOG_SERIAL
    Serial.begin(SERIAL_SPEED);
#endif  // LOG_SERIAL
    delay(Config::startup_delay);
    LOG_N(Log::Uni::Main, Log::Sev::All, Log::Note::Starting);
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::Started);
}

#ifdef IS_M5
// M5 updates, button handling etc may also go here
void updateM5(void) { M5.update(); }
#endif

void loop(void) {
    if (Global::loop_counter > Config::loop_interval) {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::LoopedN,
              Global::loop_counter);
        Global::loop_counter = 0;
    }
#ifdef IS_M5
    updateM5();
#endif
    Global::loop_counter++;
}

#else  // !ARDUINO

#include <iostream>

void test(void) {
    uint16_t times = 0;
    LOG_N(Log::Uni::Unnamed, Log::Sev::All, Log::Note::Starting);
    LOG_N(Log::Uni::Main, Log::Sev::Err, Log::Note::Started);
    std::cout << std::hex
              << "Unit: " << static_cast<uint32_t>(lg.get_unit_mask())
              << std::endl;
    std::cout << "Sev: " << static_cast<uint16_t>(lg.get_severity())
              << std::endl;
    std::cout << std::dec << "loops: " << Global::loop_counter << std::endl;
    std::cout << "times: " << times << std::endl;
    while (times < 3) {
        if (Global::loop_counter > Config::loop_interval) {
            LOG_N(Log::Uni::Test, Log::Sev::Inf, Log::Note::LoopedN,
                  Global::loop_counter);
            Global::loop_counter = 0;
            times++;
        }
        Global::loop_counter++;
    }
    LOG_E(Log::Uni::Main, Log::Err::UnexpectedError);
    LOG(Log::Uni::Main, Log::Sev::Wrn, "A test %d", 45);
    std::cout << "loops: " << Global::loop_counter << std::endl;
    std::cout << "times: " << times << std::endl;
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::Done);
}

int main(int argc, char* argv[]) {
    std::cout << "Everything" << std::endl;
    test();
    std::cout << "Only Test" << std::endl;
    lg.set_unit_mask(Log::Uni::Test);
    test();
    std::cout << "Only Main" << std::endl;
    lg.set_unit_mask(Log::Uni::Main);
    test();
    std::cout << "Everything" << std::endl;
    lg.set_unit_mask(Log::Uni::Last);
    test();
    std::cout << "Only Warnings+" << std::endl;
    lg.set_severity(Log::Sev::Wrn);
    test();
    std::cout << "Only Errors+" << std::endl;
    lg.set_severity(Log::Sev::Err);
    test();
}

#endif  // ARDUINO else

void log_output_impl(const char* str, bool error, bool truncated) {
    if (error) {
        // there was a an error expanding the string
#ifdef LOG_SERIAL
        LOG_SERIAL.printf("Format!: %s\n", str);
#elifdef LOG_STDERR
        std::cout << "Format!: " << str << std::endl;
#endif  // LOG_SERIAL LOG_STDERR
    } else if (truncated) {
        // the line got truncated
#ifdef LOG_SERIAL
        LOG_SERIAL.printf("Trunc!: %s\n", str);
#elifdef LOG_STDERR
        std::cout << "Trunc!: " << str << std::endl;
#endif  // LOG_SERIAL LOG_STDERR
    } else {
        // all is good
#ifdef LOG_SERIAL
        LOG_SERIAL.println(str);
#elifdef LOG_STDERR
        std::cout << str << std::endl;
#endif  // LOG_SERIAL LOG_STDERR
    }
}
