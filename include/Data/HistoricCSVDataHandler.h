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
        std::shared_ptr<std::queue<std::shared_ptr<Event>>>& events, 
        const std::string& csv_dir, 
        const std::vector<std::string>& symbol_list
    );

    std::vector<std::string> get_symbol_list() const override { return symbol_list_; }
    std::string get_latest_bar_datetime(const std::string& symbol) override;
    double get_latest_bar_value(const std::string& symbol, const std::string& field) override;
    void update_bars();
    std::vector<Bar> get_latest_bar_values(const std::string& symbol, const std::string& field, int N=1) override;


    bool continue_backtest = true;
    const std::vector<std::string> symbol_list_;   

private:
    const std::string csv_dir_;
    std::shared_ptr<std::queue<std::shared_ptr<Event>>> events_;

    std::unordered_map<std::string, std::vector<Bar>> bars_;
    std::unordered_map<std::string, std::vector<Bar>> latest_symbol_data_;
    std::unordered_map<std::string, std::vector<Bar>> symbol_data_;

    void open_convert_csv_files_();
    std::vector<Bar> get_latest_bars(const std::string& symbol, int N=1) override;
    
};


#endif // HISTORIC_CSV_DATA_HANDLER_H