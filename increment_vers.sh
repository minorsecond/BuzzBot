#!/bin/zsh

#
# This script increments the version number to whatever is entered after the ./increment_vers.sh command.
# The version can never be decremented, and the script will do nothing if the new version is the same as the previous.
#

# Parse date
VERS_LINE=$(tail -n 1 VERS)
PREV_VER=$(tail -n 1 VERS | awk '{print $1;}')
DATE=$(date +"%Y-%m-%d-%H-%M-%S")

# Get previous major, minor, patch
PREV_MAJ=`echo $PREV_VER | cut -d. -f1`
PREV_MINOR=`echo $PREV_VER | cut -d. -f2`
PREV_PATCH=`echo $PREV_VER | cut -d. -f3`

# Get new major, minor, patch
NEW_MAJ=`echo $1 | cut -d. -f1`
NEW_MINOR=`echo $1 | cut -d. -f2`
NEW_PATCH=`echo $1 | cut -d. -f3`

NEW_VERS="$1"

# Check if it's possible to increment version
if [[ $PREV_MAJ -lt $NEW_MAJ || $PREV_MINOR -lt $NEW_MINOR || $PREV_PATCH -lt $NEW_PATCH ]];
then
  echo "Incrementing to version " "$1"
  sed -i '' -e 's/\(MACOSX_BUNDLE_SHORT_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
  sed -i '' -e 's/\(MACOSX_BUNDLE_LONG_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
  sed -i '' -e 's/\(MACOSX_BUNDLE_BUNDLE_VERSION \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
  sed -i '' -e 's/\(std::string version = \)\(.*\)/\1'\"$1\"\;'/' src/about.cpp

  echo "$1" $DATE >> VERS

  echo "Incremented version " $PREV_VER " to " $1
  echo "Refresh CMake to apply changes to Info.plist."

elif [[ $PREV_MAJ -eq $NEW_MAJ && $PREV_MINOR -eq $NEW_MINOR && $PREV_PATCH -eq $NEW_PATCH && $NEW_VERS != *"beta"* && $VERS_LINE == *"beta"* ]]
then
  echo "Upgrading from beta version to " "$1"
  sed -i '' -e 's/\(MACOSX_BUNDLE_SHORT_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
  sed -i '' -e 's/\(MACOSX_BUNDLE_LONG_VERSION_STRING \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
  sed -i '' -e 's/\(MACOSX_BUNDLE_BUNDLE_VERSION \)\(.*\)/\1'\"$1\"'/' CMakeLists.txt
  sed -i '' -e 's/\(std::string version = \)\(.*\)/\1'\"$1\"\;'/' src/about.cpp

  echo "$1" $DATE >> VERS

  echo "Incremented version " "$PREV_VER" " to " "$1"
  echo "Refresh CMake to apply changes to Info.plist."

elif [[ $PREV_MAJ -eq $NEW_MAJ && $PREV_MINOR -eq $NEW_MINOR && $PREV_PATCH -eq $NEW_PATCH ]];
then
  echo "Versions are the same. Nothing to do."
elif [[ $PREV_MAJ -gt $NEW_MAJ || $PREV_MINOR -gt $NEW_MINOR || $PREV_PATCH -gt $NEW_PATCH ]];
then
  echo "Previous verison is greater than new version. Not changing version."
else
  echo "An error occured."
fi