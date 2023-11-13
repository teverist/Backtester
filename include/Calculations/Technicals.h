#ifndef TECHNICALS_H
#define TECHNICALS_H

#include <vector>

#include <Entities/Candle.h>


class TechnicalCalculator {
public:
    TechnicalCalculator(std::vector<Candle>& candles);
    std::vector<float> sma(int period);

private:
    std::vector<Candle> candles_;
    std::vector<float> closes_;
    std::vector<float> highs_;
    std::vector<float> lows_;
    std::vector<float> volumes_;
};




#endif // TECHNICALS_H