#include "simClasses.h"

Enviroment::Enviroment(int xs, int ys) : xsize(xs), ysize(ys) {
    map = new Cell*[xsize];
    for (int i = 0; i < xsize; i++) {
        map[i] = new Cell[ysize];
    }
}

Enviroment::~Enviroment() {
    for (int i = 0; i < xsize; i++) { delete[] map[i]; }
    delete[] map;
}