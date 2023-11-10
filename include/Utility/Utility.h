#ifndef UTILITY_H
#define UTILITY_H


#include <string>
#include <vector>
#include <sstream>


namespace Utility {

std::vector<std::string> split(std::string str, char delimiter) {
    std::stringstream ss(str);

    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


} // namespace utility


#endif // UTILITY_H


