#include <Execution/SimpleSimulatedExecutionHandler.h>


void SimpleSimulatedExecutionHandler::execute_order(const OrderEvent& event) {
    auto fill_event = std::make_shared<FillEvent>(
        "2020-01-01", // TODO: Get current time
        event.symbol_,
        event.quantity_,
        event.direction_,
        1.0, // TODO: Get current price
        0.0
    );
    
    events_queue_->push(fill_event);
}