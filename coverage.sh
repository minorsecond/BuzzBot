#!/bin/zsh

#
# Generate coverage report for BuzzBot.
#

mkdir ~/Desktop/BuzzBot-Coverage/
rm -rvf ~/Desktop/BuzzBot-Coverage/*
lcov --capture --directory ~/CLionProjects/BuzzBot/cmake-build-debug/CMakeFiles/BuzzBot.dir/src --no-external -o ~/Desktop/BuzzBot-Coverage/coverage.info
lcov -r ~/Desktop/BuzzBot-Coverage/coverage.info "*include*" "*cmake-build*" "*.h" -o ~/Desktop/BuzzBot-Coverage/final_coverage.info
genhtml ~/Desktop/BuzzBot-Coverage/final_coverage.info --output-directory ~/Desktop/BuzzBot-Coverage/