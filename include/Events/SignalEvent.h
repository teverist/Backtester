#ifndef SIGNAL_EVENT_H
#define SIGNAL_EVENT_H

#include "Event.h"


enum class SignalType {
    LONG,
    SHORT,
    EXIT
};


/**
 * @brief  Handles the event of sending a Signal from a Strategy object.
 * This is received by a Portfolio object and acted upon
 * 
 */
class SignalEvent : public Event
{
public:

    SignalEvent(std::string symbol, std::string datetime, SignalType signal_type, double strength = 1.0) :
        symbol(symbol), datetime(datetime), signal_type(signal_type), strength(strength) {};

    EventType getType() const override { return type; }

    std::string symbol;
    std::string datetime;
    SignalType signal_type;
    double strength;

private:
    const EventType type = EventType::Signal;


};


#endif // SIGNAL_EVENT_H

