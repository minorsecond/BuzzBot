#!/bin/zsh

macdeployqt cmake-build-release/Beertabs.app -appstore-compliant

echo "USING CERTIFICATE " $1

find cmake-build-release/Beertabs.app -name "*.dylib" | xargs -I $ codesign --verify --verbose --sign $1 $
find cmake-build-release/Beertabs.app -name "*.framework" | xargs -I $ codesign --verify --verbose --sign $1 $
codesign --sign $1 --verbose --entitlements Beertabs-Entitlements.plist cmake-build-release/Beertabs.app
