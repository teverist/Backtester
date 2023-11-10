#include <Events/OrderEvent.h>

void OrderEvent::print_order() {
    std::cout << "Order: Symbol=" << symbol_ << ", Type=" << order_type_to_string(order_type_) << ", Quantity=" << quantity_ << ", Direction=" << fill_direction_to_string(direction_) << std::endl;
}