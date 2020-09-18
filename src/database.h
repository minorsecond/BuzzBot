#ifndef DATABASE_H
#define DATABASE_H

#include "../include/sqlite_orm.h"
#include "iostream"
#include <vector>

struct Beer {
    int id;
    int drink_year;
    int drink_month;
    int drink_day;
    std::string name;
    std::string type;
    std::string subtype;
    std::string brewery;
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
                                                          sqlite_orm::make_column("id", &Beer::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                                                          sqlite_orm::make_column("drink_year", &Beer::drink_year),
                                                          sqlite_orm::make_column("drink_month", &Beer::drink_month),
                                                          sqlite_orm::make_column("drink_day", &Beer::drink_day),
                                                          sqlite_orm::make_column("drink_name", &Beer::name),
                                                          sqlite_orm::make_column("drink_type", &Beer::type),
                                                          sqlite_orm::make_column("drink_subtype", &Beer::subtype, sqlite_orm::default_value("")),
                                                          sqlite_orm::make_column("brewery", &Beer::brewery),
                                                          sqlite_orm::make_column("abv", &Beer::abv),
                                                          sqlite_orm::make_column("ibu", &Beer::ibu),
                                                          sqlite_orm::make_column("size", &Beer::size),
                                                          sqlite_orm::make_column("rating", &Beer::rating),
                                                          sqlite_orm::make_column("notes", &Beer::notes),
                                                          sqlite_orm::make_column("alcohol_type", &Beer::alcohol_type, sqlite_orm::default_value("")),
                                                          sqlite_orm::make_column("timestamp", &Beer::timestamp, sqlite_orm::default_value(sqlite_orm::datetime("now", "localtime")))));
}
using Storage = decltype (initStorage(""));

class Database
{
public:
    static std::vector<Beer> read(const std::string& database_path, Storage storage);
    static Storage write(Beer beer, Storage storage);
    static void truncate(Storage storage);
    static void delete_row(Storage storage, int row_num);
    static Beer read_row(int row_num, Storage storage);
    static void update(Storage storage, const Beer& beer);
    static std::vector<Beer> filter(const std::string& filter_type, const std::string& filter_text, Storage storage);
    static void write_db_to_disk(Storage storage);
    static Beer get_beer_by_name(Storage storage, std::string beer_name);
    static std::vector<Beer> get_beers_by_type(Storage storage, std::string beer_type);
    static std::vector<Beer> get_beers_by_brewery(Storage storage, std::string brewery);
    static int get_version(Storage storage);
    static int increment_version(Storage storage, int current_version);

public:
    static std::string path();
};

#endif // DATABASE_H
