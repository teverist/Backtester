
#include <iostream>


#include <Events/Event.h>
#include <Events/FillEvent.h>
#include <Events/OrderEvent.h>
#include <Events/SignalEvent.h>
#include <Data/DataHandler.h>
#include <Data/HistoricCSVDataHandler.h>
#include <Portfolio/Portfolio.h>
#include <Strategy/Strategy.h>
#include <Strategy/BuyAndHoldStrategy.h>
#include <Execution/Execution.h>
#include <Execution/SimpleSimulatedExecutionHandler.h>
#include <Backtest/Backtest.h>


int main() {
    std::cout << "Hello, World!" << std::endl;

    const std::string data_dir {"../data"};
    const std::vector<std::string> symbol_list = {"AAPL", "GOOG"};
    double initial_capital = 100000.0;
    const std::string start_date = "2018-01-01";
    const std::string end_date = "2018-01-31";
    const std::string interval = "1d";
    float heartbeat = 0.0;


    auto backtest = Backtest<HistoricCSVDataHandler, Portfolio<HistoricCSVDataHandler>, BuyAndHoldStrategy, SimpleSimulatedExecutionHandler>(
        data_dir,
        symbol_list,
        initial_capital,
        start_date,
        end_date,
        interval,
        heartbeat
    );

    return 0;
}