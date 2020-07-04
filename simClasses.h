#if !defined(_SIMCLASSES_H)
#define _SIMCLASSES_H
#include <cstdlib>

const int GENE_MAX_VAL = 1000;
const int GENE_S_MUTATION = 25;

class Organism;

class Cell {
public:
    bool food;
    Organism* occupied[3];
    Cell() : food(false) {
        occupied[0] = nullptr;
        occupied[1] = nullptr;
        occupied[2] = nullptr;
    }
};

/* A gene is number between 1 and 1000. This class includes ways to merge them */
class Gene {
private:
    int value;
    /* Returns a random value between 1 and 1000 */
    inline int randomGeneVal() { return (rand()%1000) + 1; }

    /* Performs a roll that returns true with a small probability */
    inline bool radicalMutationRoll() { return (rand()%16==0 ? true : false); }

public:
    Gene(bool setvalue=false) { if (setvalue) { value = randomGeneVal(); } }

    Gene(int v) : value(v) {}

    int geneval() { return value; }

    void setvalue(int val=-1) { value = val==-1 ? randomGeneVal() : val; }

    /* Generates an offpring of two genes*/
    Gene operator + (const Gene&);
};

class Enviroment {
private:
    int xsize;
    int ysize;
    Cell** map;
public:
    Enviroment();

    Enviroment(int xs, int ys);

    /* Selects [amount] of random cells of the enviroment and puts food there */
    void sprayFood(int amount);

    /* Creates a new organism if attempt works.
    PRE: map[x][y] has two adult organisms
    POST: If successful attempt, third organism will be on cell*/
    void reproductionAttempt(int x, int y);

    /* Simulates a fight and gives the winner the food
    PRE: map[x][y] has two organisms and food */
    void foodScramble(int x, int y);

    ~Enviroment();
};

class Organism {
private:
    /*      GENES:
    adultage:       Amount of cicles that must pass before an organism can reproduce
    size:           Size affects who wins when two organisms want the same piece of food 
                    but also how much energy each step takes
    sight:          Sight affects how far the organism can look to search for food/mate 
                    but also how much energy each step takes
    offspringratio: Percentage of energy that the child is given by that parent upon birth */
    unsigned int age;
    unsigned int generation;
    unsigned int children;
    unsigned int energy;
    Gene adultage;
    Gene size;
    Gene sight;
    Gene offspringratio;
    /* Returns how much energy this organism would give to its offspring right now */
    inline int offspringEnergy();

public:
    Organism(int baseenergy, bool generaterandom=false) : age(0), generation(0), children(0), energy(baseenergy) {
        if (generaterandom) {
            adultage.setvalue();
            size.setvalue();
            sight.setvalue();
            offspringratio.setvalue();
        }
    }

    void reproduce();

    /* Returns the offspring of the two organisms */
    Organism operator + (Organism& org);  
    void showOrganism();
};

class Simulation {
};

#endif