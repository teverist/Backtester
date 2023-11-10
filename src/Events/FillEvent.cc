#include <Events/FillEvent.h>


int FillEvent::calculate_commission() {
    /**
     * @brief Calculates the fees of trading based on an Interactive Brokers fee structure for API, in USD.
     * 
     * @return int the comission fee, not including exchange or ECN fees.
     */
    double full_cost = 1.3;
    if (quantity_ <= 500) {
        full_cost = std::max(1.3, 0.013 * quantity_);
    } else {
        full_cost = std::max(1.3, 0.008 * quantity_);
    }
    return static_cast<int>(std::round(full_cost));
}


