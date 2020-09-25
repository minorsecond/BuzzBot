//
// Created by Ross Wardrup on 9/24/20.
//

#ifndef BUZZBOT_EXPORTERS_H
#define BUZZBOT_EXPORTERS_H

#include "database.h"

class exporters {
public:
    static void to_csv(const std::vector<Drink>& drinks, const std::string& path);

private:
    static std::vector<std::string> pad_month_day(int month, int day);
};


#endif //BUZZBOT_EXPORTERS_H
