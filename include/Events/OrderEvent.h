#ifndef ORDER_EVENT_H
#define ORDER_EVENT_H

#include "Event.h"
#include "FillEvent.h"

enum class OrderType {
    MARKET,
    LIMIT
};

constexpr std::string_view order_type_to_string(OrderType& type) {
    switch (type) {
        case OrderType::MARKET: return "MARKET";
        case OrderType::LIMIT: return "LIMIT";
    }
    return "UNKNOWN";
}

/**
 * @brief Handles the event of sending an Order to an execution system. 
 * The order contains a symbol, a type, quantity and a direction.
 * 
 */
class OrderEvent : public Event {
public:

    OrderEvent(const std::string& symbol, OrderType order_type, int quantity, FillDirection direction) :
        symbol_(symbol), order_type_(order_type), quantity_(quantity), direction_(direction) {};

    EventType getType() const override { return type_; }
    std::string get_symbol() const { return symbol_; }
    OrderType get_order_type() const { return order_type_; }
    int get_quantity() const { return quantity_; }
    FillDirection get_direction() const { return direction_; }


    void print_order();

private:
    const EventType type_ = EventType::Order;

    std::string symbol_;
    OrderType order_type_;
    int quantity_;
    FillDirection direction_;
};



#endif // ORDER_EVENT_H