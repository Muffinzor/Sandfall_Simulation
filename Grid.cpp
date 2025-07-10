#include "Grid.h"

#include <random>
#include "Utility.h"

void Grid::reset_grains() {
    for (int y = height - 2; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Grain* current = cells[y][x];
            if (current != nullptr) current->moved = false;
        }
    }
}

void Grid::update() {
    reset_grains();

    for (int y = height - 2; y >= 0; --y) {
        bool leftToRight = Utility::random_bool();
        if (leftToRight) {
            for (int x = 0; x < width; ++x) {
                updateCell(x, y);
            }
        } else {
            for (int x = width - 1; x >= 0; --x) {
                updateCell(x, y);
            }
        }
    }
}

void Grid::updateCell(int x, int y) {
    Grain* current = cells[y][x];
    if (current != nullptr && !current->moved) {
        if (cells[y + 1][x] == nullptr) {
            cells[y + 1][x] = current;
            cells[y][x] = nullptr;
            current->moved = true;
        } else {
            bool leftFree = (x > 0) && (cells[y + 1][x - 1] == nullptr);
            bool rightFree = (x < width - 1) && (cells[y + 1][x + 1] == nullptr);

            if (leftFree && rightFree) {
                if (Utility::random_bool()) {
                    cells[y + 1][x - 1] = current;
                } else {
                    cells[y + 1][x + 1] = current;
                }
                cells[y][x] = nullptr;
                current->moved = true;
            } else if (leftFree) {
                cells[y + 1][x - 1] = current;
                cells[y][x] = nullptr;
                current->moved = true;
            } else if (rightFree) {
                cells[y + 1][x + 1] = current;
                cells[y][x] = nullptr;
                current->moved = true;
            }
        }
    }
}

void Grid::set(int x, int y, Grain* grain) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x] = grain;
    }
}

Grain* Grid::get(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return cells[y][x];
    }
    return nullptr;
}

Grid::~Grid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            delete cells[y][x];
        }
    }
}