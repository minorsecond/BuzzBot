#!/bin/zsh

echo "INCREMENTING TO VERSION " \"$@\"

sed -i '' -e 's/\(MACOSX_BUNDLE_SHORT_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
sed -i '' -e 's/\(MACOSX_BUNDLE_LONG_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
sed -i '' -e 's/\(std::string version = \)\(.*\)/\1'\"$1\"\;'/' src/about.cpp

# Update Info.plist
defaults write ./Info.plist CFBundleLongVersionString -string "$1"
defaults write ./Info.plist CFBundleShortVersionString -string "$1"
defaults write ./Info.plist CFBundleVersion -string "$1"
