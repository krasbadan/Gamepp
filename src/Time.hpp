#pragma once



const float DAY_DURATION = 60;

struct Time {
    int days;
    float seconds;
    
    Time();
    Time(float seconds);
    Time(int days, float seconds);
    
    Time operator+=(Time other);
    Time operator-=(Time other);
    Time operator+(Time other) const;
    Time operator-(Time other) const;
};