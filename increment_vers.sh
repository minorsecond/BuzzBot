#!/bin/zh

echo "INCREMENTING TO VERSION " $1

sed 's/\(MACOSX_BUNDLE_SHORT_VERSION_STRING \)\(.*\)/\1$1/' CMakeLists.txt
sed 's/\(MACOSX_BUNDLE_LONG_VERSION_STRING \)\(.*\)/\1$1/' CMakeLists.txt
sed 's/\(std::string version = \)\(.*\)/\1$1/' src/about.cpp