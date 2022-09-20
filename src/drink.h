//
// Created by rwardrup on 9/19/22.
//

#ifndef BUZZBOT_DRINK_H
#define BUZZBOT_DRINK_H

#include <string>

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

public:
    // Setters
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
    std::string get_date();
    std::string get_name();
    std::string get_type();
    std::string get_subtype();
    std::string get_producer();
    double get_abv();
    double get_ibu();
    double get_size();
    int get_rating();
    std::string get_notes();
    int get_vintage();
    std::string get_alcohol_type();
    std::string get_timestamp();
    int get_sort_order();
};

#endif //BUZZBOT_DRINK_H
