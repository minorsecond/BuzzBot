<img src="https://github.com/minorsecond/BuzzBot/blob/master/res/mini-icon.png" align="right"
     alt="BuzzBot Logo" width="100" height="100">
     
# BuzzBot
## Track your consumption of your favorite alcoholic drinks
It is estimated that [1 in 8 deaths of those between 20-64 years of age is attributable to excessive alcohol use.](https://jamanetwork.com/journals/jamanetworkopen/fullarticle/2798004?utm_campaign=articlePDF&utm_medium=articlePDFlink&utm_source=articlePDF&utm_content=jamanetworkopen.2022.39485)
Keeping tabs on how much alcohol you consume is essential for your health, and BuzzBot makes it easy to do.
Simply log your drink and BuzzBot will display how many standard drinks you've consumed, and how close you are to the
healthy limit. BuzzBot even features graphs and reports! You can visualize your alcohol consumption over time, and you
can use the reports feature to see what drinks you have rated highest.

### Build Status
| Branch  | macOS Build Status                                                                                                                      | Linux Build Status                                                                                                                                    | Windows Build Status                                                                                                                                      | Code Review                                                                                                                                                                                                                 |
|---------|-----------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| master  | [![Actions Status](https://github.com/minorsecond/BuzzBot/workflows/Master/badge.svg)](https://github.com/minorsecond/BuzzBot/actions)  | [![Build Status](https://ci.wardrup.me/buildStatus/icon?job=BuzzBot-Master-PRMerge-Linux)](https://ci.wardrup.me/job/BuzzBot-Master-PRMerge-Linux/)   | [![Build Status](https://ci.wardrup.me/buildStatus/icon?job=BuzzBot-MasterPRMerge-Windows)](https://ci.wardrup.me/job/BuzzBot-Master-PRMerge-Windows/)    | [![CodeFactor](https://www.codefactor.io/repository/github/minorsecond/buzzbot/badge/master?s=7d0189852bedaddcb41bc7579892f35d6cca05b3)](https://www.codefactor.io/repository/github/minorsecond/buzzbot/overview/master)   |
| develop | [![Actions Status](https://github.com/minorsecond/BuzzBot/workflows/Develop/badge.svg)](https://github.com/minorsecond/BuzzBot/actions) | [![Build Status](https://ci.wardrup.me/buildStatus/icon?job=BuzzBot-Develop-PRMerge-Linux)](https://ci.wardrup.me/job/BuzzBot-Develop-PRMerge-Linux/) | [![Build Status](https://ci.wardrup.me/buildStatus/icon?job=BuzzBot-Develop-PRMerge-Windows)](https://ci.wardrup.me/job/BuzzBot-Develop-PRMerge-Windows/) | [![CodeFactor](https://www.codefactor.io/repository/github/minorsecond/buzzbot/badge/develop?s=7d0189852bedaddcb41bc7579892f35d6cca05b3)](https://www.codefactor.io/repository/github/minorsecond/buzzbot/overview/develop) |

### Keep track of:
- Your favorite drinks
- Your favorite alcohol producers
- Number of standard drinks consumed for the week
- Number of standard drinks left for the weeks
- Average ABV & IBU per drink
- Drink notes
- Graphs

---------

<p align="center">
BuzzBot on KDE Plasma

![BuzzBot on KDE](res/buzzbot_kde.png?raw=true)

</p>

<p align="center">
BuzzBot on macOS

![BuzzBot on macOS](res/buzzbot_macOS.png?raw=true)
</p>

<p align="center">
BuzzBot on Windows

![BuzzBot on Windows](res/buzzbot_windows.png?raw=true)
</p>
---------

### Installation instructions
- `git clone https://github.com/minorsecond/BuzzBot.git`
- `cd BuzzBot`
- `mkdir build && cd build`
- `cmake -DCMAKE_BUILD_TYPE=Release ..` If you'd like to build the app custom for your CPU, run
`cmake -DCMAKE_BUILD_TYPE=RelLocalCpu`
- `cmake --build . --target BuzzBot`. If you want to run tests, run `cmake --build . --target functions_test`.
- If you're running macOS, you'll have a `BuzzBot.app` file in the `build` directory.
- If you're running Linux, you can install the app in `~/.local/bin` by running `cmake --install .`.
  The app should then be available in your app menu.
- If using a Samba share in Linux to share your database across multiple devices, be sure to add the
  `nobrl` mount option for the share that the DB file will reside on. This prevents your SMB client from sending byte
  range locks to the server. Without this addition, you will get a locked database error.

### Developing BuzzBot
- Dependencies:
    - Qt 6.2.4
    - G++11
    - Boost 1.79 or greater
    - Sqlite3
    - Catch2 (3.0 or greater)
- CLion is the preferred IDE, but you can obviously use anything.
- Please run unit tests after making your changes. A CI system is in place to protect against bad PRs but you will save yourself time by doing so.
