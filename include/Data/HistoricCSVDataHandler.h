#ifndef HISTORIC_CSV_DATA_HANDLER_H
#define HISTORIC_CSV_DATA_HANDLER_H

#include "Data/DataHandler.h"

#include <fstream>

/**
 * @brief HistoricCSVDataHandler is designed to read CSV files for
    each requested symbol from disk and provide an interface
    to obtain the "latest" bar in a manner identical to a live
    trading interface. 
 * 
 */
class HistoricCSVDataHandler : public DataHandler {
public:
    HistoricCSVDataHandler(
        std::shared_ptr<std::vector<Event*>>& events, 
        const std::string& csv_dir, 
        const std::vector<std::string>& symbol_list
    ) : events_(events), csv_dir_(csv_dir), symbol_list_(symbol_list) {
        open_convert_csv_files_();
    }

    std::vector<std::string> get_symbol_list() const override { return symbol_list_; }
    Bar get_latest_bar_datetime(const std::string& symbol) override;
    double get_latest_bar_value(const std::string& symbol, const std::string& field) override;



    const std::vector<std::string> symbol_list_;   

private:
    bool continue_backtest_ = true;
    const std::string csv_dir_;
    std::shared_ptr<std::vector<Event*>> events_;

    std::unordered_map<std::string, std::vector<Bar>> bars_;
    std::unordered_map<std::string, std::vector<Bar>> latest_symbol_data_;
    std::unordered_map<std::string, std::vector<Bar>> symbol_data_;

    void open_convert_csv_files_();
    std::vector<Bar> get_latest_bars(const std::string& symbol, int N=1) override;
    void update_bars();
    
};


#endif // HISTORIC_CSV_DATA_HANDLER_H