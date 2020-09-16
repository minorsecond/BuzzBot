#!/bin/zsh

macdeployqt cmake-build-release/Beertabs.app -appstore-compliant

echo "USING CERTIFICATE " $1

find cmake-build-release/Beertabs.app -name "*.dylib" | xargs -I $ codesign --force --verify --verbose --sign $1 $
find cmake-build-release/Beertabs.app -name "*.framework" | xargs -I $ codesign --force --verify --verbose --sign $1 $
codesign -fs $1 --entitlements Beertabs-Entitlements.plist cmake-build-release/Beertabs.app
