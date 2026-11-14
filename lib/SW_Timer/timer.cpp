
#include <timer.h>

Timer::Timer(u32 time, bool reset) : time(time), reset(reset), timer(0) {
}

void Timer::setTimer() {
    timer = time + millis();
}

u08 Timer::isTimedout() {
    u08 result = false;

    if (millis() > timer) {
        result = true;
        if ((time > 0) && reset) {
            timer = time + millis();
        }
    }
    return result;
}

void Timer::setTime(u32 newTime) {
    time = newTime;
}

void Timer::setReset(bool resetValue) {
    reset = resetValue;
}
