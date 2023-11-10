#ifndef STRATEGY_H
#define STRATEGY_H

#include <Events/Event.h>
#include <Data/DataHandler.h>
#include <Events/OrderEvent.h>
#include <Events/SignalEvent.h>

#include <memory>
#include <queue>

class Strategy {
public:
    virtual void calculate_signals(Event& event) = 0;
};

#endif // STRATEGY_H