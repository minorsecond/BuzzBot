cmake_minimum_required(VERSION 3.17)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(BuzzBot)
set(LIBPROC_SRC "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libproc.h")
#set(Qt6_DIR "/Users/rwardrup/Qt/6.0.0/clang_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "/Users/rwardrup/Qt/6.0.0/clang_64/")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building debug")
    add_compile_options(-Wall -Werror -Wextra -g -o0 -pedantic)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Building release")
    add_compile_options(-Wall -Werror -Wextra -gdwarf-2 -o3 -pedantic)
endif ()

enable_testing()

find_package(Qt6 COMPONENTS Core Widgets PrintSupport Gui REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Catch2 REQUIRED)

set(ICON_NAME "icon.icns")
set(ICON_PATH ${PROJECT_SOURCE_DIR}/res/${ICON_NAME})
set(buzzbot_ICON ${ICON_PATH})
set_source_files_properties(${buzzbot_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
file(COPY ${ICON_PATH} DESTINATION "BuzzBot.app/Contents/Resources")

add_executable(BuzzBot MACOSX_BUNDLE ${ICON_PATH} src/main.cpp src/mainwindow.cpp src/database.cpp src/mainwindow.h
        src/database.h src/usersettings.cpp src/usersettings.h src/calculate.cpp src/calculate.h src/beer.cpp
        src/liquor.cpp src/wine.cpp src/filters.cpp  src/about.cpp src/about.h src/exporters.cpp src/exporters.h
        src/standard_drink_calculator.cpp src/standard_drink_calculator.h src/confirm_dialog.cpp src/confirm_dialog.h
        src/graphing.cpp src/graphing.h include/qcustomplot.h include/qcustomplot.cpp
        src/table_manipulation.cpp src/stats_updaters.cpp)
add_executable(functions_test src/database.cpp src/database.h src/calculate.cpp src/calculate.h test/test-main.cpp
        test/test_database_functions.cpp test/test_calculations.cpp test/test_graph_calculations.cpp src/graphing.cpp
        src/graphing.h include/qcustomplot.cpp include/qcustomplot.h)

target_precompile_headers(BuzzBot PRIVATE include/sqlite_orm.h)

# Copy resources to build dir
add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/previous.png
        ${CMAKE_CURRENT_BINARY_DIR}/BuzzBot.app/Contents/Resources/previous.png)
add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/next.png
        ${CMAKE_CURRENT_BINARY_DIR}/BuzzBot.app/Contents/Resources/next.png)
add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/mini-icon.png
        ${CMAKE_CURRENT_BINARY_DIR}/BuzzBot.app/Contents/Resources/mini-icon.png)

set_target_properties(BuzzBot PROPERTIES MACOSX_BUNDLE_ICONFILE ${ICON_NAME})
target_link_libraries(BuzzBot Qt6::Core Qt6::Widgets Qt6::PrintSupport Qt6::Gui SQLite3 "-framework CoreFoundation")
target_link_libraries(functions_test SQLite3 Catch2::Catch2 Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport)

set_target_properties(BuzzBot PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "BuzzBot"
        MACOSX_BUNDLE_BUNDLE_VERSION "2.0.0"
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE icon.icns
        MACOSX_BUNDLE_LONG_VERSION_STRING "2.0.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "2.0.0"
        MACOSX_BUNDLE_COPYRIGHT "2021 Ross Wardrup"
        MACOSX_BUNDLE_GUI_IDENTIFIER com.rwardrup.buzzbot
        XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@loader_path/Libraries"
        XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME TRUE
        XCODE_ATTRIBUTE_EXECUTABLE_NAME "buzzbot")

include(CTest)
include(Catch)
catch_discover_tests(functions_test)
add_test(NAME functions_test COMMAND functions_test)
