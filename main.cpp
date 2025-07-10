#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Utility.h"

const int CELL_SIZE = 4;
const int GRID_WIDTH = 200;
const int GRID_HEIGHT = 200;
const int GRAIN_MULTIPLIER = 3;
const int GRAIN_SPREAD = 5;

sf::Color HSVtoRGB(float hue, float sat, float val) {
    int h = static_cast<int>(hue / 60.0f) % 6;
    float f = (hue / 60.0f) - h;
    float p = val * (1 - sat);
    float q = val * (1 - f * sat);
    float t = val * (1 - (1 - f) * sat);

    float r = 0, g = 0, b = 0;

    switch (h) {
        case 0: r = val, g = t, b = p; break;
        case 1: r = q, g = val, b = p; break;
        case 2: r = p, g = val, b = t; break;
        case 3: r = p, g = q, b = val; break;
        case 4: r = t, g = p, b = val; break;
        case 5: r = val, g = p, b = q; break;
    }

    return sf::Color(
        static_cast<sf::Uint8>(r * 255),
        static_cast<sf::Uint8>(g * 255),
        static_cast<sf::Uint8>(b * 255)
    );
}

int main() {
    Grid grid(GRID_WIDTH, GRID_HEIGHT);

    float hue = 1.0f;

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

        if (timeSinceLastUpdate >= timePerUpdate) {
            grid.update();
            timeSinceLastUpdate -= timePerUpdate;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                hue += 0.2f;
                if (hue >= 360) hue = 1;
                sf::Color color = HSVtoRGB(hue, 1.0f, 1.0f);
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < GRAIN_MULTIPLIER; ++i) {
                    int gridX = mousePos.x / CELL_SIZE;
                    int gridY = mousePos.y / CELL_SIZE;

                    gridX += Utility::random_int(-GRAIN_SPREAD, GRAIN_SPREAD);
                    gridY += Utility::random_int(-GRAIN_SPREAD, GRAIN_SPREAD);

                    if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) {
                        if (grid.get(gridX, gridY) == nullptr) {
                            grid.set(gridX, gridY, new Grain(color));
                        }
                    }
                }
            }
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