//
// Created by rwardrup on 9/19/22.
//

#ifndef BUZZBOT_DRINK_H
#define BUZZBOT_DRINK_H

#include <string>
#include "utilities.h"
#include "options.h"

class Drink {
private:
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

    friend class Calculate;
    friend class Database;
    friend auto initStorage(const std::string& file_name, int db_version);

public:
    // Setters
    void set_id(const int &in_id);
    void set_date(const std::string &in_date);
    void set_name(const std::string &in_name);
    void set_type(const std::string &in_type);
    void set_subtype(const std::string &in_subtype);
    void set_producer(const std::string &in_producer);
    void set_abv(const double &in_abv);
    void set_ibu(const double &in_ibu);
    void set_size(const double &in_size);
    void set_rating(const int &in_rating);
    void set_notes(const std::string &in_notes);
    void set_vintage(const int &in_vintage);
    void set_alcohol_type(const std::string &in_alcohol_type);
    void set_timestamp(const std::string &in_timestamp);
    void set_sort_order(const int &in_sort_order);

    // Getters
    int get_id() const;
    std::string get_date() const;
    std::string get_name() const;
    std::string get_type() const;
    std::string get_subtype() const;
    std::string get_producer() const;
    double get_abv() const;
    double get_ibu() const;
    double get_size() const;
    int get_rating() const;
    std::string get_notes() const;
    int get_vintage() const;
    std::string get_alcohol_type() const;
    std::string get_timestamp() const;
    int get_sort_order() const;

    // Methods
    double standard_drinks() const;
    double get_alcohol_volume() const;
};

#endif //BUZZBOT_DRINK_H
