IF(APPLE)
    message(STATUS "Building for Apple")
ELSEIF(UNIX AND NOT APPLE)
    message(STATUS "Building for Linux")
endif()
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
IF(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")
    set(LIBPROC_SRC "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libproc.h")
ENDIF()
project(BuzzBot)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building debug")
    add_compile_options(-Wall -Werror -Wextra -g -O0 -pedantic)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Building release")
    add_compile_options(-Wall -Werror -Wextra -gdwarf-2 -O2 -pedantic)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-enum-enum-conversion")

enable_testing()
include_directories(/usr/lib /usr/lib64)
find_package(Qt6 COMPONENTS Core Widgets PrintSupport Gui)

IF( NOT Qt6_FOUND )
    message(STATUS "Could not automatically find Qt6 for ${CMAKE_SYSTEM_NAME}")
    IF(APPLE)
        message(STATUS "Searching for Qt in home directory")
        set(CMAKE_PREFIX_PATH  $ENV{HOME}/Qt/6.3.2/macos/lib/cmake)
    ELSEIF(UNIX AND NOT APPLE)
        SET(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/6.3.2/gcc_64/lib/cmake)
    ENDIF()
    MESSAGE(STATUS ${CMAKE_PREFIX_PATH})
    find_package(Qt6 COMPONENTS Core Widgets PrintSupport Gui REQUIRED)
ENDIF()

find_package(SQLite3 REQUIRED)
find_package(Catch2 3 REQUIRED)
find_package(Boost REQUIRED)

IF(APPLE)
    set(ICON_NAME "icon.icns")
    set(ICON_PATH ${PROJECT_SOURCE_DIR}/res/${ICON_NAME})
    set(buzzbot_ICON ${ICON_PATH})
    set_source_files_properties(${buzzbot_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    file(COPY ${ICON_PATH} DESTINATION "BuzzBot.app/Contents/Resources")
ENDIF()

add_executable(BuzzBot MACOSX_BUNDLE ${ICON_PATH} src/main.cpp src/mainwindow.cpp src/database.cpp src/mainwindow.h
        src/database.h src/usersettings.cpp src/usersettings.h src/calculate.cpp src/calculate.h src/beer.cpp
        src/liquor.cpp src/wine.cpp src/filters.cpp  src/about.cpp src/about.h src/exporters.cpp src/exporters.h
        src/standard_drink_calculator.cpp src/standard_drink_calculator.h src/confirm_dialog.cpp src/confirm_dialog.h
        src/graphing.cpp src/graphing.h include/qcustomplot.h include/qcustomplot.cpp
        src/table_manipulation.cpp src/stats_updaters.cpp src/utilities.cpp src/utilities.h)
add_executable(functions_test src/database.cpp src/database.h src/calculate.cpp src/calculate.h
        test/test_database_functions.cpp test/test_calculations.cpp test/test_graph_calculations.cpp src/graphing.cpp
        src/graphing.h include/qcustomplot.cpp include/qcustomplot.h src/utilities.cpp src/utilities.h)

target_precompile_headers(BuzzBot PRIVATE include/sqlite_orm.h)

IF(APPLE)
    # Copy resources to build dir
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/previous.png
            ${CMAKE_CURRENT_BINARY_DIR}/BuzzBot.app/Contents/Resources/previous.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/next.png
            ${CMAKE_CURRENT_BINARY_DIR}/BuzzBot.app/Contents/Resources/next.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/mini-icon.png
            ${CMAKE_CURRENT_BINARY_DIR}/BuzzBot.app/Contents/Resources/mini-icon.png)

    set_target_properties(BuzzBot PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "BuzzBot"
            MACOSX_BUNDLE_BUNDLE_VERSION "2.2.1"
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_ICON_FILE icon.icns
            MACOSX_BUNDLE_LONG_VERSION_STRING "2.2.1"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "2.2.1"
            MACOSX_BUNDLE_COPYRIGHT "2021 Ross Wardrup"
            MACOSX_BUNDLE_GUI_IDENTIFIER com.rwardrup.buzzbot
            XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@loader_path/Libraries"
            XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME TRUE
            XCODE_ATTRIBUTE_EXECUTABLE_NAME "buzzbot")
ELSEIF(UNIX AND NOT APPLE)
    file(MAKE_DIRECTORY $ENV{HOME}/.local/share/com.rwardrup.buzzbot)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/previous.png
            $ENV{HOME}/.local/share/icons/com.rwardrup.buzzbot/previous.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/next.png
            $ENV{HOME}/.local/share/icons/com.rwardrup.buzzbot/next.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/mini-icon.png
            $ENV{HOME}/.local/share/icons/com.rwardrup.buzzbot/mini-icon.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/big_sur_icon.png
            $ENV{HOME}/.local/share/icons/big_sur_icon.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/buzzbot.desktop
            $ENV{HOME}/.local/share/applications/buzzbot.desktop)
ENDIF()

IF(APPLE)
    set_target_properties(BuzzBot PROPERTIES MACOSX_BUNDLE_ICONFILE ${ICON_NAME})
ENDIF()
target_link_libraries(BuzzBot Qt6::Core Qt6::Widgets Qt6::PrintSupport Qt6::Gui sqlite3)
target_link_libraries(functions_test PRIVATE sqlite3 Catch2::Catch2WithMain Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport)

IF(UNIX AND NOT APPLE)
    #install(TARGETS BuzzBot DESTINATION bin)
    install(CODE "execute_process(COMMAND ../linux_install.sh)")
ENDIF()
include(CTest)
include(Catch)
catch_discover_tests(functions_test)
add_test(NAME functions_test COMMAND functions_test)
