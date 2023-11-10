#include <Execution/SimpleSimulatedExecutionHandler.h>


void SimpleSimulatedExecutionHandler::execute_order(const OrderEvent& event) {
    auto fill_event = FillEvent(
        //Todo: change to libfmt
        //std::format("{:%d-%m-%Y %H:%M:%OS}", std::chrono::system_clock::now()),
        std::string("2021-01-01 00:00:00"),
        event.get_symbol(),
        event.get_quantity(),
        event.get_direction(),
        1.0,
        0.0
    );

    this->events_queue_->push(new FillEvent(fill_event));

}