#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

struct Grain {
    sf::Color color;
    Grain(sf::Color c) : color(c) {}
    bool moved = false;
    float velocity = 1;
    int immobile_frames = 0;
};

class Grid {
private:
public:
    int width;
    int height;
    std::vector<std::vector<Grain*>> cells;
    Grid(int width, int height)
        : width(width), height(height) {
        cells.resize(height, std::vector<Grain*>(width, nullptr));
    }
    void set(int x, int y, Grain* grain);
    Grain* get(int x, int y);
    void update();
    void updateCell(int x, int y);
    void reset_grains();
    ~Grid();
};

#endif //GRID_H
