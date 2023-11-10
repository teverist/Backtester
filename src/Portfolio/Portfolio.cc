#include <Portfolio/Portfolio.h>


template <typename DataHandlerType>
Portfolio<DataHandlerType>::Portfolio(
    std::shared_ptr<std::queue<Event*>>& events_queue,
    std::shared_ptr<DataHandlerType>& data_handler,
    std::string_view start_date,
    double initial_capital
) {
    events_queue_ = events_queue;
    data_handler_ = data_handler;
    start_date_ = start_date;
    initial_capital_ = initial_capital;
    symbol_list_ = data_handler_->get_symbol_list();

    all_positions_ = construct_all_positions();
    all_holdings_ = construct_all_holdings();
    current_holdings_ = construct_current_holdings();
    std::unordered_map<std::string, double> current_positions;
    for (const auto& symbol : symbol_list_) {
        current_positions[symbol] = 0.0;
    }
}


template <typename DataHandlerType>
std::vector<std::unordered_map<std::string, double>> Portfolio<DataHandlerType>::construct_all_positions() {
    std::unordered_map<std::string, double> positions;
    for (const auto& symbol : symbol_list_) {
        positions[symbol] = 0.0;
    }
    positions["datetime"] = start_date_;
    return {positions};
}


template <typename DataHandlerType>
std::vector<std::unordered_map<std::string, double>> Portfolio<DataHandlerType>::construct_all_holdings() {
    std::unordered_map<std::string, double> holdings;
    for (const auto& symbol : symbol_list_) {
        holdings[symbol] = 0.0;
    }
    holdings["datetime"] = start_date_;
    holdings["cash"] = initial_capital_;
    holdings["commission"] = 0.0;
    holdings["total"] = initial_capital_;
    return {holdings};
}


template <typename DataHandlerType>
std::unordered_map<std::string, double> Portfolio<DataHandlerType>::construct_current_holdings() {
    std::unordered_map<std::string, double> holdings;
    for (const auto& symbol : symbol_list_) {
        holdings[symbol] = 0.0;
    }
    holdings["cash"] = initial_capital_;
    holdings["commission"] = 0.0;
    holdings["total"] = initial_capital_;
    return holdings;
}


template <typename DataHandlerType>
void Portfolio<DataHandlerType>::update_timeindex() {
    std::unordered_map<std::string, double> position;
    for (const auto& symbol : symbol_list_) {
        position[symbol] = current_positions_[symbol];
    }
    position["datetime"] = data_handler_->get_latest_bar_datetime(symbol_list_[0]);
    all_positions_.push_back(position);

    std::unordered_map<std::string, double> holdings;
    for (const auto& symbol : symbol_list_) {
        holdings[symbol] = current_holdings_[symbol];
    }
    holdings["datetime"] = data_handler_->get_latest_bar_datetime(symbol_list_[0]);
    holdings["cash"] = current_holdings_["cash"];
    holdings["commission"] = current_holdings_["commission"];
    holdings["total"] = current_holdings_["total"];
    all_holdings_.push_back(holdings);
}


template <typename DataHandlerType>
void Portfolio<DataHandlerType>::update_signal(Event& event) {
    if (event.getType() == EventType::Signal) {
        auto signal_event = static_cast<const SignalEvent&>(event);
        auto order_event = generate_naive_order(signal_event);
        events_queue_->push(order_event);
    }
}


template <typename DataHandlerType>
OrderEvent Portfolio<DataHandlerType>::generate_naive_order(const SignalEvent& signal) {
    OrderEvent order;
    auto symbol = signal.symbol;
    auto direction = signal.signal_type;
    auto strength = signal.strength;
    auto mkt_quantity = std::floor(100 * strength);
    auto cur_quantity = current_positions_[symbol];
    auto order_type = OrderType::MARKET;

    if (direction == SignalType::LONG && cur_quantity == 0) {
        order = OrderEvent(symbol, order_type, mkt_quantity, "BUY");
    }
    if (direction == SignalType::SHORT && cur_quantity == 0) {
        order = OrderEvent(symbol, order_type, mkt_quantity, "SELL");
    }
    if (direction == SignalType::EXIT && cur_quantity > 0) {
        order = OrderEvent(symbol, order_type, abs(cur_quantity), "SELL");
    }
    if (direction == SignalType::EXIT && cur_quantity < 0) {
        order = OrderEvent(symbol, order_type, abs(cur_quantity), "BUY");
    }
    return order;
}

template <typename DataHandlerType>
void Portfolio<DataHandlerType>::update_fill(Event& event) {
    if(event.getType() == EventType::Fill) {
        auto fill_event = static_cast<FillEvent&>(event);
        update_positions_after_fill(fill_event);
        update_holdings_after_fill(fill_event);
    }
}

template <typename DataHandlerType>
void Portfolio<DataHandlerType>::update_positions_after_fill(const FillEvent& fill_event) {
    auto symbol = fill_event.getSymbol();
    auto direction = fill_event.getDirection();
    auto quantity = fill_event.getQuantity();
    auto fill_dir = 0;
    if (direction == FillDirection::BUY) {
        fill_dir = 1;
    } else if (direction == FillDirection::SELL) {
        fill_dir = -1;
    }
    current_positions_[symbol] += fill_dir * quantity;
}

template <typename DataHandlerType>
void Portfolio<DataHandlerType>::update_holdings_after_fill(const FillEvent& fill_event) {
    auto fill_dir = 0;
    if (fill_event.direction_ == FillDirection::BUY) {
        fill_dir = 1;
    } else if (fill_event.direction_ == FillDirection::SELL) {
        fill_dir = -1;
    }
    auto fill_cost = data_handler_->get_latest_bar_value(fill_event.getSymbol(), "adj_close");
    auto cost = fill_dir * fill_event.getQuantity() * fill_cost;
    current_holdings_[fill_event.getSymbol()] += cost;
    current_holdings_["commission"] += fill_event.getCommission();
    current_holdings_["cash"] -= cost + fill_event.getCommission();
    current_holdings_["total"] -= cost + fill_event.getCommission();
}   