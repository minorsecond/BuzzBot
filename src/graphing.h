//
// Created by Ross Wardrup on 12/7/20.
//

#ifndef BUZZBOT_GRAPHING_H
#define BUZZBOT_GRAPHING_H

#include "database.h"


class graphing {

private:
    std::vector<double> get_beer_ibus(const std::vector<Drink>& all_drinks);
    std::vector<double> get_beer_abvs(const std::vector<Drink>& all_drinks);
};


#endif //BUZZBOT_GRAPHING_H
