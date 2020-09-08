#include "database.h"
#include "../include/sqlite_orm.h"
#include <CoreServices/CoreServices.h>
#include <boost/filesystem.hpp>

//Database::Database()
//{
//}

std::vector<Beer> Database::read() {
    std::string database_path = Database::path();
    std::cout << "Reading or building the database at " << database_path << std::endl;
    Storage storage = initStorage(database_path);
    std::vector<Beer> all_beers = storage.get_all<Beer>();

    return all_beers;
}

void Database::write_db_to_disk(Storage storage) {
    storage.sync_schema(false);
}

std::string Database::path() {

    // Find path to application support directory
    FSRef ref;
    OSType folderType = kApplicationSupportFolderType;
    char db_path[PATH_MAX];

    FSFindFolder( kUserDomain, folderType, kCreateFolder, &ref );

    FSRefMakePath( &ref, (UInt8*)&db_path, PATH_MAX );

    // Create db path
    std::string directory = std::string(db_path);
    directory += "/Beertabs";
    //directory = "/Users/rwardrup/Desktop/Beertabs";

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
