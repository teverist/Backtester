#ifndef MARKET_EVENT_H
#define MARKET_EVENT_H

#include "Event.h"

/**
 * @brief Handles the event of receiving a new market update with corresponding bars.
 * 
 */
class MarketEvent : public Event
{
public:
    EventType getType() const override { return type; }


private:
    const EventType type = EventType::Market;
};

#endif // MARKET_EVENT_H