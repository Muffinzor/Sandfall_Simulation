#ifndef UTILITY_H
#define UTILITY_H
#include <cstdlib>
#include <stdlib.h>

class Utility {
public:
    static int random_int(int min, int max) {
        return rand() % (max - min) + min;
    }
    static bool random_bool() {
        return rand() % 2;
    }
};

#endif //UTILITY_H
