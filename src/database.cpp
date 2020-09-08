#include "database.h"
#include "../include/sqlite_orm.h"
#include <CoreServices/CoreServices.h>
#include <sys/stat.h>
#include <sys/types.h>

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
    FSRef ref;
    OSType folderType = kApplicationSupportFolderType;
    char db_path[PATH_MAX];

    FSFindFolder( kUserDomain, folderType, kCreateFolder, &ref );

    FSRefMakePath( &ref, (UInt8*)&db_path, PATH_MAX );

    std::string directory = std::string(db_path);
    directory += "/Alcool";
    std::string full_path = directory += "/alcool.db";

    mkdir(directory.c_str(), 0777);

    return full_path;
}
