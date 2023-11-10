#ifndef BACKTEST_H
#define BACKTEST_H


#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <thread>

#include "Data/DataHandler.h"
#include "Portfolio/Portfolio.h"
#include "Strategy/Strategy.h"
#include "Execution/Execution.h"
#include "Events/Event.h"


template <typename DataHandlerType, typename PortfolioType, typename StrategyType, typename ExecutionHandlerType>
class Backtest {
public:

Backtest(const std::string& data_dir,
        const std::vector<std::string>& symbol_list,
        double initial_capital,
        const std::string& start_date,
        const std::string& end_date,
        const std::string& interval,
        float heartbeat
    );
    void simulate_trading();

private:
    const std::string data_dir;
    const std::vector<std::string>& symbol_list;
    double initial_capital;
    const std::string start_date;
    const std::string end_date;
    const std::string interval;
    float heartbeat;
    std::shared_ptr<DataHandlerType> data_handler;
    std::unique_ptr<PortfolioType> portfolio;
    std::unique_ptr<StrategyType> strategy;
    std::unique_ptr<ExecutionHandlerType> execution_handler;
    std::shared_ptr<std::queue<Event*>> events;

    int signal_count;
    int order_count;
    int fill_count;
    int num_strats;

    void run_backtest();
    void output_performance();
    void generate_trading_instances();

};

#endif // BACKTEST_H