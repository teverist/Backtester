
#include <gtest/gtest.h>

#include <chrono>
#include <vector>

#include <Entities/Candle.h>
#include <Entities/Timespan.h>
#include <Storage/InMemoryStorage.h>

constexpr std::string TEST_SYMBOL = "TEST";

// Set up test fixture
class InMemoryStorageTest : public ::testing::Test {
protected:
    void setUp() override;

};


// Test save single candle
TEST_F(InMemoryStorageTest, save_single_candle) {
    InMemoryStorage storage = InMemoryStorage();

    auto minute_candle = _generate_candle(TimeSpan::MINUTE, std::chrono::high_resolution_clock::now());
    storage.save(minute_candle);

    auto candles = storage.get_candles(TEST_SYMBOL, TimeSpan::MINUTE, minute_candle.timestamp_, minute_candle.timestamp_);

    ASSERT_EQ(candles.size(), 1);
    ASSERT_EQ(TEST_SYMBOL, candles[0].symbol_);
    ASSERT_EQ(TimeSpan::MINUTE, candles[0].timespan_);
    ASSERT_EQ(minute_candle.timestamp_, candles[0].timestamp_);
}

// Test save different timespan candles
TEST_F(InMemoryStorageTest, save_different_timespan_candles) {
    InMemoryStorage storage = InMemoryStorage();

    auto minute_candle = _generate_candle(TimeSpan::MINUTE, std::chrono::high_resolution_clock::now());
    auto hour_candle = _generate_candle(TimeSpan::HOUR, std::chrono::high_resolution_clock::now());
    auto day_candle = _generate_candle(TimeSpan::DAY, std::chrono::high_resolution_clock::now());

    storage.save(minute_candle);
    storage.save(hour_candle);
    storage.save(day_candle);

    auto candles = storage.get_candles(TEST_SYMBOL, TimeSpan::MINUTE, minute_candle.timestamp_, minute_candle.timestamp_);

    ASSERT_EQ(candles.size(), 1);
    ASSERT_EQ(TEST_SYMBOL, candles[0].symbol_);
    ASSERT_EQ(TimeSpan::MINUTE, candles[0].timespan_);
    ASSERT_EQ(minute_candle.timestamp_, candles[0].timestamp_);
}



static Candle _generate_candle(TimeSpan timespan, std::chrono::high_resolution_clock::time_point timestamp) {
    return Candle(TEST_SYMBOL, timespan, timestamp, 0.0, 0.0, 0.0, 0.0, 0.0);
}