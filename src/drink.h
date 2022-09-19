//
// Created by rwardrup on 9/19/22.
//

#ifndef BUZZBOT_DRINK_H
#define BUZZBOT_DRINK_H

#include <string>

struct Drink {
    int id;
    std::string date;
    std::string name;
    std::string type;
    std::string subtype;
    std::string producer;
    double abv;
    double ibu;
    double _size;  // TODO: Rename to size
    int rating;
    std::string notes;
    int vintage;
    std::string alcohol_type;
    std::string timestamp;
    int sort_order;
};

#endif //BUZZBOT_DRINK_H
