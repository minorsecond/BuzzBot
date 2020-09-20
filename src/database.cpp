#include "database.h"
#include <boost/filesystem.hpp>
#include <utility>
#include <QStandardPaths>
#include <QDebug>

using namespace sqlite_orm;
std::string Database::path() {
    /*
     * Find database path and create it if it doesn't exist.
     * @return full_path Path where database file should be stored.
     */
    // Find path to application support directory

    std::string directory = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0).toStdString();
    std::string full_path = directory + "/buzzbot.db";
    boost::filesystem::create_directory(directory);

    return full_path;
}

std::vector<Beer> Database::read(const std::string& database_path, Storage storage) {
    /*
     * Read all rows from the database.
     * @return all_beers A vector containing Beer, storing all rows in the database.
     */

    std::vector<Beer> all_beers = storage.get_all<Beer>();

    return all_beers;
}

void Database::write_db_to_disk(Storage storage) {
    /*
     * Flush in-memory database data to disk.
     */
    std::cout << "Writing data to disk" << std::endl;
    storage.sync_schema(true);
}

Storage Database::write(Beer beer, Storage storage) {
    /*
     * Write a row to the SQLite database.
     * @param beer: a beer
     * @return Storage: The storage instance
     */

    std::string database_path = path();
    int inserted_id = storage.insert(beer);
    beer.id = inserted_id;
    write_db_to_disk(storage);

    return storage;
}

void Database::truncate(Storage storage) {
    /*
     * Delete all rows from the sqlite database while retaining columns.
     * @param storage: a storage instance.
     */

    storage.remove_all<Beer>();
    write_db_to_disk(storage);
}

void Database::delete_row(Storage storage, int row_num) {
    /*
     * Delete a specific row from the database.
     * @param storage: A storage instance
     * @param row_num: Integer denoting row number to delete. This corresponds to DB primary key.
     */

    storage.remove<Beer>(row_num);
}

Beer Database::read_row(int row_num, Storage storage) {
    /*
     * Read a specific row from the database.
     * @param storage: A storage instance.
     * @param row_num: The row number that should be read.
     * @return beer: The results of the database query.
     */
    
    Beer beer = storage.get<Beer>(row_num);
    return beer;
}

void Database::update(Storage storage, const Beer& beer) {
    /*
     * Update a specific database row.
     * @param storage: A storage instance.
     * @param beer: The row to update. The ID of the beer must match the internal primary key on the DB.
     */

    storage.update(beer);
}

std::vector<Beer> Database::filter(const std::string& filter_type, const std::string& filter_text, Storage storage) {
    /*
     * Retrieve DB rows based on filter column and text.
     * @param filter_type: Column on which to filter.
     * @param filter_text: Text to search columns for.
     * @param storage: A storage instance.
     * @return filtered_beers: The results of the database query.
     */

    std::vector<Beer> filtered_beers;

    // Filter by name
    if (filter_type == "Name") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::name) == filter_text));
    } else if (filter_type == "Type") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::type) == filter_text));
    } else if (filter_type == "Subtype") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::subtype) == filter_text));
    } else if (filter_type == "Brewery") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::brewery) == filter_text));
    } else if (filter_type == "Date") {
        int year = stoi(filter_text.substr(6, 8));
        int month = stoi(filter_text.substr(3, 2));
        int day = stoi(filter_text.substr(0, 2));
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::drink_year) == year && c(&Beer::drink_month) == month &&
                c(&Beer::drink_day) == day));
    } else if (filter_type == "After Date") {
        int year = stoi(filter_text.substr(6, 8));
        int month = stoi(filter_text.substr(3, 2));
        int day = stoi(filter_text.substr(0, 2));

        filtered_beers = storage.get_all<Beer>(where(c(&Beer::drink_year) == year && c(&Beer::drink_month) == month &&
                                                     c(&Beer::drink_day) >= day));

    } else if (filter_type == "Rating") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::rating) == filter_text));
    } else {
        filtered_beers = storage.get_all<Beer>();
    }

    return filtered_beers;
}

Beer Database::get_beer_by_name(Storage storage, std::string beer_name) {
    Beer beer_by_name = storage.get_all<Beer>(where(c(&Beer::name) == std::move(beer_name))).at(0);
    return beer_by_name;
}

std::vector<Beer> Database::get_beers_by_type(Storage storage, std::string beer_type) {
    std::vector<Beer> beers_by_type = storage.get_all<Beer>(where(c(&Beer::type) == std::move(beer_type)));
    return beers_by_type;
}

std::vector<Beer> Database::get_beers_by_brewery(Storage storage, std::string brewery) {
    std::vector<Beer> beers_by_brewery = storage.get_all<Beer>(where(c(&Beer::brewery) == std::move(brewery)));
    return beers_by_brewery;
}

int Database::get_version(Storage storage) {
    std::cout << "Current DB version: " << storage.pragma.user_version() << std::endl;
    return storage.pragma.user_version();
}

int Database::increment_version(Storage storage, int current_version) {
    /*
     * Increment database version to current version.
     */

    if (get_version(storage) == 0) {  // Never use 0
        storage.pragma.user_version(storage.pragma.user_version() + 1);
        storage.sync_schema(true);
        std::cout << "Migrated DB from version 0 to version " << storage.pragma.user_version() << std::endl;
    }
    return storage.pragma.user_version();
}
