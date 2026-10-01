# A MAZE ING

A maze game written in **C** with **[raylib](https://www.raylib.com/)**. Guide your hero through procedurally generated mazes across five game modes, three difficulty levels and three maze-generation algorithms, and compete on local leaderboards.

<!-- Add screenshots or a GIF here, e.g.:
![Main menu](screenshots/menu.png)
![Gameplay](screenshots/gameplay.png)
![The Dark Night](screenshots/dark_night.png)
-->

---

## Table of Contents

- [Features](#features)
- [How to Play](#how-to-play)
- [Game Modes](#game-modes)
- [Difficulty Levels](#difficulty-levels)
- [Maze Generation Algorithms](#maze-generation-algorithms)
- [Leaderboards](#leaderboards)
- [Requirements](#requirements)
- [Build and Run](#build-and-run)
- [Project Structure](#project-structure)
- [Credits](#credits)

---

## Features

- **5 game modes**: a time trial, a 50-level campaign, a dark maze, a survival mode and an endless practice arena
- **3 difficulty levels**: Easy, Medium and Hard
- **3 maze-generation algorithms** you can switch between in Settings: Recursive Backtracker, Prim's and Aldous-Broder
- **Leaderboards** for best times and high scores, with a player-name search
- **Animated hero sprite** (idle, attack and death animations)
- **Background music and sound effects**, with a music on/off toggle
- **Built-in Info pages** that explain the controls, every game mode and each algorithm

---

## How to Play

Guide your hero from the **top-left cell** to the **glowing exit at the bottom-right**. Walls block your path, so find the gaps and navigate the corridors to reach the exit.

### Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` or Arrow keys | Move the hero |
| `Space` | Generate a new maze (*The Dark Night* and *Infinity War* only) |
| `Enter` | Confirm (for example, after entering your name) |
| `Backspace` | Go back to the menu |
| Mouse | Navigate menus and buttons |

**Getting started:** pick a mode from the main menu, choose your difficulty and maze algorithm in **Settings**, enter your name, and start solving.

---

## Game Modes

### 1. The Best of Us
A classic time trial. Solve one maze on Easy, Medium or Hard as fast as you can. Your best time is saved to the leaderboard.

### 2. The Multiverse of Madmaze
Climb through **50 escalating levels**, each maze bigger and tighter than the last. Finishing a level takes you to the next one automatically. Clear all 50 to conquer the Multiverse!
Each completed level adds `width × height × 5` points to your score.

### 3. The Dark Night
The maze is shrouded in darkness, and you can only see a small radius around your character. Press `Space` at any time for a fresh maze. Race the clock while exploring blind! Best times are saved to a separate leaderboard.

### 4. Time Runs Out
Survive as many rounds as you can. Each maze has a shrinking time limit: finish quickly to score bonus points and advance, but run out of time and it's game over.
- You start with **120 seconds**.
- The limit drops by **10 seconds** per round for the first 5 rounds, then by **5 seconds** per round after that.
- Each round awards `round × 50 + (remaining seconds × 5)` points.

### 5. Infinity War
An endless practice arena. Press `Space` to instantly generate a brand new maze whenever you like, with no timer or scoring. Perfect for casual solving or testing the algorithms.

| Mode | Timer | Score / Leaderboard | Difficulty applies |
|------|:-----:|---------------------|:------------------:|
| The Best of Us | Yes | Best times | Yes |
| The Multiverse of Madmaze | No | High scores | No (levels scale automatically) |
| The Dark Night | Yes | Best times | Yes |
| Time Runs Out | Yes (countdown) | High scores | Yes |
| Infinity War | No | None | Yes |

---

## Difficulty Levels

| Difficulty | Maze size (cells) |
|-----------|-------------------|
| Easy | 17 × 13 |
| Medium | 35 × 25 |
| Hard | 58 × 42 |

In *The Multiverse of Madmaze*, the maze starts small at level 1 and grows with each level, while the cells and walls get progressively smaller, up to level 50.

---

## Maze Generation Algorithms

You can choose the algorithm used to build each maze in **Settings**. Each one gives mazes a different feel.

| Algorithm | Description |
|-----------|-------------|
| **Recursive Backtracker** | A depth-first search that carves long, winding corridors with relatively few dead ends. |
| **Prim's Algorithm** | Grows the maze outward from a starting cell by picking random frontier cells. It produces many short branches and dead ends. |
| **Aldous-Broder** | A random walk that connects each newly visited cell to the maze. It produces unbiased, uniformly random mazes. |

All three algorithms generate *perfect mazes*: every cell is reachable and there is exactly one path between any two cells.

---

## Leaderboards

Leaderboards are saved locally as plain text files in the `scores/` folder and loaded each time the game starts.

| File | Used by |
|------|---------|
| `Best_Times_{easy,medium,hard}.txt` | The Best of Us |
| `Dark_Times_{easy,medium,hard}.txt` | The Dark Night |
| `High_Scores.txt` | The Multiverse of Madmaze |
| `Out_Scores_{easy,medium,hard}.txt` | Time Runs Out |

- View the **High Scores** and **Best Times** pages from the main menu.
- Use the **search** button to look up a player by name.
- Use the **nuke** button to clear a leaderboard.

---

## Requirements

- A C compiler (GCC or Clang)
- [raylib](https://github.com/raysan5/raylib) (5.0 or newer recommended)

### Installing raylib

**Linux (Debian/Ubuntu)**
```bash
sudo apt update
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev \
                 libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
# then build and install raylib from source: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
```

**macOS (Homebrew)**
```bash
brew install raylib
```

**Windows**
Install [raylib with w64devkit](https://github.com/raysan5/raylib/releases), or use MSYS2:
```bash
pacman -S mingw-w64-x86_64-raylib
```

---

## Build and Run

Clone the repository and move into the project folder:

```bash
git clone <your-repository-url>
cd <project-folder>
```

### Linux
```bash
gcc main.c game.c maze.c ui.c scores.c -o game -lraylib -lm
./game
```

### macOS
```bash
gcc main.c game.c maze.c ui.c scores.c -o game \
    $(pkg-config --cflags --libs raylib) -lm
./game
```

### Windows (MinGW / w64devkit)
```bash
gcc main.c game.c maze.c ui.c scores.c -o game.exe -lraylib -lopengl32 -lgdi32 -lwinmm -lm
game.exe
```

> **Important:** always run the game **from the project's root folder**. The game loads its assets (`Assets/...`) and leaderboard files (`scores/...`) using relative paths, so running it from another directory will fail.

---

## Project Structure

```
.
├── main.c          # Entry point and main game loop
├── game.c / .h     # Game state, page handling, game modes, gameplay logic
├── maze.c / .h     # Maze data structures, generation algorithms, rendering
├── ui.c / .h       # Reusable UI components (buttons, cards)
├── scores.c / .h   # Loading, saving, sorting and clearing leaderboards
├── player.h        # Player structure and sprite data
├── Assets/
│   ├── Buttons/        # Button images
│   ├── Mode Buttons/   # Game mode selection images
│   ├── Fonts/          # Fonts
│   ├── Images/         # Title art, info pages, credits
│   ├── Music/          # Background music
│   ├── Sound Effects/  # Sound effects
│   ├── Sprites/        # Hero animation frames
│   └── Textures/       # Wall and floor textures
└── scores/         # Saved leaderboards (plain text)
```

---

## Credits

### Developers

| Name | ID |
|------|----|
| Md Abidur Rahman | 2505019 |
| S.M. Afif Iqbal | 2505004 |

### External Resources

| Resource | Source |
|----------|--------|
| Sprites | [craftpix.net](https://craftpix.net) |
| Textures | [itch.io](https://itch.io) |
| Music | [chosic.com](https://www.chosic.com) |
| Fonts | [dafont.com](https://dafont.com) |
| Sound Effects | [itch.io](https://itch.io) |

Built with [raylib](https://www.raylib.com/).
