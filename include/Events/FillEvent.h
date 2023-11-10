#ifndef FILL_EVENT_H
#define FILL_EVENT_H


#include "Event.h"


enum class FillDirection {
    BUY,
    SELL
};

constexpr std::string_view fill_direction_to_string(FillDirection& direction) {
    switch (direction) {
        case FillDirection::BUY: return "BUY";
        case FillDirection::SELL: return "SELL";
    }

    // This should never happen
    return "UNKNOWN";
}


/**
 * @brief Encapsulates the notion of a Filled Order, as returned from a brokerage. 
 * Stores the quantity of an instrument actually filled and at what price. 
 * In addition, stores the commission of the trade from the brokerage.
 * 
 */
class FillEvent : public Event {
public:
    FillEvent(
        const std::string& timeindex, 
        const std::string& symbol, 
        int quantity, 
        FillDirection direction, 
        double fill_cost, 
        double commission = 0.0
        ) : timeindex_(timeindex), symbol_(symbol), quantity_(quantity), direction_(direction), fill_cost_(fill_cost), commission_(commission) {};
    
    /**
     * @brief Calculates the fees of trading based on an Interactive Brokers fee structure for API, in USD.
     * 
     * @return int the comission fee, not including exchange or ECN fees.
     */
    int calculate_commission();

    EventType getType() const override { return type_; }
    std::string getSymbol() const { return symbol_; }
    int getQuantity() const { return quantity_; }
    FillDirection getDirection() const { return direction_; }
    double getFillCost() const { return fill_cost_; }
    double getCommission() const { return commission_; }
    std::string getTimeindex() const { return timeindex_; }


    FillDirection direction_;
    
private:
    const EventType type_ = EventType::Fill;

    const std::string timeindex_;
    const std::string symbol_;
    int quantity_;
    double fill_cost_;
    double commission_;
};

#endif // FILL_EVENT_H