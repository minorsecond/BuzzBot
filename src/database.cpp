#include "database.h"
#include <boost/filesystem.hpp>
#include <utility>
#include <iostream>
#include <QStandardPaths>

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

std::vector<Drink> Database::read(const std::string& database_path, Storage storage) {
    /*
     * Read all rows from the database.
     * @return all_beers A vector containing Drink, storing all rows in the database.
     */

    std::vector<Drink> all_beers = storage.get_all<Drink>();

    return all_beers;
}

void Database::write_db_to_disk(Storage storage) {
    /*
     * Flush in-memory database data to disk.
     */

    storage.sync_schema(true);
}

Storage Database::write(Drink beer, Storage storage) {
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
     * @return beer: The results of the database query.
     */
    
    Drink beer = storage.get<Drink>(row_num);
    return beer;
}

void Database::update(Storage storage, const Drink& beer) {
    /*
     * Update a specific database row.
     * @param storage: A storage instance.
     * @param beer: The row to update. The ID of the beer must match the internal primary key on the DB.
     */

    storage.update(beer);
}

std::string Database::get_latest_notes(Storage storage, const std::string& name, const std::string& alcohol_type) {
    /*
     * Get the last notes entered for a drink.
     * @param storage: A Storage instance.
     * @param name: Name of alcohol to retrieve notes for.
     * @param alcohol_type: Type of alcohol that Name is.
     * @return notes: A string containing notes entered for the name and alcohol type.
     */

    std::vector<Drink> drinks = storage.get_all<Drink>(where(c(&Drink::name) == name && c(&Drink::alcohol_type) == alcohol_type));
    std::string notes;
    unsigned temp_id = 0;
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
    } else if (filter_type == "Date") {
        int year = stoi(filter_text.substr(6, 8));
        int month = stoi(filter_text.substr(3, 2));
        int day = stoi(filter_text.substr(0, 2));

        std::cout << "*** Query year: " << year << ", query month: " << month << ", query day: " << day << std::endl;
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::drink_year) == year && c(&Drink::drink_month) == month &&
                                                      c(&Drink::drink_day) == day));
    } else if (filter_type == "After Date") {
        //int year = stoi(filter_text.substr(6, 8));
        //int month = stoi(filter_text.substr(3, 2));
        //int day = stoi(filter_text.substr(0, 2));

        //filtered_drinks = storage.get_all<Drink>(where(c(&Drink::drink_year) == year && c(&Drink::drink_month) == month &&
        //                                              c(&Drink::drink_day) >= day));

        std::cout << "Filter date: " << filter_text << std::endl;
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::date) >= filter_text));
        std::cout << "Size of filtered drinks: " << filtered_drinks.size() << std::endl;

    } else if (filter_type == "Rating") {
        filtered_drinks = storage.get_all<Drink>(where(c(&Drink::rating) == filter_text));
    } else {
        filtered_drinks = storage.get_all<Drink>();
    }

    return filtered_drinks;
}

Drink Database::get_drink_by_name(Storage storage, std::string alcohol_type, std::string beer_name) {
    /*
     * Get a drink by its name.
     * @param storage: A Storage instance
     * @param drink_name: Name of drink to query
     * @return drink_by_name: A Drink matching the name.
     */

    // TODO: Filter by alcohol_type that should be passed in by selected tabwidget tab
    std::vector<Drink> drink_by_name_result = storage.get_all<Drink>(where(c(&Drink::name) == std::move(beer_name) && c(&Drink::alcohol_type) == std::move(alcohol_type)));
    Drink drink_by_name;

    if (!drink_by_name_result.empty()) {
        drink_by_name = drink_by_name_result.at(0);
    } else {
        drink_by_name.id = -1;
    }

    return drink_by_name;
}

std::vector<Drink> Database::get_beers_by_type(Storage storage, std::string beer_type) {
    std::vector<Drink> beers_by_type = storage.get_all<Drink>(where(c(&Drink::type) == std::move(beer_type)));
    return beers_by_type;
}

std::vector<Drink> Database::get_beers_by_brewery(Storage storage, std::string producer) {
    std::vector<Drink> beers_by_brewery = storage.get_all<Drink>(where(c(&Drink::producer) == std::move(producer)));
    return beers_by_brewery;
}

int Database::get_version(Storage storage) {
    return storage.pragma.user_version();
}

int Database::increment_version(Storage storage, int current_version) {
    /*
     * Increment database version to current version.
     */

    std::cout << "Using DB version " << storage.pragma.user_version() << std::endl;

    if (get_version(storage) < 5 && current_version == 5) {
        // This adds the year, month, day fields into the date field in the correct format.
        std::cout << "*** Upgrading DB from version " << storage.pragma.user_version() <<  " to 5." << std::endl;
        populate_date_field();
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

    if (a.drink_year < b.drink_year) {
        return true;
    } else if (a.drink_year == b.drink_year && a.drink_month < b.drink_month) {
        return true;
    } else if (a.drink_year == b.drink_year && a.drink_month == b.drink_month && a.drink_day < b.drink_day) {
        return true;
    } else if (a.drink_year == b.drink_year && a.drink_month == b.drink_month && a.drink_day == b.drink_day && a.id < b.id) {
        return true;
    } else {
        return false;
    }
}

std::vector<Drink> Database::sort_by_date_id(std::vector<Drink> drinks) {
    /*
     * Adds a sort column integer to database.
     */

    // First sort by entered date
    std::sort(drinks.begin(), drinks.end(), compare_date);

    // Now add sort order value
    int sort_order = 1;
    for (int i = 0; i < drinks.size(); ++i) {
        drinks[i].sort_order = sort_order;
        sort_order++;
    }

    return drinks;
}

void Database::populate_date_field() {
    /*
     * Convert the year, month, and date fields to the date field.
     */

    Storage storage = initStorage(path());
    write_db_to_disk(storage);
    std::vector all_drinks = storage.get_all<Drink>();
    for (auto& drink : all_drinks) {
        std::ostringstream month_padded;
        std::ostringstream day_padded;
        month_padded << std::setw(2) << std::setfill('0') << drink.drink_month;
        day_padded << std::setw(2) << std::setfill('0') << drink.drink_day;
        std::string formatted_date = std::to_string(drink.drink_year) + "-" + month_padded.str() + "-" + day_padded.str();
        drink.date = formatted_date;
        std::cout << "Formatted date: " << formatted_date << std::endl;
        update(storage, drink);
    }
}