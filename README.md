Lunar Labyrinth
Lunar Labyrinth is an engaging 2D maze exploration game built using C++ and the SFML library. Navigate through randomly generated mazes, collect keys to unlock the exit, and avoid traps to progress through levels. This open-source project demonstrates procedural generation and maze-based gameplay in C++. Your support through GitHub Sponsors helps us enhance the game with new features and keep it free for the community!
Features

Procedurally generated mazes using recursive backtracking.
Key collection to unlock exits and progress to new levels.
Traps that penalize the player and reset their position.
Score tracking based on key collection and level completion.
Audio feedback for movement, key collection, and trap triggers.
Lightweight and extensible codebase.

Gameplay

Objective: Find and collect 3 keys to unlock the exit, avoid traps, and advance to the next level.
Controls:
Arrow Keys: Move the player through the maze.


Scoring:
Collect a key: +50 points.
Hit a trap: -20 points.
Reach the exit: +100 points.


Mechanics:
Collect 3 keys to unlock the exit.
Avoid red traps, which deduct points and reset you to the start.
Reach the green exit to advance to a new maze.



Prerequisites
To build and run Lunar Labyrinth, you need:

A C++ compiler (e.g., g++).
SFML 2.5.1 or later installed and configured.
A font file (arial.ttf) for the HUD display.
Sound files (move.wav, key.wav, trap.wav) for audio effects.

Installation

Clone the Repository:
git clone https://github.com/yourusername/LunarLabyrinth.git
cd LunarLabyrinth


Install SFML:

Download SFML from sfml-dev.org.
Follow the installation instructions for your platform (Windows, macOS, or Linux).
Link SFML libraries (graphics, window, system, audio) in your project.


Add Resources:

Place arial.ttf (e.g., from Google Fonts) in the project directory.
Place move.wav, key.wav, and trap.wav (e.g., from Freesound) in the project directory.


Build the Project:

Example using g++:g++ -c main.cpp -I/path/to/sfml/include
g++ main.o -o LunarLabyrinth -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio




Run the Game:
./LunarLabyrinth



Project Structure

main.cpp: The main game source code.
arial.ttf: Font file for HUD display (not included, must be added).
move.wav, key.wav, trap.wav: Sound files for game actions (not included, must be added).

Contributing
We welcome contributions to improve Lunar Labyrinth! You can:

Report bugs or suggest features via GitHub Issues.
Submit pull requests with enhancements or fixes.
Share feedback to enhance gameplay or code.

To contribute:

Fork the repository.
Create a new branch (git checkout -b feature/your-feature).
Commit your changes (git commit -m 'Add your feature').
Push to the branch (git push origin feature/your-feature).
Open a pull request.

Support the Project
Enjoy Lunar Labyrinth and want to see it grow? Support us through GitHub Sponsors! Your contributions help:

Add new features like new trap types, power-ups, or larger mazes.
Improve visuals with sprites and animations.
Maintain and optimize the codebase for the community.

Every donation helps keep Lunar Labyrinth thriving—thank you!
Future Plans

Add a main menu and game over screen with restart option.
Implement a high-score system with persistent storage.
Introduce power-ups (e.g., speed boost, trap immunity).
Add sprite-based graphics for walls, keys, and traps.
Include background music and enhanced sound effects.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments

Built with SFML.
Inspired by classic maze exploration games.
Thanks to the open-source community for tools and resources.


Navigate the lunar maze and thank you for playing Lunar Labyrinth!
