#!/bin/zsh

echo "Copying Beertabs.app to desktop."
rm -R ~/Desktop/Beertabs/Beertabs.app
mkdir ~/Desktop/Beertabs
cp -R cmake-build-release/Beertabs.app ~/Desktop/Beertabs/Beertabs.app

echo "Extracting debug symbols"
dsymutil ~/Desktop/Beertabs/Beertabs.app/Contents/MacOS/Beertabs -o ~/Desktop/Beertabs/Beertabs.app.dSYM

echo "Running macdeployqt."
macdeployqt ~/Desktop/Beertabs/Beertabs.app -appstore-compliant

echo "Codesigning."
find ~/Desktop/Beertabs/Beertabs.app -name "*.dylib" | xargs -I $ codesign --options runtime --verify --verbose --sign $1 $
find ~/Desktop/Beertabs/Beertabs.app -name "*.framework" | xargs -I $ codesign --options runtime --verify --verbose --sign $1 $
codesign --sign $1 --options runtime --verbose --entitlements Beertabs-Entitlements.plist ~/Desktop/Beertabs/Beertabs.app

echo "Deployed to ~/Desktop/Beertabs.app"

echo "Notarizing app"
zip ~/Desktop/Beertabs/Beertabs.zip -r ~/Desktop/Beertabs/Beertabs.app/
xcrun altool --notarize-app --primary-bundle-id "com.rwardrup.beertabs.zip" --username "rwardrup" --password "@keychain:AC_PASSWORD" --file ~/Desktop/Beertabs/Beertabs.zip