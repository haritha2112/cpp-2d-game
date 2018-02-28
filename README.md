# Aqua's Quest

## About 
Data Driven 2-D game developed using C++ and SDL 2.0.

The game has one level and the main theme of the game is that Aqua [the blue bird] has to collect eggs and go to it's tree. It has 3 lives. It will be facing enemies [red and green bugs] on its way. It can shoot its enemies, and it's health reduces when it comes in contact with a enemy [Dies when it comes in contact with more than 2]. Near its tree will be a huge gaint enemy[The boss], which will keep shooting at the player. Aqua has to kill the enemy and reach the tree in order to win the game. A score board will be displayed after you finish the game. 

## Demo

![alt text](https://github.com/haritha2112/cpp-2d-game/blob/myproject/Aqua's-Quest-Demo.gif "Aqua's Quest Demo")

## Controls
WASD      - Movements

Space Bar - Shoot

F1        - Toggle Menu

R         - Restart

P         - Pause

E         - Toggle Sound Effects

M         - Toggle Music

G         - God Mode

Q or Esc  - Quit

## Gee-Whiz Factors

1. Painters Algorithm was implemented: Black birds are flying in the background - behind and in front of the mountains
2. Health bar with 3 lives
3. Options to toggle Music and sound effects, and that status will be visible on the hud
4. Score calculation and displaying it at the end of the game or after the player loses.

## Other details

1. Number of bullets to kill the enemies [Configurable via game.xml]:

    1 - Green enemy
    
    2 - Red enemy
    
    20 - Boss enemy
2. The player will restart from the first position after he loses a life.
3. Points are calculated based on the number of lives left, number of eggs collected and number of enemies killed.

## Sprite Source
1.  Background Images Source: https://opengameart.org/content/horizontal-2d-backgrounds

2.  Egg Sprite Source: https://opengameart.org/content/egg-item-sprite

3.  Bird [Player] Sprite Source: https://openclipart.org/detail/240196/flying-game-character-sprite-sheet

4.  Green Enemy Sprite Source: https://opengameart.org/content/bevouliin-free-flappy-monster-sprite-sheets

5.  Red Enemy Sprite Source: https://opengameart.org/content/bevouliin-free-red-flappy-bee-bird-game-character-sprite-sheets-for-game-developers

6.  Boss Enemy Sprite Source: https://opengameart.org/content/grumpy-bee-enemy-game-character

7.  Player's Bullets Sprite Source: https://opengameart.org/content/energy-ball

8.  Enemy's Bullets Sprite Source: https://opengameart.org/sites/default/files/spr_bullet_strip02.png

9.  Tree [nest] Sprite Source: https://twitter.com/izquierelena/status/622728214323023873

10. Heart Sprite Source: https://opengameart.org/content/heart-1

11. Blackbird Sprite Source: http://spritely.net/

12. Background Music Source: https://www.playonloop.com/2017-music-loops/doggo-brothers/

13. Sound Effects Source: https://freesound.org/
