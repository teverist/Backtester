#ifndef IN_MEMORY_STORAGE_H
#define IN_MEMORY_STORAGE_H

#include <algorithm>

#include <Storage/StorageProvider.h>

class InMemoryStorage : public StorageProvider {
public:
    void save(const Candle& candle) override;
    std::vector<Candle> get_candles(const std::string& symbol, TimeSpan timespan, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) override;
private:
    std::unordered_map<std::string, std::vector<Candle>> candles_;
};


#endif // IN_MEMORY_STORAGE_H