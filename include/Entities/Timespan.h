#ifndef TIMESPAN_H
#define TIMESPAN_H



enum class TimeSpan {
    Second = 1,
    Minute = 60 * Second,
    Hour = 60 * Minute,
    Day = 24 * Hour,
};


#endif // TIMESPAN_H