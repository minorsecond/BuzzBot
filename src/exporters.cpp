//
// Created by Ross Wardrup on 9/24/20.
//

#include "exporters.h"
#include "fstream"

/*
 * Keep an eye on this code as it was previously causing crashes (exc_bad_access).
 * I think the issue was due to using ostringstream to add padding to the month & date
 * digits in to_csv().
 *
*/

void exporters::to_csv(const std::vector<Drink> &drinks, const std::string &path) {
    /*
     * Creates a CSV file containing the current DB contents.
     * @param drinks: A vector of Drinks.
     * @param path: Path where CSV should be saved.
     */

    std::ofstream output_csv(path);

    // Create the header
    output_csv << "Date,";
    output_csv << "Name,";
    output_csv << "Type,";
    output_csv << "Subtype,";
    output_csv << "Producer,";
    output_csv << "Vintage,";
    output_csv << "ABV,";
    output_csv << "IBU,";
    output_csv << "Size,";
    output_csv << "Rating,";
    output_csv << "Notes,";
    output_csv << "Alcohol Type,";
    output_csv << "Timestamp,";
    output_csv << "ID\n";

    for (const auto& drink : drinks) {
        std::string ibu = (drink.ibu == -1) ? "" : std::to_string(drink.ibu);
        std::string vintage = (drink.vintage == -999) ? "" : std::to_string(drink.vintage);

        // TODO: sanitize string formatting, deal with commas, tabs, etc.
        std::string drink_name = '"' + drink.name + '"';
        std::string drink_type = '"' + drink.type + '"';
        std::string drink_subtype = '"' + drink.subtype + '"';
        std::string drink_producer = '"' + drink.producer + '"';
        std::string drink_notes = '"' + drink.notes + '"';

        output_csv << drink.date + ",";
        output_csv << drink_name + ",";
        output_csv << drink_type + ",";
        output_csv << drink_subtype + ",";
        output_csv << drink_producer + ",";
        output_csv << vintage + ",";
        output_csv << std::to_string(drink.abv) + ",";
        output_csv << ibu + ",";
        output_csv << std::to_string(drink._size) + ",";
        output_csv << std::to_string(drink.rating) + ",";
        output_csv << drink_notes + ",";
        output_csv << drink.alcohol_type + ",";
        output_csv << drink.timestamp + ",";
        output_csv << std::to_string(drink.id) + "\n";
    }

    output_csv.close();
}