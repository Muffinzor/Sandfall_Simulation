#include "Grid.h"

#include <iostream>
#include <random>
#include "Utility.h"

void Grid::reset_grains() {
    for (int y = height - 2; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Grain* current = cells[y][x];
            if (current != nullptr) {
                current->moved = false;
                if (current->immobile_frames >= 3) current->velocity = 1;
            }
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

void accelerate_grain(Grain* current) {
    current->velocity += 0.1f;
}

void Grid::updateCell(int x, int y) {
    Grain* current = cells[y][x];
    if (current != nullptr && !current->moved) {
        accelerate_grain(current);

        int fallDistance = static_cast<int>(std::floor(current->velocity));
        int currentY = y;
        int currentX = x;

        for (int i = 0; i < fallDistance; ++i) {
            int nextY = currentY + 1;
            if (nextY >= height) {
                current->velocity = 1;
                break;
            }

            if (cells[nextY][currentX] == nullptr) {
                cells[nextY][currentX] = current;
                cells[currentY][currentX] = nullptr;
                currentY = nextY;
                current->moved = true;
            } else {
                Grain* blocking_grain = cells[nextY][currentX];
                if (blocking_grain != nullptr && blocking_grain->velocity < current->velocity) {
                    blocking_grain->velocity = current->velocity;
                }
                bool leftFree = (currentX > 0) && (cells[currentY + 1][currentX - 1] == nullptr);
                bool rightFree = (currentX < width - 1) && (cells[currentY + 1][currentX + 1] == nullptr);

                if (leftFree || rightFree) {
                    int targetX = currentX;
                    if (leftFree && rightFree) {
                        targetX += Utility::random_bool() ? -1 : 1;
                    } else if (leftFree) {
                        targetX -= 1;
                    } else {
                        targetX += 1;
                    }
                    cells[currentY + 1][targetX] = current;
                    cells[currentY][currentX] = nullptr;
                    currentY += 1;
                    currentX = targetX;
                    current->moved = true;
                } else {
                    break;
                }
            }
        }

        if (!current->moved) {
            current->immobile_frames++;
        } else {
            current->immobile_frames = 0;
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