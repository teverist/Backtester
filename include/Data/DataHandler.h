#ifndef DATAHANDLER_H
#define DATAHANDLER_H


#include <Events/Event.h>
#include "Bar.h"

#include <vector>
#include <unordered_map>
#include <memory>

/**
 * @brief DataHandler is an abstract base class providing an interface for
    all subsequent (inherited) data handlers (both live and historic).

    The goal of a (derived) DataHandler object is to output a generated
    set of bars (OLHCVI) for each symbol requested. 

    This will replicate how a live strategy would function as current
    market data would be sent "down the pipe". Thus a historic and live
    system will be treated identically by the rest of the backtesting suite.
 * 
 */
class DataHandler {
public:
    /**
     * @brief Returns the last N bars from the latest_symbol list, or fewer if less bars are available.
     * 
     * @param symbol 
     * @param N - number of bars to return
     * @return std::vector<std::string>  - vector of strings representing the bars
     */
    virtual std::vector<Bar> get_latest_bars(const std::string& symbol, int N=1) = 0;

    /**
     * @brief Pushes the latest bar to the latest symbol structure for all symbols in the symbol list.
     * 
     * @param symbol 
     */
    virtual void update_bars() = 0;

    /**
     * @brief Returns the symbols
     * 
     */
    virtual std::vector<std::string> get_symbol_list() const = 0;

    virtual double get_latest_bar_value(const std::string& symbol, const std::string& field) = 0;

    virtual Bar get_latest_bar_datetime(const std::string& symbol) = 0;

    virtual Bar get_latest_bar(const std::string& symbol) = 0;

    virtual Bar get_latest_bar_values(const std::string& symbol, const std::string& field, int N=1) = 0;
};


#endif // DATAHANDLER_H