#ifndef BUY_AND_HOLD_STRATEGY_H
#define BUY_AND_HOLD_STRATEGY_H

#include "Strategy.h"
#include <Data/Bar.h>

#include <vector>

class BuyAndHoldStrategy : public Strategy {
public:

    BuyAndHoldStrategy(std::shared_ptr<DataHandler> data_handler, std::shared_ptr<std::queue<std::shared_ptr<Event>>> events) 
        : data_handler_(data_handler), events_(events) {
        symbol_list_ = data_handler_->get_symbol_list();
        bought_ = calculate_initial_bought_();
        };
    
    void calculate_signals(Event& event) override;
    

private:
    std::shared_ptr<std::queue<std::shared_ptr<Event>>> events_;
    std::shared_ptr<DataHandler> data_handler_;
    std::vector<std::string> symbol_list_;
    std::unordered_map<std::string, bool> bought_;

    std::unordered_map<std::string, bool> calculate_initial_bought_();  
};


#endif // BUY_AND_HOLD_STRATEGY_H