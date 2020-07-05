#if !defined(_SIMCLASSES_H)
#define _SIMCLASSES_H
#include <cstdlib>
#include "simConstants.h"


/* A gene is number between 1 and GENE_MAX_VAL. This class includes ways to merge them */
class Gene {
private:
    int value;
    /* Returns a random value between 1 and GENE_MAX_VAL */
    inline int randomGeneVal() { return (rand()%GENE_MAX_VAL) + 1; }

    /* Performs a roll that returns true with a small probability */
    inline bool radicalMutationRoll() { return (rand()%RADICAL_MUT_FACTOR==0 ? true : false); }

public:
    /* Gene() creates an non-initiated Gene
    Gene(true) generates a random value */
    Gene(bool setvalue=false) { if (setvalue) { value = randomGeneVal(); } }

    Gene(int v) : value(v) {}

    /* Returns the value of the gene */
    int geneval() { return value; }

    /* Initiates the value. With no argument it sets a random one*/
    void setvalue(int val=-1) { value = val==-1 ? randomGeneVal() : val; }

    /* Generates an offpring of two genes*/
    Gene operator+(const Gene&);
};

/* Organism:-:
    adultage:       Amount of cicles that must pass before an organism can reproduce
    reprEneFactor:  The bigger this value the more energy the organism will need before it will be willing to reproduce
    size:           Size affects who wins when two organisms want the same piece of food 
                    but also how much energy each step takes
    sight:          Sight affects how far the organism can look to search for food/mate 
                    but also how much energy each step takes
    offspringratio: Percentage of energy that the child is given by that parent upon birth */
class Organism {
private:
    unsigned int age;
    unsigned int generation;
    unsigned int children;
    unsigned int energy;
    unsigned int moveCost;
    Gene adultage;
    Gene reprEneFactor;
    Gene size;
    Gene sight;
    Gene offspringratio;
    
    /* Returns how much energy this organism would give to its offspring given its current energy */
    inline int offspringEnergy() {
        return static_cast<float>(energy)*(static_cast<float>(offspringratio.geneval())/1000.0f);
    }

    void setMoveCost();

public:
    Organism(int baseenergy, bool generaterandom=false);

    /* Modifies the Organism as if it just reproduced.
    NOTE: Call AFTER calling baby=org1+org2 */
    void reproduce();

    /* Modifies the Organisms as if it just moved one step */
    void move();

    /* Returns the offspring of the two organisms */
    Organism operator + (Organism& org);  
    
    /* Shows all details of the organism */
    void showOrganism();

    /* Returns a char that represents the organism */
    char reprChar();
};

/* Full public Class that represents the cells of the map */
class Cell {
public:
    bool food;
    Organism* occupied[3];
    Cell();
    char cellshow();
};

class Enviroment {
protected:
    int xsize;
    int ysize;
    Cell** map;
public:
    Enviroment(int xs, int ys);

    /* Creates an un-initialized enviroment, size=0 */
    Enviroment();

    /* Allocates memory */
    void initialize(int xs, int ys);

    /* Selects [amount] of random cells of the enviroment and puts food there */
    void sprayFood(int amount);

    /* Selects a random free place of them map and places the organism there */
    void addOrganism(Organism*);

    /* Creates a new organism if attempt works.
    PRE: map[x][y] has two adult organisms
    POST: If successful attempt, third organism will be on cell*/
    void reproductionAttempt(int x, int y);

    /* Simulates a fight and gives the winner the food
    PRE: map[x][y] has two organisms and food */
    void foodScramble(int x, int y);

    void showFoodCells();

    void printMap();

    ~Enviroment();
};

class Simulation : private Enviroment {
private:
    int foodperiod;
    int foodamount;
public:
    Simulation(int xs, int ys, int initFood, int foodp, int fooda, int initOrganisms, int baseEnergy);

    void step();

    void run(int cicles=0);
};

#endif