# so_long
For this 42 project, we code a simple 2D game using the minilibX graphics library for rendering and event handling.

<img width="678" alt="Screenshot of the game" src="https://user-images.githubusercontent.com/92207326/199592185-a5e94666-7c4c-4b0c-8e77-420615bfcad2.png">

## How to run it
First you have to compile the project, you can do so with :
```
make
```
Then, you can run the program like so :
```
./so_long <map_path>
```
The program takes a map_path as an argument, a sample map is provided in the maps folder. You can test it by running this command :
```
./so_long maps/map.ber
```

## How to play
You are a cunning fox and you have to eat all the chickens on the map before escaping through the hole. 
Each time you move a steps counter is incremented, the goal is to complete the game with the smallest number of steps.

To move you can press the W,A,S,D keys. The game can be exited by pressing the Esc key.

## Features
* You can't pass through the walls !
* The program can parse any map, so you can create a map from sracth and the game will run it
* The map parsing ensures that the map is valid (rectangular, enclosed by walls, containing at least an exit, a player position and an item)
* As always, the program should be free of memory leaks

## Credits
* [minilibX](https://github.com/42Paris/minilibx-linux)
* For the beautiful pixel art : \
https://elthen.itch.io/2d-pixel-art-fox-sprites \
https://jamiebrownhill.itch.io/solaria-demo \
https://pixelplant.itch.io/chicken-sprite-sheet
