//
// Created by Ross Wardrup on 9/24/20.
//

#ifndef BUZZBOT_EXPORTERS_H
#define BUZZBOT_EXPORTERS_H

#include "database.h"

class exporters {
public:
    static void to_csv(const std::vector<Drink>& drinks, const std::string& path);

};


#endif //BUZZBOT_EXPORTERS_H
