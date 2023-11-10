#ifndef EXECUTION_H
#define EXECUTION_H

#include "Events/Event.h"
#include "Events/OrderEvent.h"
#include "Events/FillEvent.h"

#include <chrono>
#include <queue>
#include <memory>
//#include <format>


class ExecutionHandler {
public:
    virtual void execute_order(const OrderEvent& order_event) = 0;
};


#endif // EXECUTION_H