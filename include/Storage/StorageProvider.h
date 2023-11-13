#ifndef STORAGE_PROVIDER_H
#define STORAGE_PROVIDER_H


#include <vector>
#include <chrono>
#include <unordered_map>

#include <Entities/Candle.h>
#include <Entities/Timespan.h>


class StorageProvider {
public:
    virtual void save(const Candle& candle) = 0;
    virtual std::vector<Candle> get_candles(std::string_view symbol, TimeSpan timespan, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) = 0;
};



#endif // STORAGE_PROVIDER_H