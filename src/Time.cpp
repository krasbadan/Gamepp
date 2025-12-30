#include "Time.hpp"

#include <cmath>



Time::Time():
    days(0), seconds(0)
{}
Time::Time(float _seconds) {
    seconds = std::remquof(_seconds, DAY_DURATION, &days);
}
Time::Time(int _days, float _seconds):
    days(_days), seconds(_seconds)
{}

Time Time::operator+=(Time other) {
    days += other.days;
    seconds += other.seconds;
    if (seconds >= DAY_DURATION) {
        ++days;
        seconds -= DAY_DURATION;
    }
    return *this;
}
Time Time:: operator-=(Time other) {
    days -= other.days;
    seconds -= other.seconds;
    if (seconds < 0) {
        --days;
        seconds += DAY_DURATION;
    }
    return *this;
}
Time Time::operator+(Time other) const {
    int new_day = days + other.days;
    float new_seconds = seconds + other.seconds;
    if (new_seconds >= DAY_DURATION)
        return Time(new_day+1, new_seconds-DAY_DURATION);
    return Time(new_day, new_seconds);
}
Time Time::operator-(Time other) const {
    int new_day = days - other.days;
    float new_seconds = seconds - other.seconds;
    if (new_seconds < 0)
        return Time(new_day-1, new_seconds+DAY_DURATION);
    return Time(new_day, new_seconds);
}