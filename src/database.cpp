#include "database.h"
#include <utility>
#include <iostream>
#include <QStandardPaths>
#include <filesystem>

using namespace sqlite_orm;
std::string Database::path() {
    /*
     * Find database path and create it if it doesn't exist.
     * @return full_path Path where database file should be stored.
     */

    // Find path to application support directory
    std::string directory = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0).toStdString();
    std::string full_path = directory + "/buzzbot.db";
    std::filesystem::create_directory(directory);

    std::cout << "Using DB located at " << full_path << std::endl;

    return full_path;
}

std::vector<Drink> Database::read(Storage storage) {
    /*
     * Read all rows from the database.
     * @return all_drinks A vector containing Drink, storing all rows in the database.
     */

    std::vector<Drink> all_drinks = storage.get_all<Drink>();

    return all_drinks;
}

void Database::write_db_to_disk(Storage storage) {
    /*
     * Flush in-memory database data to disk.
     */

    storage.sync_schema(true);
}

Storage Database::write(Drink drink, Storage storage) {
    /*
     * Write a row to the SQLite database.
     * @param drink: a drink
     * @return Storage: The storage instance
     */

    std::string database_path = path();
    int inserted_id = storage.insert(drink);
    drink.id = inserted_id;
    write_db_to_disk(storage);

    return storage;
}

void Database::truncate(Storage storage) {
    /*
     * Delete all rows from the sqlite database while retaining columns.
     * @param storage: a storage instance.
     */

    storage.remove_all<Drink>();
    write_db_to_disk(storage);
}

void Database::delete_row(Storage storage, int row_num) {
    /*
     * Delete a specific row from the database.
     * @param storage: A storage instance
     * @param row_num: Integer denoting row number to delete. This corresponds to DB primary key.
     */

    storage.remove<Drink>(row_num);
}

Drink Database::read_row(int row_num, Storage storage) {
    /*
     * Read a specific row from the database.
     * @param storage: A storage instance.
     * @param row_num: The row number that should be read.
     * @return drink: The results of the database query.
     */
    
    auto drink = storage.get<Drink>(row_num);
    return drink;
}

void Database::update(Storage storage, const Drink& drink) {
    /*
     * Update a specific database row.
     * @param storage: A storage instance.
     * @param drink: The row to update. The ID of the drink must match the internal primary key on the DB.
     */

    storage.update(drink);
}

std::string Database::get_latest_notes(Storage storage, const std::string& name, const std::string& alcohol_type) {
    /*
     * Get the last notes entered for a drink.
     * @param storage: A Storage instance.
     * @param name: Name of alcohol to retrieve notes for.
     * @param alcohol_type: Type of alcohol that Name is.
     * @return notes: A string containing notes entered for the name and alcohol type.
     */

    // TODO: Get notes based on primary key
    std::vector<Drink> drinks = storage.get_all<Drink>(where(c(&Drink::name) == name && c(&Drink::alcohol_type) == alcohol_type));
    std::string notes;
    int temp_id = 0;
    for (const auto& drink_for_notes : drinks) {
        if (drink_for_notes.id > temp_id && drink_for_notes.alcohol_type == alcohol_type) {
            temp_id = drink_for_notes.id;
            if (!drink_for_notes.notes.empty()) {
                notes = drink_for_notes.notes;
            }
        }
    }

    return notes;
}


std::vector<Drink> Database::filter(const std::string& filter_type, const std::string& filter_text, Storage storage) {
    /*
     * Retrieve DB rows based on filter column and text.
     * @param filter_type: Column on which to filter.
     * @param filter_text: Text to search columns for.
     * @param storage: A storage instance.
     * @return filtered_drinks: The results of the database query.
     */

    std::vector<Drink> filtered_drinks;

    // Filter by name
    if (filter_type == "Name") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::name) == filter_text));
    } else if (filter_type == "Type") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::type) == filter_text));
    } else if (filter_type == "Subtype") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::subtype) == filter_text));
    } else if (filter_type == "Producer") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::producer) == filter_text));
    } else if (filter_type == "Alcohol Type") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::alcohol_type) == filter_text));
    } else if (filter_type == "After Date") {
        std::cout << "Filter date: " << filter_text << std::endl;
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::date) >= filter_text));

    } else if (filter_type == "Rating") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::rating) == filter_text));
    } else if (filter_type == "Name & Producer") {
        // Parse the -- (PRODUCER) text to strip out drink name and producer.
        std::string producer_name {filter_text.substr(filter_text.find(" -- (") + 5)};
        producer_name = producer_name.substr(0, producer_name.size() - 1);
        std::string drink_name {filter_text.substr(0, filter_text.find(" -- ("))};
        std::cout << drink_name << " " << producer_name << std::endl;
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::name) == drink_name and c(&Drink::producer) == producer_name));
    } else {
        filtered_drinks = storage.get_all<Drink>();
    }

    return filtered_drinks;
}

