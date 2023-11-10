#include <Data/HistoricCSVDataHandler.h>
#include <Utility/Utility.h>
#include <Events/MarketEvent.h>

#include <algorithm>


/**
 * @brief Opens the CSV files from the data directory.
 * Assumes data is from Yahoo.
 * 
 */
void HistoricCSVDataHandler::open_convert_csv_files_() {
    for(auto& symbol : symbol_list_) {
        std::string filename = csv_dir_ + symbol + ".csv";
        std::ifstream csv_file(filename);
        std::string line;
        
        if(csv_file.is_open()) {
            while(std::getline(csv_file, line)) {
                std::vector<std::string> line_data = Utility::split(line, ',');
                Bar bar;
                bar.datetime = std::stoi(line_data[0]);
                bar.open = std::stod(line_data[1]);
                bar.high = std::stod(line_data[2]);
                bar.low = std::stod(line_data[3]);
                bar.close = std::stod(line_data[4]);
                bar.adj_close = std::stod(line_data[5]);
                bar.volume = std::stoi(line_data[6]);

                bars_[symbol].push_back(bar);
            }

            std::reverse(bars_[symbol].begin(), bars_[symbol].end());

            csv_file.close();
        } 
    }
}


/**
 * @brief Returns the latest bar for a given symbol.
 * 
 * @param symbol 
 * @return std::vector<Bar> 
 */
std::vector<Bar> HistoricCSVDataHandler::get_latest_bars(const std::string& symbol, int N) {
    std::vector<Bar> bars;
    if(bars_.find(symbol) != bars_.end()) {
        bars = std::vector<Bar>(bars_[symbol].end() - N, bars_[symbol].end());
    }
    return bars;
}



/**
 * @brief Pushes the lastest bar to the latest symbol structure for all symbols in the symbol list.
 * 
 */
void HistoricCSVDataHandler::update_bars() {
    for (auto& symbol : symbol_list_) {
        Bar bar;
        try {
            bar = bars_[symbol].back();
        } catch (std::out_of_range& e) {
            continue_backtest_ = false;
        }
        // TODO: Check if bar is empty
        latest_symbol_data_[symbol].push_back(bar);

    }
    events_->push_back(new MarketEvent());
}


Bar HistoricCSVDataHandler::get_latest_bar_datetime(const std::string& symbol) {
    // if(latest_symbol_data_.find(symbol) != latest_symbol_data_.end()) {
    //     return latest_symbol_data_[symbol].back().datetime;
    // } else {
    //     return "";
    // }
    std::vector<Bar> bars;
    try {
        bars = latest_symbol_data_.at(symbol);
    } catch (std::out_of_range& e) {
        return Bar();
    }
    return bars.back();
}

double HistoricCSVDataHandler::get_latest_bar_value(const std::string& symbol, const std::string& field) {
    if(latest_symbol_data_.find(symbol) != latest_symbol_data_.end()) {
        Bar bar = latest_symbol_data_[symbol].back();
        if(field == "open") {
            return bar.open;
        } else if(field == "high") {
            return bar.high;
        } else if(field == "low") {
            return bar.low;
        } else if(field == "close") {
            return bar.close;
        } else if(field == "adj_close") {
            return bar.adj_close;
        } else if(field == "volume") {
            return bar.volume;
        } else {
            return 0.0;
        }
    } else {
        return 0.0;
    }
}