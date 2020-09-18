#ifndef DATABASE_H
#define DATABASE_H

#include "../include/sqlite_orm.h"
#include "iostream"
#include <vector>

struct Drink {  // TODO: Remove brewery in DB version 3/Beertabs v1.0.0
    int id;
    int drink_year;
    int drink_month;
    int drink_day;
    std::string name;
    std::string type;
    std::string subtype;
    std::string brewery;
    std::string producer;
    double abv;
    double ibu;
    int size;
    int rating;
    std::string notes;
    std::string alcohol_type;
    std::string timestamp;
};

inline auto initStorage(const std::string& file_name) {
    std::cout << "Opening or creating DB at " << file_name << std::endl;
    return sqlite_orm::make_storage(file_name,
                                    sqlite_orm::make_table("beers",
                                                          sqlite_orm::make_column("id", &Drink::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                                                          sqlite_orm::make_column("drink_year", &Drink::drink_year),
                                                          sqlite_orm::make_column("drink_month", &Drink::drink_month),
                                                          sqlite_orm::make_column("drink_day", &Drink::drink_day),
                                                          sqlite_orm::make_column("drink_name", &Drink::name),
                                                          sqlite_orm::make_column("drink_type", &Drink::type),
                                                          sqlite_orm::make_column("drink_subtype", &Drink::subtype, sqlite_orm::default_value("")),
                                                          sqlite_orm::make_column("brewery", &Drink::brewery),
                                                          sqlite_orm::make_column("producer", &Drink::producer, sqlite_orm::default_value("")),
                                                          sqlite_orm::make_column("abv", &Drink::abv),
                                                          sqlite_orm::make_column("ibu", &Drink::ibu),
                                                          sqlite_orm::make_column("size", &Drink::size),
                                                          sqlite_orm::make_column("rating", &Drink::rating),
                                                          sqlite_orm::make_column("notes", &Drink::notes),
                                                          sqlite_orm::make_column("alcohol_type", &Drink::alcohol_type, sqlite_orm::default_value("Beer")),
                                                          sqlite_orm::make_column("timestamp", &Drink::timestamp, sqlite_orm::default_value(sqlite_orm::datetime("now", "localtime")))));
}
using Storage = decltype (initStorage(""));

class Database
{
public:
    static std::vector<Drink> read(const std::string& database_path, Storage storage);
    static Storage write(Drink beer, Storage storage);
    static void truncate(Storage storage);
    static void delete_row(Storage storage, int row_num);
    static Drink read_row(int row_num, Storage storage);
    static void update(Storage storage, const Drink& beer);
    static std::vector<Drink> filter(const std::string& filter_type, const std::string& filter_text, Storage storage);
    static void write_db_to_disk(Storage storage);
    static Drink get_drink_by_name(Storage storage, std::string beer_name);
    static std::vector<Drink> get_beers_by_type(Storage storage, std::string beer_type);
    static std::vector<Drink> get_beers_by_brewery(Storage storage, std::string brewery);
    static int get_version(Storage storage);
    static int increment_version(Storage storage, int current_version);
    static void populate_maker_column();

public:
    static std::string path();
};

#endif // DATABASE_H
