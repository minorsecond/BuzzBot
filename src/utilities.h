//
// Created by Ross Wardrup on 9/28/21.
//

#ifndef BUZZBOT_UTILITIES_H
#define BUZZBOT_UTILITIES_H

#include <string>
#include <time.h>
#include <iomanip>
#include <sstream>

#ifdef __WIN32
    #include <windows.h>
#endif

class utilities {
public:
    static std::string zero_pad_string(unsigned integer);

    static std::string get_local_date();

    static std::string get_home_path();

    static double get_std_drink_size();

    static std::string get_application_data_path();

    static bool file_exists(const std::string &path);

    static std::string get_db_path();

    static std::string settings_path();

    static char* strptime(const char* s,
                              const char* f,
                              struct tm* tm) {
        // Isn't the C++ standard lib nice? std::get_time is defined such that its
        // format parameters are the exact same as strptime. Of course, we have to
        // create a string stream first, and imbue it with the current C locale, and
        // we also have to make sure we return the right things if it fails, or
        // if it succeeds, but this is still far simpler an implementation than any
        // of the versions in any of the C standard libraries.
        std::istringstream input(s);
        input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
        input >> std::get_time(tm, f);
        if (input.fail()) {
            return nullptr;
        }
        return (char*)(s + input.tellg());
    }

#ifdef __WIN32
    static std::string exe_path() {
        TCHAR buffer[MAX_PATH] = { 0 };
        GetModuleFileName( NULL, buffer, MAX_PATH );
        std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
        std::wstring ws(std::wstring(buffer).substr(0, pos));
        std::string str(ws.begin(), ws.end());
        return str;
    }
#endif
};


#endif //BUZZBOT_UTILITIES_H
