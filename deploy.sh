#!/bin/zsh

echo "Copying Beertabs.app to desktop."
rm -R ~/Desktop/Beertabs.app
cp -R cmake-build-release/Beertabs.app ~/Desktop/Beertabs.app

echo "Running macdeployqt."
macdeployqt ~/Desktop/Beertabs.app -appstore-compliant

echo "Codesigning."
find ~/Desktop/Beertabs.app -name "*.dylib" | xargs -I $ codesign --verify --verbose --sign $1 $
find ~/Desktop/Beertabs.app -name "*.framework" | xargs -I $ codesign --verify --verbose --sign $1 $
codesign --sign $1 --options runtime --verbose --entitlements Beertabs-Entitlements.plist ~/Desktop/Beertabs.app

echo "Deployed to ~/Desktop/Beertabs.app"