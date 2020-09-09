cmake_minimum_required(VERSION 3.17)
project(Beertabs)

set(CMAKE_CXX_STANDARD 20)

set(LIBPROC_SRC "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libproc.h")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

enable_testing()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Boost COMPONENTS filesystem)
find_package(Catch2 REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(ICON_NAME "icon.icns")
set(ICON_PATH ${PROJECT_SOURCE_DIR}/res/${ICON_NAME})
set(beertabs_ICON ${ICON_PATH})
set_source_files_properties(${beertabs_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
file(COPY ${ICON_PATH} DESTINATION "Beertabs.app/Contents/Resources")

add_executable(Beertabs MACOSX_BUNDLE ${ICON_PATH} src/main.cpp src/mainwindow.cpp src/database.cpp src/mainwindow.h src/database.h)
add_executable(functions_test src/database.cpp src/database.h test/test-main.cpp test/test_database_functions.cpp)

set_target_properties(Beertabs PROPERTIES MACOSX_BUNDLE_ICONFILE ${ICON_NAME})
target_link_libraries(Beertabs Qt5::Core Qt5::Widgets SQLite3 Boost::filesystem)
target_link_libraries(functions_test SQLite3 Boost::filesystem)
include(CTest)
#include(ParseAndCatchTests)
#ParseAndAddCatchTests(functions_test)