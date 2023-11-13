#include <Strategy/BuyAndHoldStrategy.h>

std::unordered_map<std::string, bool> BuyAndHoldStrategy::calculate_initial_bought_() {
    std::unordered_map<std::string, bool> bought;
    for(auto& symbol : symbol_list_) {
        bought[symbol] = false;
    }
    return bought;
}

void BuyAndHoldStrategy::calculate_signals(Event& event) { 
    constexpr double strength = 1.0;
    if(event.getType() == EventType::Market) {
        for (const auto& symbol : symbol_list_) {
            auto bars = data_handler_->get_latest_bars(symbol);
            if (bars.size() > 0) {
                if (!bought_[symbol]) {
                    auto signal = std::make_shared<SignalEvent>(symbol, "now", SignalType::LONG, strength);
                    events_->push(signal);
                    bought_[symbol] = true;
                }
            }
            
        }
    }
}
