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

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-enum-enum-conversion -Wno-error=extra-semi -Wno-error=old-style-cast")

enable_testing()
include_directories(/usr/lib /usr/lib64)
find_package(Qt6 COMPONENTS Core Widgets PrintSupport Gui)

IF( NOT Qt6_FOUND )
    message(STATUS "Could not automatically find Qt6 for ${CMAKE_SYSTEM_NAME}")
    IF(APPLE)
        set(CMAKE_PREFIX_PATH  $ENV{HOME}/Qt/6.2.4/macos/lib/cmake)
    ELSEIF(UNIX AND NOT APPLE)
        SET(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/6.2.4/gcc_64/lib/cmake)
    ENDIF()
    MESSAGE(STATUS ${CMAKE_PREFIX_PATH})
    find_package(Qt6 COMPONENTS Core Widgets PrintSupport Gui REQUIRED)
ENDIF()

find_package(SQLite3 REQUIRED)
find_package(Catch2 3 REQUIRED)

IF(APPLE)
    set(ICON_NAME "icon.icns")
    set(ICON_PATH ${PROJECT_SOURCE_DIR}/res/${ICON_NAME})
    set(buzzbot_ICON ${ICON_PATH})
    set_source_files_properties(${buzzbot_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    file(COPY ${ICON_PATH} DESTINATION "BuzzBot.app/Contents/Resources")
ENDIF()

set(PROJECT_SRC_FILES src/main.cpp src/mainwindow.cpp src/database.cpp
        src/usersettings.cpp src/calculate.cpp src/beer.cpp
        src/liquor.cpp src/wine.cpp src/filters.cpp src/about.cpp src/exporters.cpp
        src/standard_drink_calculator.cpp src/confirm_dialog.cpp
        src/graphing.cpp include/qcustomplot.cpp
        src/table_manipulation.cpp src/stats_updaters.cpp src/utilities.cpp
        src/graphing_calculations.cpp src/drink.cpp
        src/drink_standards.cpp src/options.cpp)

IF(APPLE)
    add_executable(BuzzBot MACOSX_BUNDLE ${ICON_PATH} ${PROJECT_SRC_FILES})
ELSEIF(UNIX AND NOT APPLE)
    add_executable(BuzzBot ${PROJECT_SRC_FILES})
ELSE()
    add_executable(BuzzBot WIN32 ${PROJECT_SRC_FILES})
ENDIF()

add_executable(functions_test src/database.cpp src/database.h src/calculate.cpp src/calculate.h
        test/test_database_functions.cpp test/test_calculations.cpp test/test_graph_calculations.cpp
        src/utilities.cpp src/utilities.h src/drink.h src/graphing_calculations.h src/graphing_calculations.cpp
        src/options.h src/drink.cpp src/drink_standards.h src/drink_standards.cpp src/options.cpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building debug")
    #add_compile_options(-Werror -g -O0 -pedantic)
    # These warnings occur in include files and we don't want to modify them
    add_compile_options(-Wall -Werror -Wextra -g -O0 - pedantic -Wno-error=deprecated-enum-enum-conversion -Wno-error=extra-semi -Wno-error=old-style-cast)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Building release")
    add_compile_options(-Wall -Werror -Wextra -gdwarf-2 -O2 -pedantic -Wno-error=deprecated-enum-enum-conversion -Wno-error=extra-semi -Wno-error=old-style-cast)
endif ()

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
            MACOSX_BUNDLE_BUNDLE_VERSION "v2.4.1"
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_ICON_FILE icon.icns
            MACOSX_BUNDLE_LONG_VERSION_STRING "v2.4.1"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "v2.4.1"
            MACOSX_BUNDLE_COPYRIGHT "2021 Ross Wardrup"
            MACOSX_BUNDLE_GUI_IDENTIFIER com.rwardrup.buzzbot
            XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@loader_path/Libraries"
            XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME TRUE
            XCODE_ATTRIBUTE_EXECUTABLE_NAME "buzzbot")

ELSEIF(WIN32)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/res)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/styles)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/platforms)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/previous.png
            ${CMAKE_CURRENT_BINARY_DIR}/res/previous.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/next.png
            ${CMAKE_CURRENT_BINARY_DIR}/res/next.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/mini-icon.png
            ${CMAKE_CURRENT_BINARY_DIR}/res/mini-icon.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/res/big_sur_icon.png
            ${CMAKE_CURRENT_BINARY_DIR}/res/big_sur_icon.png)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            "C:/msys64/mingw64/share/qt6/plugins/styles/qwindowsvistastyle.dll"
            ${CMAKE_CURRENT_BINARY_DIR}/styles/qwindowsvistastyle.dll)
    add_custom_command(TARGET BuzzBot POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            "C:/msys64/mingw64/share/qt6/plugins/platforms/qwindows.dll"
            ${CMAKE_CURRENT_BINARY_DIR}/platforms/qwindows.dll)
ENDIF()

IF(APPLE)
    set_target_properties(BuzzBot PROPERTIES MACOSX_BUNDLE_ICONFILE ${ICON_NAME})
ENDIF()
target_link_libraries(BuzzBot Qt6::Core Qt6::Widgets Qt6::PrintSupport Qt6::Gui sqlite3)
target_link_libraries(functions_test PRIVATE sqlite3 Catch2::Catch2WithMain Qt6::Core)

IF(UNIX AND NOT APPLE)
    install(CODE "execute_process(COMMAND ../linux_install.sh)")
ENDIF()
include(CTest)
include(Catch)
catch_discover_tests(functions_test)
add_test(NAME functions_test COMMAND functions_test)
