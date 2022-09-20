//
// Created by rwardrup on 9/20/22.
//

#include "drink.h"

void Drink::set_date(const std::string &in_date) {
    /*
     * Set drink date.
     * @param date: Date in YYYY-MM-DD format.
     * @return: None.
     */

    date = in_date;
}

void Drink::set_name(const std::string &in_name) {
    /*
     * Set drink name.
     * @param in_name: drink name.
     * @return: None
     */

    name = in_name;
}

void Drink::set_type(const std::string &in_type) {
    /*
     * Set drink type.
     * @param in_type: Drink type.
     * @return: None
     */

    type = in_type;
}

void Drink::set_subtype(const std::string &in_subtype) {
    /*
     * Set drink subtype.
     * @param in_subtype: Drink subtype.
     * @return: None
     */

    subtype = in_subtype;
}

void Drink::set_producer(const std::string &in_producer) {
    /*
     * Set drink producer.
     * @param in_producer: Drink producer
     * @return: None
     */

    producer = in_producer;
}

void Drink::set_abv(const double &in_abv) {
    /*
     * Set drink ABV.
     * @param in_abv: Drink ABV.
     * @return: None
     */

    abv = in_abv;
}

void Drink::set_ibu(const double &in_ibu) {
    /*
     * Set beer IBU.
     * @param in_ibu: Drink IBU
     * @return: None
     */

    ibu = in_ibu;
}

void Drink::set_size(const double &in_size) {
    /*
     * Set drink size.
     * @param in_size: Drink size
     * @return: None
     */

    _size = in_size; // TODO: Rename _size to size
}

void Drink::set_rating(const int &in_rating) {
    /*
     * Set drink rating.
     * @param in_rating: Drink rating.
     * @return: none
     */

    rating = in_rating;
}

void Drink::set_notes(const std::string &in_notes) {
    /*
     * Set drink notes.
     * @param in_notes: Drink notes.
     * @return: None
     */

    notes = in_notes;
}

void Drink::set_vintage(const int &in_vintage) {
    /*
     * Set drink vintage.
     * @param in_vintage: Drink vintage.
     * @return: None
     */

    vintage = in_vintage;
}

void Drink::set_alcohol_type(const std::string &in_alcohol_type) {
    /*
     * Set drink alcohol type.
     * @param in_alcohol_type: drink alcohol type.
     * @return: None
     */

    alcohol_type = in_alcohol_type;
}

void Drink::set_timestamp(const std::string &in_timestamp) {
    /*
     * Set drink timestamp.
     * @param in_timestamp: drink timestamp.
     * @return: None
     */

    timestamp = in_timestamp;
}

void Drink::set_sort_order(const int &in_sort_order) {
    /*
     * Set table sort order.
     * @param sort_order: Order to be sorted in table.
     * @return: None
     */

    sort_order = in_sort_order;
}

std::string Drink::get_date() {
    /*
     * Get drink date
     * @return: Drink date
     */
    return date;
}

std::string Drink::get_name() {
    /*
     * Get drink name.
     * @return: Drink name.
     */
    return name;
}

std::string Drink::get_type() {
    /*
     * Get drink type.
     * @return: Drink type.
     */
    return type;
}

std::string Drink::get_subtype() {
    /*
     * Get drink subtype.
     * @return: Drink subtype.
     */
    return subtype;
}

std::string Drink::get_producer() {
    /*
     * Get drink producer.
     * @return: Drink producer.
     */
    return producer;
}

double Drink::get_abv() {
    /*
     * Get drink ABV
     * @return: Drink ABV
     */
    return abv;
}

double Drink::get_ibu() {
    /*
     * Get drink IBU
     * @return: Drink IBU
     */
    return ibu;
}

double Drink::get_size() {
    /*
     * Get drink size
     * @return: Drink size
     */
    return _size;
}

int Drink::get_rating() {
    /*
     * Get drink rating
     * @return: Drink rating.
     */
    return rating;
}

std::string Drink::get_notes() {
    /*
     * Get drink notes
     * @return: Drink notes
     */
    return notes;
}

int Drink::get_vintage() {
    /*
     * Get drink vintage.
     * @return: drink vintage
     */
    return vintage;
}

std::string Drink::get_alcohol_type() {
    /*
     * Get alcohol type.
     * @return: Alcohol type
     */
    return alcohol_type;
}

std::string Drink::get_timestamp() {
    /*
     * Get drink timestamp.
     * @return: drink timestamp
     */
    return timestamp;
}

int Drink::get_sort_order() {
    /*
     * Get drink sort order.
     * @return: Sort order
     */
    return sort_order;
}
