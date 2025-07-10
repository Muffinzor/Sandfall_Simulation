#include <SFML/Graphics.hpp>
#include "Grid.h"

const int CELL_SIZE = 3;
const int GRID_WIDTH = 300;
const int GRID_HEIGHT = 300;

int main() {
    Grid grid(GRID_WIDTH, GRID_HEIGHT);

    // Manually insert one yellow grain
    sf::Color yellow(255, 255, 0);
    sf::Color red(255, 0, 0);
    sf::Color green(0, 255, 0);
    sf::Color blue(0, 0, 255);

    grid.set(70, 50, new Grain(yellow));
    grid.set(70, 52, new Grain(red));
    grid.set(70, 54, new Grain(green));
    grid.set(70, 56, new Grain(blue));


    sf::RenderWindow window(sf::VideoMode(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE), "Grain Test");
    sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    sf::Clock clock;
    const sf::Time timePerUpdate = sf::seconds(1.f / 60.f);  // 90 updates per second
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        timeSinceLastUpdate += clock.restart();

        // Update the simulation at fixed intervals
        while (timeSinceLastUpdate >= timePerUpdate) {
            grid.update();
            timeSinceLastUpdate -= timePerUpdate;
        }

        window.clear();

        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                Grain* g = grid.get(x, y);
                if (g != nullptr) {
                    cellShape.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    cellShape.setFillColor(g->color);
                    window.draw(cellShape);
                }
            }
        }

        window.display();
    }

    return 0;
}