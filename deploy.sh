#!/bin/zsh

echo "Copying BuzzBot.app to desktop."
rm -R ~/Desktop/BuzzBot/
mkdir -p ~/Desktop/BuzzBot/App
cp -R cmake-build-release/BuzzBot.app ~/Desktop/BuzzBot/App/BuzzBot.app

echo "Extracting debug symbols"
dsymutil ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/MacOS/BuzzBot -o ~/Desktop/BuzzBot/BuzzBot.app.dSYM

echo "Running macdeployqt."
macdeployqt ~/Desktop/BuzzBot/App/BuzzBot.app -always-overwrite -appstore-compliant

echo "Codesigning with ID " DIST_ID
find ~/Desktop/BuzzBot/App/BuzzBot.app -name "*.dylib" | xargs -I $ codesign --options runtime --verify --verbose --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" $
find ~/Desktop/BuzzBot/App/BuzzBot.app -name "*.framework" | xargs -I $ codesign --options runtime --verify --verbose --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" $
codesign --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" --options runtime --verbose --entitlements BuzzBot-Entitlements.plist ~/Desktop/BuzzBot/App/BuzzBot.app/Contents/MacOS/BuzzBot
codesign --sign "3rd Party Mac Developer Application: Robert Wardrup (7KNS6YGX5V)" --options runtime --verbose --entitlements BuzzBot-Entitlements.plist ~/Desktop/BuzzBot/App/BuzzBot.app

pkgbuild --analyze --root ~/Desktop/BuzzBot/App/ ~/Desktop/BuzzBot/Components.plist
pkgbuild --root ~/Desktop/BuzzBot/App/ --identifier "com.rwardrup.buzzbot" --component-plist ~/Desktop/BuzzBot/Components.plist ~/Desktop/BuzzBot/Buzzbot.app.pkg
productbuild --synthesize --package ~/Desktop/BuzzBot/Buzzbot.app.pkg ~/Desktop/BuzzBot/Distribution.xml
productbuild --distribution ~/Desktop/BuzzBot/Distribution.xml --sign "3rd Party Mac Developer Installer: Robert Wardrup (7KNS6YGX5V)" --package-path ~/Desktop/BuzzBot ~/Desktop/BuzzBot/Buzzbot-Installer.pkg
productbuild --component ~/Desktop/BuzzBot/App/BuzzBot.app /Applications --sign "3rd Party Mac Developer Installer: Robert Wardrup (7KNS6YGX5V)" ~/Desktop/BuzzBot/Buzzbot-Installer.pkg

echo "Deployed to ~/Desktop/BuzzBot.app"
xcrun altool --validate-app -f ~/Desktop/BuzzBot/BuzzBot-Installer.pkg --type osx --primary-bundle-id "com.rwardrup.buzzbot" -u "rosswardrup@hotmail.com" -p "leua-xskx-hcve-tzpz"

#echo "Notarizing app"
#zip ~/Desktop/BuzzBot/BuzzBot.zip -r ~/Desktop/BuzzBot/BuzzBot.app/
#xcrun altool --notarize-app --primary-bundle-id "com.rwardrup.buzzbot.zip" --username "rwardrup" --password "@keychain:AC_PASSWORD" --file ~/Desktop/BuzzBot/BuzzBot.zip