Drink Database::get_drink_by_name(Storage storage, std::string alcohol_type, std::string drink_name) {
    /*
     * Get a drink by its name.
     * @param storage: A Storage instance
     * @param drink_name: Name of drink to query
     * @return drink_by_name: A Drink matching the name.
     */

    std::vector<Drink> drink_by_name_result = storage.get_all<Drink>(where(c(&Drink::name) ==
            std::move(drink_name) && c(&Drink::alcohol_type) == std::move(alcohol_type)));
    Drink drink_by_name;

    std::sort(drink_by_name_result.begin(), drink_by_name_result.end(), compare_date);

    if (!drink_by_name_result.empty()) {
        drink_by_name = drink_by_name_result.at(drink_by_name_result.size() - 1);
    } else {
        drink_by_name.id = -1;
    }

    return drink_by_name;
}
Drink Database::get_drink_by_name(Storage storage, std::string alcohol_type, std::string drink_name, std::string producer) {
    /*
     * Overloaded get_drink_by_name method that gets a drink by name and producer, if provided.
     * @param storage: a Storage instance
     * @param drink_name: name of drink to query
     * @param alcohol_type: The alcohol type to query
     * @param producer: The drink producer
     */

    std::vector<Drink> drink_by_name_result = storage.get_all<Drink>(where(c(&Drink::name)
            == std::move(drink_name) && c(&Drink::alcohol_type) == std::move(alcohol_type) &&
            c(&Drink::producer) == std::move(producer)));
    Drink drink_by_name;

    std::sort(drink_by_name_result.begin(), drink_by_name_result.end(), compare_date);

    if (!drink_by_name_result.empty()) {
        drink_by_name = drink_by_name_result.at(drink_by_name_result.size() - 1);
    } else {
        drink_by_name.id = -1;
    }

    return drink_by_name;
}

std::vector<Drink> Database::get_drinks_by_type(Storage storage, std::string drink_type) {
    /*
     * Get drinks by type.
     * @param storage: A storage instance.
     * @param drink_type: The type of drink to filter on.
     * @return: A vector of drinks that match drink_type.
     */
    std::vector<Drink> drinks_by_type = storage.get_all<Drink>(where(c(&Drink::type) == std::move(drink_type)));
    return drinks_by_type;
}

std::vector<Drink> Database::get_drinks_by_producer(Storage storage, std::string producer) {
    /*
     * Get drinks by producer.
     * @param storage: A storage instance.
     * @param producer: The producer name to filter on.
     * @return: A vector of drinks produced by a producer.
     */
    std::vector<Drink> drinks_by_producer = storage.get_all<Drink>(where(c(&Drink::producer) == std::move(producer)));
    return drinks_by_producer;
}

int Database::get_version(Storage storage) { // NOLINT(performance-unnecessary-value-param)
    /*
     * Get the current database version.
     * @param storage: A storage instance.
     * @return: An integer denoting the current database version.
     */
    return storage.pragma.user_version();
}

int Database::increment_version(Storage storage, int current_version) {
    /*
     * Increment database version to current version.
     * @param storage: A storage instance.
     * @param current_version: The version that the DB should be incremented to.
     * @return: An integer denoting new DB version, straight from the DB.
     */

    std::cout << "Using DB version " << storage.pragma.user_version() << std::endl;
    int version = get_version(storage);
    if (version < 8 && current_version == 8) {
        std::cout << "*** Upgrading DB from version " << storage.pragma.user_version() <<  " to " << current_version << std::endl;

        if (version != 0) {  // DB will be version 0 if app is a new install, so table will not be called beers.
            storage.rename_table("beers", "drinks");
        }
        // Set to new version number
        storage.pragma.user_version(current_version);
        storage.sync_schema(true);
    }
    return storage.pragma.user_version();
}

bool Database::compare_date(const Drink &a, const Drink &b) {
    /*
     * Determine if second date is greater than the first date.
     * @return: True if second date is more recent than the first date. Else, false.
     */

    int a_year = std::stoi(a.date.substr(0, 4));
    int a_month = std::stoi(a.date.substr(5, 7));
    int a_day = std::stoi(a.date.substr(8, 9));
    int b_year = std::stoi(b.date.substr(0, 4));
    int b_month = std::stoi(b.date.substr(5, 7));
    int b_day = std::stoi(b.date.substr(8, 9));

    if (a_year < b_year) {
        return true;
    } else if (a_year == b_year) {
        if (a_month < b_month) {
            return true;
        } else if (a_month == b_month && a_day < b_day) {
            return true;
        } else if (a_month == b_month && a_day == b_day && a.id < b.id) {
            return true;
        }
    }
    // Else:
    return false;
}

void Database::sort_by_date_id(std::vector<Drink> &drinks) {
    /*
     * Adds a sort column integer to database.
     */

    // First sort by entered date
    std::sort(drinks.begin(), drinks.end(), compare_date);
    // Now add sort order value
    int sort_order = 1;
    for (unsigned i = 0; i < drinks.size(); ++i) { // NOLINT(modernize-loop-convert)
        drinks[i].sort_order = sort_order;
        sort_order++;
    }
}
