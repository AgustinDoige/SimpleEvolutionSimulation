#if !defined(_SIMCLASSES_H)
#define _SIMCLASSES_H

class Cell {
public:
    bool food;
    Organism* occupied[3];
    Cell() : food(false), occupied({nullptr, nullptr, nullptr}) {}
};

class Enviroment {
private:
    int xsize;
    int ysize;
    Cell** map;
public:
    Enviroment() : xsize(0), ysize(0), map(nullptr) {}

    Enviroment(int xs, int ys) : xsize(xs), ysize(ys);

    /* Selects [amount] of random cells of the enviroment and puts food there */
    void sprayFood(int amount);

    /* Creates a new organism PRE: map[x][y] has two adult organisms */
    void reproductionAttempt(int x, int y);

    ~Enviroment();
};

class Organism {
private:
    int age;
    int adultage;
    int energy;
    int maxenergy;
    int size;
public:
    Organism() : age(0) {
    }

    void showCreature();
};

class Simulation {
};

#endif