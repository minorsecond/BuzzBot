#!/bin/bash

echo "Moving binary"
mkdir -p ~/.local/bin/
cp BuzzBot ~/.local/bin/

echo "Setting up icons"
mkdir -p ~/.local/share/icons/buzzbot
cp ../res/big_sur_icon.png ~/.local/share/icons/buzzbot
cp ../res/previous.png ~/.local/share/icons/buzzbot
cp ../res/next.png ~/.local/share/icons/buzzbot

echo "Setting up .desktop file"
cp ../res/buzzbot.desktop ~/.local/share/applications/buzzbot.desktop
