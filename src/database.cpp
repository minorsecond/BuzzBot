#include "database.h"
#include <boost/filesystem.hpp>
using namespace sqlite_orm;
std::string Database::path() {
    /*
     * Find database path and create it if it doens't exist.
     * @return full_path Path where database file should be stored.
     */
    // Find path to application support directory

    std::string username = getenv("USER");
    std::string directory = "/Users/" + username + "/Library/Application Support/Beertabs";

    // Remove spaces from path
    directory.erase(std::remove_if(
            begin(directory), end(directory),
            [l = std::locale{}](auto ch) {return std::isspace(ch, l);}),
                    end(directory));

    std::string full_path = directory + "/beertabs.db";

    boost::filesystem::create_directory(directory);

    return full_path;
}

std::vector<Beer> Database::read(const std::string& database_path, Storage storage) {
    /*
     * Read all rows from the database.
     * @return all_beers A vector containing Beer, storing all rows in the database.
     */

    std::cout << "Reading or building the database at " << database_path << std::endl;
    std::vector<Beer> all_beers = storage.get_all<Beer>();

    return all_beers;
}

void Database::write_db_to_disk(Storage storage) {
    /*
     * Flush in-memory database data to disk.
     */

    storage.sync_schema(false);
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
    } else if (filter_type == "Brewery") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::brewery) == filter_text));
    } else if (filter_type == "Date") {
        int year = stoi(filter_text.substr(6, 8));
        int month = stoi(filter_text.substr(3, 2));
        int day = stoi(filter_text.substr(0, 2));

        filtered_beers = storage.get_all<Beer>(where(c(&Beer::drink_year) == year && c(&Beer::drink_month) == month &&
                c(&Beer::drink_day) == day));
    } else if (filter_type == "Rating") {
        filtered_beers = storage.get_all<Beer>(where(c(&Beer::rating) == filter_text));
    } else {
        filtered_beers = storage.get_all<Beer>();
    }

    return filtered_beers;
}

