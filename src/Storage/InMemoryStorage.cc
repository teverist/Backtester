#include <Storage/InMemoryStorage.h>



void InMemoryStorage::save(const Candle& candle) {
    if (candles_.find(candle.symbol_) == candles_.end()) {
        candles_[candle.symbol_] = {};
    }

    candles_[candle.symbol_].push_back(candle);

    // Sort candles by timestamp
    std::sort(candles_[candle.symbol_].begin(), candles_[candle.symbol_].end(), [](const Candle& a, const Candle& b) {
        return a.timestamp_ < b.timestamp_;
    });

} 


std::vector<Candle> InMemoryStorage::get_candles(const std::string& symbol, TimeSpan timespan, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) {
    if (candles_.find(symbol) == candles_.end()) {
        return {};
    }

    std::vector<Candle> candles;

    for (const auto& candle : candles_[symbol]) {
        if (candle.timespan_ == timespan && candle.timestamp_ >= start && candle.timestamp_ <= end) {
            candles.push_back(candle);
        }
    }

    // Do the above in a lambda
    // std::copy_if(candles_[symbol].begin(), candles_[symbol].end(), std::back_inserter(candles), [](const Candle& candle) { 
    //     return candle.timespan_ == timespan && candle.timestamp_ >= start && candle.timestamp_ <= end;
    // });

    return candles;

}