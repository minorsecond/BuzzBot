#!/bin/zsh

VERSION=$(head -n 1 VERS)

echo "Deploying version" $VERSION

echo "Copying BuzzBot.app to desktop."
rm -R ~/Desktop/BuzzBot/
mkdir -p ~/Desktop/BuzzBot/App
cp -R cmake-build-release/BuzzBot.app ~/Desktop/BuzzBot/App/BuzzBot.app

echo "Extracting debug symbols"
dsymutil ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/MacOS/BuzzBot -o ~/Desktop/BuzzBot/BuzzBot.app.dSYM

echo "Running macdeployqt."
macdeployqt ~/Desktop/BuzzBot/App/BuzzBot.app -always-overwrite -appstore-compliant

echo "Configuring plist."
/usr/libexec/PlistBuddy -c "Add :CFBundleSupportedPlatforms array" ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/Info.plist
/usr/libexec/PlistBuddy -c "Add :CFBundleSupportedPlatforms:0 string MacOSX" ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/Info.plist
/usr/libexec/PlistBuddy -c "Add :LSApplicationCategoryType string public.app-category.lifestyle" ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/Info.plist
/usr/libexec/PlistBuddy -c "Add :LSMinimumSystemVersion string 10.15.5" ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/Info.plist

echo "Codesigning."
find ~/Desktop/BuzzBot/App/BuzzBot.app -name "*.dylib" | xargs -I $ codesign --options runtime --verify --verbose --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" $
find ~/Desktop/BuzzBot/App/BuzzBot.app -name "*.framework" | xargs -I $ codesign --options runtime --verify --verbose --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" $
codesign --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" --options runtime --verbose --entitlements BuzzBot-Entitlements.plist ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/MacOS/BuzzBot
codesign --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" --options runtime --verbose --entitlements BuzzBot-Entitlements.plist ~/Desktop/BuzzBot/App/BuzzBot.app

echo "Building pkg."
productbuild --component ~/Desktop/BuzzBot/App/BuzzBot.app /Applications --sign "3rd Party Mac Developer Installer: Robert Wardrup (7KNS6YGX5V)" ~/Desktop/BuzzBot/Buzzbot-Installer.pkg

echo "Deployed. Now verifying installer"
xcrun altool --validate-app -f ~/Desktop/BuzzBot/BuzzBot-Installer.pkg --type osx --primary-bundle-id "com.rwardrup.buzzbot" -u "rosswardrup@hotmail.com" -p "leua-xskx-hcve-tzpz"

echo "Uncomment xcrun altool --upload-app to upload to app store."
#xcrun altool --upload-app --type osx --file ~/Desktop/BuzzBot/Buzzbot-Installer.pkg --primary-bundle-id "com.rwardrup.buzzbot" --username "rosswardrup@hotmail.com" -p "leua-xskx-hcve-tzpz"

#echo "Notarizing app"
#zip ~/Desktop/BuzzBot/BuzzBot.zip -r ~/Desktop/BuzzBot/BuzzBot.app/
#xcrun altool --notarize-app --primary-bundle-id "com.rwardrup.buzzbot.zip" --username "rwardrup" --password "@keychain:AC_PASSWORD" --file ~/Desktop/BuzzBot/BuzzBot.zip