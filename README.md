# Game of Life 🌱
The "**Game of Life**" project is a cellular automaton simulation created 
using the **SFML** graphics library for visual rendering and the **YAML** 
file format for game configuration.

In this game, each cell has two states: alive or dead, and its state 
changes based on the number of neighboring cells. The game continues 
until it stabilizes or reaches a certain step limit.

## Technologies and Libraries 🔧
- **SFML** — used for graphical rendering and window management in the game.
- **YAML** — used to store game configuration, such as field size, initial alive cells, and color schemes.

## Project Overview 🎮
This project models the classic **Game of Life** on a grid of configurable 
size and initial configuration. You can adjust game parameters via 
the **config.yaml** file to change:

- Grid size
- Initial number of alive cells
- Background and cell colors
- Cell size
- Update interval and frame rate 

## Project Structure 📂
- **src/** — source code for the game.
- **libs/** — libraries, including SFML and YAML.
- **config.yaml** — game configuration file.

## How to Build the Project 🛠️
1. Clone the repository to your computer:
```
git clone https://github.com/Rinaz-netiz/cpp-Game-of-life.git
```
2. Navigate to the project directory:
```
cd cpp-Game-of-life
```
3. Create a build directory:
```
mkdir build
cd build
```
4. Run CMake to generate the build configuration:
```
cmake .. -G "Visual Studio 17 2022" -A x64
```
5. Build needed type(Debug or Release):
```
cmake --build . --config Debug
```
```
cmake --build . --config Release
```

6. Run needed version from directory build
```
Debug/Game_life.exe
```
```
Release/Game_life.exe
```

## How to Configure the Game 📝
The **config.yaml** file allows you to configure the game parameters:

```yaml
game_settings:
width: 40            # Field width
height: 40           # Field height
initial_alive: 3     # Initial number of alive cells
cell_size: 20        # Size of a single cell in pixels
update_delay: 0.1    # Update delay (in seconds)

colors:
background: [240, 30, 0]  # Background color (R, G, B)
alive_cell: [0, 0, 0]     # Alive cell color (black)
dead_cell: [255, 255, 255] # Dead cell color (white)

window:
title: "Game of Life"      # Window title
window_size: [800, 800]    # Window size (width, height)
framerate_limit: 30        # Frame rate limit
```
## Notes ⚠️
- To change game settings, edit the **config.yaml** file.
- You can customize not only the grid size but also the cell colors, 
allowing for a more personalized game experience.
- You should have the **Visual C++ 17 (2022)** compile for **SFML-3.0.0** 
