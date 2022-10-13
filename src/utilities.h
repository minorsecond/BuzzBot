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

    static int date_string_to_date_int(const std::string& in_date);

    static void strptime(const char *s, const char *f, struct tm *tm) {
        std::istringstream input(s);
        input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
        input >> std::get_time(tm, f);
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
