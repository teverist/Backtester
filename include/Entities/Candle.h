#ifndef CANDLE_H
#define CANDLE_H

#include <chrono>
#include <string>

#include <Entities/Timespan.h>

class Candle {
public :
    Candle(std::string& symbol, TimeSpan timespan, std::chrono::high_resolution_clock::time_point timestamp, float open, float close, float high, float low, float volume) :
        symbol_(symbol), timespan_(timespan), timestamp_(timestamp), open_(open), close_(close), high_(high), low_(low), volume_(volume) {};

    const std::string symbol_;
    const TimeSpan timespan_;
    const std::chrono::high_resolution_clock::time_point timestamp_;
    const float open_;
    const float close_;
    const float high_;
    const float low_;
    const float volume_;
};

#endif // CANDLE_H