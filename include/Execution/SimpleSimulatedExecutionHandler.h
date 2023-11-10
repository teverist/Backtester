#ifndef SIMPLE_SIMULATED_EXECUTION_HANDLER_H
#define SIMPLE_SIMULATED_EXECUTION_HANDLER_H

#include "Execution.h"


class SimpleSimulatedExecutionHandler : public ExecutionHandler {
public:
    SimpleSimulatedExecutionHandler(std::shared_ptr<std::queue<Event*>>& events_queue) : events_queue_(events_queue) {}
    void execute_order(const OrderEvent& order_event) override;


private:
    std::shared_ptr<std::queue<Event*>> events_queue_;
};



#endif // SIMPLE_SIMULATED_EXECUTION_HANDLER_H