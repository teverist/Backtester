#include <Data/HistoricCSVDataHandler.h>
#include <Utility/Utility.h>
#include <Events/MarketEvent.h>

#include <algorithm>


// HistoricCSVDataHandler::HistoricCSVDataHandler(std::shared_ptr<std::queue<std::shared_ptr<Event>>& events, const std::string& csv_dir, const std::vector<std::string>& symbol_list) :
//     csv_dir_(csv_dir),
//     symbol_list_(symbol_list),
//     events_(events)
// {
//     open_convert_csv_files_();
// }

HistoricCSVDataHandler::HistoricCSVDataHandler(
    std::shared_ptr<std::queue<std::shared_ptr<Event>>>& events, 
    const std::string& csv_dir, 
    const std::vector<std::string>& symbol_list
) :
    csv_dir_(csv_dir),
    symbol_list_(symbol_list),
    events_(events)
{
    open_convert_csv_files_();
}


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
 * @brief Returns the last N bar values from the latest_symbol list, or fewer if less bars are available.
 * 
 * @param symbol 
 * @param field 
 * @param N 
 * @return std::vector<Bar> 
 */
std::vector<Bar> HistoricCSVDataHandler::get_latest_bar_values(const std::string& symbol, const std::string& field, int N) {
    if (N <= 0 || field.empty()) {
        std::cout << "N must be greater than 0 or field must not be empty" << std::endl;
        return {};
    }
    std::vector<Bar> bars;
    if(bars_.find(symbol) != bars_.end()) {
        bars = get_latest_bars(symbol, N);
    } else {
        std::cout << "Symbol " << symbol << " not found in bars" << std::endl;
        return {};
    }
    // Get the bar values

    for(auto& bar : bars) {
        if(field == "open") {
            bar.open = bar.open;
        } else if(field == "high") {
            bar.high = bar.high;
        } else if(field == "low") {
            bar.low = bar.low;
        } else if(field == "close") {
            bar.close = bar.close;
        } else if(field == "adj_close") {
            bar.adj_close = bar.adj_close;
        } else if(field == "volume") {
            bar.volume = bar.volume;
        } else {
            std::cout << "Field " << field << " not found in bar" << std::endl;
            return {};
        }
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
            continue_backtest = false;
        }
        // TODO: Check if bar is empty
        latest_symbol_data_[symbol].push_back(bar);

    }
    events_->push(std::make_shared<MarketEvent>());
}


std::string HistoricCSVDataHandler::get_latest_bar_datetime(const std::string& symbol) {
    std::vector<Bar> bars;
    try {
        bars = latest_symbol_data_.at(symbol);
    } catch (std::out_of_range& e) {
        return ""; // TODO: Fix this
    }
    return bars.back().datetime;
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