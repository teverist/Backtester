#include <Backtest/Backtest.h>


template <typename DataHandlerType, typename PortfolioType, typename StrategyType, typename ExecutionHandlerType>
Backtest<DataHandlerType, PortfolioType, StrategyType, ExecutionHandlerType>::Backtest(
    const std::string& data_dir,
    const std::vector<std::string>& symbol_list,
    double initial_capital,
    const std::string& start_date,
    const std::string& end_date,
    const std::string& interval,
    float heartbeat
) {
    this->data_dir = data_dir;
    this->symbol_list = symbol_list;
    this->initial_capital = initial_capital;
    this->start_date = start_date;
    this->end_date = end_date;
    this->interval = interval;
    this->heartbeat = heartbeat;

    this->events = std::make_shared<std::queue<Event*>>();

    this->signal_count = 0;
    this->order_count = 0;
    this->fill_count = 0;
    this->num_strats = 1;

    generate_trading_instances();

}

template <typename DataHandlerType, typename PortfolioType, typename StrategyType, typename ExecutionHandlerType>
void Backtest<DataHandlerType, PortfolioType, StrategyType, ExecutionHandlerType>::generate_trading_instances() {
    std::cout << "Creating DataHandler, Strategy, Portfolio and ExecutionHandler" << std::endl;

    // Create the data handler
    this->data_handler = std::make_shared<DataHandlerType>(data_dir, symbol_list);

    // Create the portfolio
    this->portfolio = std::make_unique<PortfolioType>(data_handler, events, start_date, initial_capital);

    // Create the strategy
    this->strategy = std::make_unique<StrategyType>(data_handler, events);

    // Create the execution handler
    this->execution_handler = std::make_unique<ExecutionHandlerType>(events);
} 


template <typename DataHandlerType, typename PortfolioType, typename StrategyType, typename ExecutionHandlerType>
void Backtest<DataHandlerType, PortfolioType, StrategyType, ExecutionHandlerType>::run_backtest() {

    int i = 0;

    while (true) {
        i++;
        std::cout << "Backtest iteration: " << i << std::endl;

        // Update the market bars
        if (data_handler->continue_backtest) {
            data_handler->update_bars();
        } else {
            break;
        }

        // Handle the events
        while (!events->empty()) {
            auto event = events->front();
            events->pop();

            switch(event->getType()) {
                case EventType::Market: {
                    strategy->calculate_signals(event);
                    portfolio->update_time_index(event);
                    break;
                }
                case EventType::Signal: {
                    portfolio->update_signal(event);
                    break;
                }
                case EventType::Order: {
                    execution_handler->execute_order(event);
                    break;
                }
                case EventType::Fill: {
                    portfolio->update_fill(event);
                    break;
                }
                default: {
                    std::cout << "Event type not recognised" << std::endl;
                    break;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(heartbeat));

    }

        
}


template <typename DataHandlerType, typename PortfolioType, typename StrategyType, typename ExecutionHandlerType>
void Backtest<DataHandlerType, PortfolioType, StrategyType, ExecutionHandlerType>::output_performance() {
    std::cout << "Creating summary stats..." << std::endl;

    std::cout << "Signals: " << signal_count << std::endl;
    std::cout << "Orders: " << order_count << std::endl;
    std::cout << "Fills: " << fill_count << std::endl;

    // TODO: Create equity curve and portfolio stats
}


template <typename DataHandlerType, typename PortfolioType, typename StrategyType, typename ExecutionHandlerType>
void Backtest<DataHandlerType, PortfolioType, StrategyType, ExecutionHandlerType>::simulate_trading() {
    std::cout << "Running backtest..." << std::endl;
    run_backtest();
    output_performance();
}