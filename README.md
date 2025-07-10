# 🎮 Maze Shooter Game

A classic console-based maze game written in C++ where players navigate through a maze, avoid enemies, and shoot obstacles to survive!

## 🚀 Features

- **🕹️ Player Movement**: Navigate through the maze using arrow keys
- **🎯 Shooting System**: Fire bullets upward to destroy obstacles and enemies
- **👾 Enemy AI**: Enemies move vertically and bounce off walls
- **💥 Collision Detection**: Realistic collision system between player, enemies, and obstacles
- **🏆 Scoring System**: 
  - 50 points for destroying obstacles (`x`)
  - 5 points for defeating enemies (`e`)
- **❤️ Lives System**: Start with 3 lives, lose one when touching enemies
- **🎨 Colorful Console Display**: Different colors for player, enemies, and obstacles
- **⚡ Real-time Gameplay**: Smooth animation with customizable game speed

## 🎯 Game Elements

| Symbol | Description | Color |
|--------|-------------|-------|
| `P` | Player | 🔴 Red |
| `e` | Enemy | 🟢 Green |
| `x` | Destructible Obstacle | 🟣 Magenta |
| `#` | Wall | ⚪ White |
| `.` | Bullet | ⚪ White |

## 🎮 Controls

- **⬆️ Up Arrow**: Move up
- **⬇️ Down Arrow**: Move down
- **⬅️ Left Arrow**: Move left
- **➡️ Right Arrow**: Move right
- **🔫 Spacebar**: Fire bullet
- **❌ Q**: Quit game

## 🛠️ Technical Details

- **Language**: C++
- **Platform**: Windows (uses Windows.h)
- **Dependencies**: 
  - `windows.h` for console manipulation
  - `conio.h` for keyboard input
- **Display**: 20x20 maze with console buffer rendering
- **Architecture**: Structured programming with enemy management system

## 🎲 Gameplay

1. **🎯 Objective**: Defeat all enemies while avoiding direct contact
2. **🏃 Movement**: Navigate through the maze avoiding walls (`#`) and enemies (`e`)
3. **🔫 Combat**: Shoot bullets upward to destroy obstacles and enemies
4. **⚠️ Danger**: Touching enemies costs a life and resets your position
5. **🏆 Victory**: Eliminate all enemies to win the game
6. **💀 Game Over**: Lose all 3 lives and the game ends

## 🚀 Getting Started

### Prerequisites
- Windows OS
- C++ compiler (Visual Studio, MinGW, etc.)

### Compilation
```bash
g++ -o maze_game maze_game.cpp
```

### Running
```bash
./maze_game.exe
```

## 🎨 Game Features

- **🎭 Dynamic Enemy Movement**: Enemies move vertically and change direction when hitting walls
- **🎯 Precision Shooting**: Bullets travel upward until hitting obstacles, enemies, or walls
- **🔄 Player Respawn**: Player returns to starting position when hit by enemies
- **📊 Live Score Display**: Real-time score and lives counter
- **🎨 Console Graphics**: Colorful ASCII art with Windows console API

## 🤝 Contributing

Feel free to fork this project and submit pull requests! Some ideas for improvements:
- 🎵 Add sound effects
- 🗺️ Create multiple maze levels
- 🎮 Add power-ups and special weapons
- 🤖 Implement different enemy types
- 🎯 Add horizontal shooting

## 📜 License

This project is open source and available under the MIT License.

---

**🎮 Enjoy the retro gaming experience!** 🕹️✨
