#ifndef BAR_H
#define BAR_H

#include <string>

class Bar
{
public:
    std::string datetime;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adj_close;
};

#endif // BAR_H