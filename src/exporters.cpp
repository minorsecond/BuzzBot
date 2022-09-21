//
// Created by Ross Wardrup on 9/24/20.
//

#include "exporters.h"
#include "calculate.h"
#include <fstream>

/*
 * Keep an eye on this code as it was previously causing crashes (exc_bad_access).
 * I think the issue was due to using ostringstream to add padding to the month & date
 * digits in to_csv().
 *
*/

void exporters::to_csv(const std::vector<Drink> &drinks, const std::string &path, const std::string& units) {
    /*
     * Creates a CSV file containing the current DB contents.
     * @param drinks: A vector of Drinks.
     * @param path: Path where CSV should be saved.
     */

    std::ofstream output_csv(path);

    const std::string size_header = (units == "Metric") ? "Size (ml)," : "Size (oz),";

    // Create the header
    output_csv << "Date,";
    output_csv << "Name,";
    output_csv << "Type,";
    output_csv << "Subtype,";
    output_csv << "Producer,";
    output_csv << "Vintage,";
    output_csv << "ABV,";
    output_csv << "IBU,";
    output_csv << size_header;
    output_csv << "Rating,";
    output_csv << "Notes,";
    output_csv << "Alcohol Type,";
    output_csv << "Timestamp,";
    output_csv << "ID\n";

    for (const auto& drink : drinks) {
        const std::string ibu = (drink.get_ibu() == -1) ? "" : std::to_string(drink.get_ibu());
        const std::string vintage = (drink.get_vintage() == -999) ? "" : std::to_string(drink.get_vintage());

        const std::string drink_name = '"' + drink.get_name() + '"';
        const std::string drink_type = '"' + drink.get_type() + '"';
        const std::string drink_subtype = '"' + drink.get_subtype() + '"';
        const std::string drink_producer = '"' + drink.get_producer() + '"';
        const std::string drink_notes = '"' + drink.get_notes() + '"';

        // Convert size to ml if metric option is selected
        const std::string size = (units == "Metric") ? std::to_string(Calculate::oz_to_ml(drink.get_size())) :
                std::to_string(drink.get_size());

        output_csv << drink.get_date() + ",";
        output_csv << drink_name + ",";
        output_csv << drink_type + ",";
        output_csv << drink_subtype + ",";
        output_csv << drink_producer + ",";
        output_csv << vintage + ",";
        output_csv << std::to_string(drink.get_abv()) + ",";
        output_csv << ibu + ",";
        output_csv << size + ",";
        output_csv << std::to_string(drink.get_rating()) + ",";
        output_csv << drink_notes + ",";
        output_csv << drink.get_alcohol_type() + ",";
        output_csv << drink.get_timestamp() + ",";
        output_csv << std::to_string(drink.get_id()) + "\n";
    }

    output_csv.close();
}