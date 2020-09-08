#include "database.h"
#include <boost/filesystem.hpp>

std::vector<Beer> Database::read() {
    /*
     * Read all rows from the database.
     * @return all_beers A vector containing Beer, storing all rows in the database.
     */

    std::string database_path = Database::path();
    std::cout << "Reading or building the database at " << database_path << std::endl;
    Storage storage = initStorage(database_path);
    std::vector<Beer> all_beers = storage.get_all<Beer>();

    return all_beers;
}

void Database::write_db_to_disk(Storage storage) {
    /*
     * Flush in-memory database data to disk.
     */

    storage.sync_schema(false);
}

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

    std::cout << "Creating app support directory: " << directory << std::endl;
    std::string full_path = directory + "/beertabs.db";

    boost::filesystem::create_directory(directory);

    return full_path;
}
