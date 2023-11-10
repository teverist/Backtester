#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <cmath>
#include <iostream>

enum class EventType {
    Market,
    Signal,
    Order,
    Fill
};


constexpr std::string_view event_type_to_string(EventType& type) {
    switch (type) {
        case EventType::Market: return "Market";
        case EventType::Signal: return "Signal";
        case EventType::Order: return "Order";
        case EventType::Fill: return "Fill";
    }

    // This should never happen
    return "UNKNOWN";
}


class Event {
public:
    virtual ~Event() = default;
    virtual EventType getType() const = 0;
};

#endif // EVENT_H