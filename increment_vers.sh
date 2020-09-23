#!/bin/zsh

WORKING_DIR=$PWD

echo $WORKING_DIR

echo "INCREMENTING TO VERSION " \"$@\"
sed -i '' -e 's/\(MACOSX_BUNDLE_SHORT_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
sed -i '' -e 's/\(MACOSX_BUNDLE_LONG_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
sed -i '' -e 's/\(MACOSX_BUNDLE_BUNDLE_VERSION \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
sed -i '' -e 's/\(std::string version = \)\(.*\)/\1'\"$1\"\;'/' src/about.cpp

echo "$1" > VERS

echo "Refresh CMake to apply changes to Info.plist"