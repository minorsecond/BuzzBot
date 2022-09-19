<img src="https://github.com/minorsecond/BuzzBot/blob/master/res/mini-icon.png" align="right"
     alt="BuzzBot Logo" width="100" height="100">
     
# BuzzBot
## Track your consumption of your favorite alcoholic drinks
### Build Status
| Branch  | macOS Build Status                                                                                                                      | Linux Build Status                                                                                                        | Code Review                                                                                                                                                                                                                 |
|---------|-----------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| master  | [![Actions Status](https://github.com/minorsecond/BuzzBot/workflows/Master/badge.svg)](https://github.com/minorsecond/BuzzBot/actions)  | [![Build Status](https://ci.wardrup.me/buildStatus/icon?job=Buzzbot-Master-Push)](https://ci.wardrup.me/job/Buzzbot-Master-Push/)  | [![CodeFactor](https://www.codefactor.io/repository/github/minorsecond/buzzbot/badge/master?s=7d0189852bedaddcb41bc7579892f35d6cca05b3)](https://www.codefactor.io/repository/github/minorsecond/buzzbot/overview/master)   |
| develop | [![Actions Status](https://github.com/minorsecond/BuzzBot/workflows/Develop/badge.svg)](https://github.com/minorsecond/BuzzBot/actions) | [![Build Status](https://ci.wardrup.me/buildStatus/icon?job=BuzzBot-Develop)](https://ci.wardrup.me/job/BuzzBot-Develop/) | [![CodeFactor](https://www.codefactor.io/repository/github/minorsecond/buzzbot/badge/develop?s=7d0189852bedaddcb41bc7579892f35d6cca05b3)](https://www.codefactor.io/repository/github/minorsecond/buzzbot/overview/develop) |

### Keep track of:
- Your favorite drinks
- Your favorite alcohol producers
- Number of standard drinks consumed for the week
- Number of standard drinks left for the weeks
- Average ABV & IBU per drink
- Drink notes

### Installation instructions
- `git clone https://github.com/minorsecond/BuzzBot.git`
- `cd BuzzBot`
- `mkdir build && cd build`
- `cmake ..`
- `cmake --build . --target BuzzBot`
- If you're running macOS, you'll have a `BuzzBot.app` file in the `build` directory.
- If you're running Linux, you can install the app in `~/.local/bin` by running `cmake --install .`. 
The app should then be available in your app menu.
