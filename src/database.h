#ifndef DATABASE_H
#define DATABASE_H

#include "../include/sqlite_orm.h"
#include <vector>
#include <QDate>

struct Drink {
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
};

inline auto initStorage(const std::string& file_name, int db_version) {
    /*
     * Initialize the DB
     */

    std::string table_name = "beers";
    // Set table name based on DB version
    if (db_version > 7) {
        table_name = "drinks";
    }

    return sqlite_orm::make_storage(file_name,
                                    sqlite_orm::make_table(table_name,
                                                          sqlite_orm::make_column("id", &Drink::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                                                          sqlite_orm::make_column("date", &Drink::date, sqlite_orm::default_value("2020-01-01")),
                                                          sqlite_orm::make_column("drink_name", &Drink::name),
                                                          sqlite_orm::make_column("drink_type", &Drink::type),
                                                          sqlite_orm::make_column("drink_subtype", &Drink::subtype, sqlite_orm::default_value("")),
                                                          sqlite_orm::make_column("producer", &Drink::producer, sqlite_orm::default_value("")),
                                                          sqlite_orm::make_column("abv", &Drink::abv),
                                                          sqlite_orm::make_column("ibu", &Drink::ibu),
                                                          sqlite_orm::make_column("_size", &Drink::_size, sqlite_orm::default_value(0.0)),
                                                          sqlite_orm::make_column("rating", &Drink::rating),
                                                          sqlite_orm::make_column("notes", &Drink::notes),
                                                          sqlite_orm::make_column("vintage", &Drink::vintage, sqlite_orm::default_value(-999)),
                                                          sqlite_orm::make_column("alcohol_type", &Drink::alcohol_type, sqlite_orm::default_value("Beer")),
                                                          sqlite_orm::make_column("timestamp", &Drink::timestamp, sqlite_orm::default_value(sqlite_orm::datetime("now", "localtime")))));
}
using Storage = decltype (initStorage("", -1));

class Database
{
public:
    static const int db_version {8};
    static std::vector<Drink> read(Storage storage);
    static Storage write(Drink drink, Storage storage);
    static void truncate(Storage storage);
    static void delete_row(Storage &storage, const int &row_num);
    static Drink read_row(const int &row_num, Storage &storage);
    static void update(Storage storage, const Drink& drink);
    static std::vector<Drink> filter(const std::string& filter_type, const std::string& filter_text, Storage storage);
    static void write_db_to_disk(Storage &storage);
    static Drink get_drink_by_name(Storage &storage, const std::string &alcohol_type, const std::string &drink_name);
    static Drink get_drink_by_name(Storage &storage, const std::string &alcohol_type, const std::string &drink_name, const std::string &producer);
    static std::vector<Drink> get_drinks_by_type(Storage storage, std::string drink_type);
    static std::vector<Drink> get_drinks_by_producer(Storage storage, std::string producer);
    static int get_version(Storage storage);
    static int increment_version(Storage storage, int current_version);
    static void sort_by_date_id(std::vector<Drink> &drinks);
    static std::string get_latest_notes(Storage &storage, const std::string& name, const std::string& alcohol_type);

private:
    static bool compare_date(const Drink &a, const Drink &b);
    static void populate_size_field();

public:
    static std::string path();
};

#endif // DATABASE_H
