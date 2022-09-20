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
    void set_date(std::string date);
    void set_name(std::string name);
    void set_type(std::string type);
    void set_subtype(std::string subtype);
    void set_producer(std::string producer);
    void set_abv(double abv);
    void set_ibu(double ibu);
    void set_size(double size);
    void set_rating(int rating);
    void set_notes(std::string notes);
    void set_vintage(int vintage);
    void set_alcohol_type(std::string alcohol_type);
    void set_timestamp(std::string timestamp);
    void set_sort_order(int sort_order);

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
