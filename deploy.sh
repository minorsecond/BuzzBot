#!/bin/zsh

echo "Copying BuzzBot.app to desktop."
rm -R ~/Desktop/BuzzBot/BuzzBot.app
mkdir ~/Desktop/BuzzBot
cp -R cmake-build-release/BuzzBot.app ~/Desktop/BuzzBot/BuzzBot.app

echo "Extracting debug symbols"
dsymutil ~/Desktop/BuzzBot/BuzzBot.app/Contents/MacOS/BuzzBot -o ~/Desktop/BuzzBot/BuzzBot.app.dSYM

echo "Running macdeployqt."
macdeployqt ~/Desktop/BuzzBot/BuzzBot.app -appstore-compliant

echo "Codesigning with ID " DIST_ID
find ~/Desktop/BuzzBot/BuzzBot.app -name "*.dylib" | xargs -I $ codesign --options runtime --verify --verbose --sign $DIST_ID $
find ~/Desktop/BuzzBot/BuzzBot.app -name "*.framework" | xargs -I $ codesign --options runtime --verify --verbose --sign $DIST_ID $
codesign --sign $DIST_ID --options runtime --verbose --entitlements BuzzBot-Entitlements.plist ~/Desktop/BuzzBot/BuzzBot.app

echo "Deployed to ~/Desktop/BuzzBot.app"

echo "Notarizing app"
zip ~/Desktop/BuzzBot/BuzzBot.zip -r ~/Desktop/BuzzBot/BuzzBot.app/
xcrun altool --notarize-app --primary-bundle-id "com.rwardrup.buzzbot.zip" --username "rwardrup" --password "@keychain:AC_PASSWORD" --file ~/Desktop/BuzzBot/BuzzBot.zip