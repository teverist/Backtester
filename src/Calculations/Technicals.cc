#include <Calculations/Technicals.h>


TechnicalCalculator::TechnicalCalculator(std::vector<Candle>& candles) {
    candles_ = candles;
    for (const auto& candle : candles_) {
        closes_.push_back(candle.close_);
        highs_.push_back(candle.high_);
        lows_.push_back(candle.low_);
        volumes_.push_back(candle.volume_);
    }
}


std::vector<float> TechnicalCalculator::sma(int period) {
    if (candles_.size() < period) {
        return {};
    }

    std::vector<float> sma;

    for (int i = period; i < candles_.size(); i++) {
        float sum = 0.0;
        for (int j = i - period; j < i; j++) {
            sum += closes_[j];
        }
        sma.push_back(sum / period);
    }

    return sma;

}