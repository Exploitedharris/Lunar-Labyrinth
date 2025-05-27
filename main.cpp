#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <stack>
#include <sstream>
#include <iostream>

// Window and maze settings
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 40;
const int MAZE_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int MAZE_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

// Player settings
const float PLAYER_SPEED = 100.0f;

// Game elements
enum class CellType { Wall, Path, Key, Exit, Trap };

class LunarLabyrinth {
private:
    sf::RenderWindow window;
    sf::RectangleShape player;
    std::vector<std::vector<CellType>> maze;
    sf::Vector2i playerPos;
    int keysCollected, level, score;
    sf::Font font;
    sf::Text hudText;
    sf::Sound moveSound, keySound, trapSound;
    sf::SoundBuffer moveBuffer, keyBuffer, trapBuffer;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    LunarLabyrinth() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lunar Labyrinth"),
                       gen(rd()), dist(0, 1) {
        window.setFramerateLimit(60);

        // Initialize player
        player.setSize(sf::Vector2f(CELL_SIZE - 4, CELL_SIZE - 4));
        player.setFillColor(sf::Color::Cyan);
        playerPos = sf::Vector2i(1, 1);
        player.setPosition(playerPos.x * CELL_SIZE + 2, playerPos.y * CELL_SIZE + 2);

        // Initialize game state
        keysCollected = 0;
        level = 1;
        score = 0;
        generateMaze();

        // Initialize HUD
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font\n";
        }
        hudText.setFont(font);
        hudText.setCharacterSize(20);
        hudText.setFillColor(sf::Color::White);
        hudText.setPosition(10.0f, 10.0f);

        // Initialize sounds
        if (!moveBuffer.loadFromFile("move.wav")) {
            std::cerr << "Error loading move sound\n";
        }
        if (!keyBuffer.loadFromFile("key.wav")) {
            std::cerr << "Error loading key sound\n";
        }
        if (!trapBuffer.loadFromFile("trap.wav")) {
            std::cerr << "Error loading trap sound\n";
        }
        moveSound.setBuffer(moveBuffer);
        keySound.setBuffer(keyBuffer);
        trapSound.setBuffer(trapBuffer);
    }

    void generateMaze() {
        maze.resize(MAZE_HEIGHT, std::vector<CellType>(MAZE_WIDTH, CellType::Wall));
        std::stack<sf::Vector2i> stack;
        maze[1][1] = CellType::Path;
        stack.push(sf::Vector2i(1, 1));

        // Generate maze using recursive backtracking
        while (!stack.empty()) {
            sf::Vector2i current = stack.top();
            std::vector<sf::Vector2i> neighbors;

            int x = current.x, y = current.y;
            if (x > 1 && maze[y][x - 2] == CellType::Wall) neighbors.push_back({x - 2, y});
            if (x < MAZE_WIDTH - 2 && maze[y][x + 2] == CellType::Wall) neighbors.push_back({x + 2, y});
            if (y > 1 && maze[y - 2][x] == CellType::Wall) neighbors.push_back({x, y - 2});
            if (y < MAZE_HEIGHT - 2 && maze[y + 2][x] == CellType::Wall) neighbors.push_back({x, y + 2});

            if (!neighbors.empty()) {
                auto next = neighbors[dist(gen) % neighbors.size()];
                maze[(current.y + next.y) / 2][(current.x + next.x) / 2] = CellType::Path;
                maze[next.y][next.x] = CellType::Path;
                stack.push(next);
            } else {
                stack.pop();
            }
        }

        // Place keys, exit, and traps
        int keys = 3, traps = 5;
        for (int i = 0; i < keys; ++i) {
            int x = dist(gen) * 2 + 1, y = dist(gen) * 2 + 1;
            while (maze[y][x] != CellType::Path || (x == 1 && y == 1)) {
                x = dist(gen) * 2 + 1;
                y = dist(gen) * 2 + 1;
            }
            maze[y][x] = CellType::Key;
        }
        int ex = MAZE_WIDTH - 2, ey = MAZE_HEIGHT - 2;
        maze[ey][ex] = CellType::Exit;
        for (int i = 0; i < traps; ++i) {
            int x = dist(gen) * 2 + 1, y = dist(gen) * 2 + 1;
            while (maze[y][x] != CellType::Path || (x == 1 && y == 1) || (x == ex && y == ey)) {
                x = dist(gen) * 2 + 1;
                y = dist(gen) * 2 + 1;
            }
            maze[y][x] = CellType::Trap;
        }
    }

    void handleInput() {
        sf::Vector2i newPos = playerPos;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerPos.x > 0) newPos.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPos.x < MAZE_WIDTH - 1) newPos.x++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerPos.y > 0) newPos.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playerPos.y < MAZE_HEIGHT - 1) newPos.y++;

        if (maze[newPos.y][newPos.x] != CellType::Wall) {
            playerPos = newPos;
            player.setPosition(playerPos.x * CELL_SIZE + 2, playerPos.y * CELL_SIZE + 2);
            moveSound.play();

            // Handle cell interactions
            if (maze[playerPos.y][playerPos.x] == CellType::Key) {
                keysCollected++;
                maze[playerPos.y][playerPos.x] = CellType::Path;
                keySound.play();
                score += 50;
            } else if (maze[playerPos.y][playerPos.x] == CellType::Trap) {
                score -= 20;
                trapSound.play();
                playerPos = sf::Vector2i(1, 1);
                player.setPosition(playerPos.x * CELL_SIZE + 2, playerPos.y * CELL_SIZE + 2);
            } else if (maze[playerPos.y][playerPos.x] == CellType::Exit && keysCollected >= 3) {
                level++;
                score += 100;
                keysCollected = 0;
                playerPos = sf::Vector2i(1, 1);
                player.setPosition(playerPos.x * CELL_SIZE + 2, playerPos.y * CELL_SIZE + 2);
                generateMaze();
            }
        }
    }

    void update(float dt) {
        // Update HUD
        std::stringstream ss;
        ss << "Level: " << level << " | Keys: " << keysCollected << "/3 | Score: " << score;
        hudText.setString(ss.str());
    }

    void render() {
        window.clear(sf::Color::Black);

        // Draw maze
        for (int y = 0; y < MAZE_HEIGHT; ++y) {
            for (int x = 0; x < MAZE_WIDTH; ++x) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                if (maze[y][x] == CellType::Wall) cell.setFillColor(sf::Color(50, 50, 50));
                else if (maze[y][x] == CellType::Path) cell.setFillColor(sf::Color::White);
                else if (maze[y][x] == CellType::Key) cell.setFillColor(sf::Color::Yellow);
                else if (maze[y][x] == CellType::Exit) cell.setFillColor(sf::Color::Green);
                else if (maze[y][x] == CellType::Trap) cell.setFillColor(sf::Color::Red);
                window.draw(cell);
            }
        }

        window.draw(player);
        window.draw(hudText);
        window.display();
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            float dt = clock.restart().asSeconds();
            handleInput();
            update(dt);
            render();
        }
    }
};

int main() {
    LunarLabyrinth game;
    game.run();
    return 0;
}
