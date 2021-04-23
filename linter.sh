cppcheck --enable=all --suppress=missingIncludeSystem --check-config --suppress='*:include/date.h*' src/mainwindow.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/database.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/calculate.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/table_manipulation.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/stats_updaters.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/filters.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/exporters.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/about.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/beer.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/confirm_dialog.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/liquor.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/usersettings.cpp
cppcheck --enable=all --suppress=missingIncludeSystem --check-config src/wine.cpp