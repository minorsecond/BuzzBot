//
// Created by Ross Wardrup on 12/7/20.
//

#ifndef BUZZBOT_GRAPHING_H
#define BUZZBOT_GRAPHING_H

#include "database.h"


class Graphing {

public:
    static std::vector<double> get_beer_ibus(const std::vector<Drink>& all_drinks);
    static std::vector<double> get_drink_abvs(const std::vector<Drink>& all_drinks);
};


#endif //BUZZBOT_GRAPHING_H
