# Magician Wars
Magician Wars is a text-based RPG game, originally developed by Roland Wang, Ahad Rauf, Jiahao Liu as a final project for the CS2 class at Las Positas College. The game involves the player (protagonist) that fights against the computer (antagonist). At each turn, the player can choose to attack, buy/use an item, or use a skill. Each enemy that the player defeats will result in the creation of a stronger enemy. A RPG-style game involves various metrics driven by a character’s level. The higher a level, the higher the player’s attack, defense, magic, etc. will become. These metrics makes an enemy stronger. As the game progresses, the player will gain levels and so will the enemy. Object of the game is to defeat as many enemies as possible. 

The player will have opportunities to purchase items to use. Items such as potion to heal the player will be available to buy. Buying or using an item constitutes as a turn. As the player gains level, the player will develop skills. Skills are a stronger attack, but require the use of magic points. Magic points gets restored incrementally after defeating enemies.

At the end of the game, the program will write the score to file. The score is the number of enemies defeated.

## How to Play
The game uses the [https://docs.microsoft.com/en-us/cpp/mfc/mfc-desktop-applications?view=vs-2019](Microsoft Foundation Classes (MFC)) to handle graphics. This library needs to be installed, if you plan to run the code via command line (it is installed by default if you installed Visual Studio, however).

The commands to play are straightforward, and an example of the screen is shown below:
![Main Game Demo Screen](https://raw.githubusercontent.com/ahadrauf/magician_wars/master/figures/home_page_demo.png)
