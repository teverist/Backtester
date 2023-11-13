#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <Events/Event.h>
#include <Events/FillEvent.h>
#include <Events/OrderEvent.h>
#include <Events/SignalEvent.h>
#include <Events/MarketEvent.h>

#include <Data/DataHandler.h>

#include <memory>
#include <queue>

template <class DataHandlerType>
class Portfolio {
public:
    Portfolio(std::shared_ptr<std::queue<std::shared_ptr<Event>>>& events_queue, 
        std::shared_ptr<DataHandlerType>& data_handler, 
        const std::string& start_date, 
        double initial_capital
    );

    void update_timeindex(const Event& event);
    void update_fill(Event& event);
    void update_signal(Event& event);

private:

    std::shared_ptr<std::queue<std::shared_ptr<Event>>> events_queue_;
    std::shared_ptr<DataHandlerType> data_handler_;
    std::string start_date_;
    double initial_capital_;
    std::vector<std::string> symbol_list_;

    std::vector<std::unordered_map<std::string, double>> all_positions_;
    std::vector<std::unordered_map<std::string, double>> all_holdings_;
    std::unordered_map<std::string, double> current_positions_;
    std::unordered_map<std::string, double> current_holdings_;

    std::vector<std::unordered_map<std::string, double>> construct_all_positions();
    std::vector<std::unordered_map<std::string, double>> construct_all_holdings();
    std::unordered_map<std::string, double> construct_current_holdings();

    void update_positions_after_fill(const FillEvent& fill_event);
    void update_holdings_after_fill(const FillEvent& fill_event);
    std::shared_ptr<Event> generate_naive_order(const SignalEvent& signal);

};



#endif // PORTFOLIO_H