#include "simClasses.h"
#include <iostream>
#include <cstdlib>

///////////////////////////////////////////////////
char Cell::cellshow() {
    if(occupied[0]==nullptr) {
        return (food ? '~' : ' ');
    } else if(occupied[2]!=nullptr) {
            return ('3');
    } else if (occupied[1]!=nullptr) {
        return (food ? '!' : '2');
    } else {
        return (*occupied[0]).reprChar();
    }
}
///////////////////////////////////////////////////
Gene Gene::operator+(const Gene& b) {
    if(Gene::radicalMutationRoll()) {
        //std::cout << "Radical Mutation!" << std::endl;
        return Gene();
    } else {
        int aux = rand();
        int mutation = aux % GENE_S_MUTATION;
        mutation *= (aux%2 == 0) ? 1 : -1;
        aux = (aux>>5)%100;
        mutation += (static_cast<float>(aux)/100.0f) * value + (1 - (static_cast<float>(aux)/100.0f)) * b.value;
        mutation = mutation>GENE_MAX_VAL ? GENE_MAX_VAL : mutation;
        return Gene(abs(mutation));
    }
}

///////////////////////////////////////////////////
Enviroment::Enviroment() : xsize(0), ysize(0) {}

Enviroment::Enviroment(int xs, int ys) : xsize(xs), ysize(ys) {
    map = new Cell*[xsize];
    for (int i = 0; i < xsize; i++) { map[i] = new Cell[ysize]; }
}

void Enviroment::initialize(int xs, int ys) {
    xsize = xs;
    ysize = ys;
    map = new Cell*[xsize];
    for (int i = 0; i < xsize; i++) { map[i] = new Cell[ysize]; }
}

void Enviroment::showFoodCells() {
    std::cout << "Foods:  ";
    for (int x=0; x<xsize; x++) {
        for (int y=0; y<ysize; y++) {
            if(map[x][y].food) {
                std::cout << "[" << x << "," << y << "]" << " ";
            }
        }
    }
    std::cout << std::endl;
}

void Enviroment::printMap() {
    std::cout << "|";
    for (int y=0; y<ysize; y++) { std::cout << "="; }
    std::cout << "|";
    for (int x=0; x<xsize; x++) {
        for (int y=0; y<ysize; y++) { std::cout << map[x][y].cellshow(); }
        std::cout << "|\n|";
    }
    for (int y=0; y<ysize; y++) { std::cout << "="; }
    std::cout << "|" << std::endl;
}

Enviroment::~Enviroment() {
    for (int i = 0; i < xsize; i++) { delete[] map[i]; }
    delete[] map;
}

void Enviroment::addOrganism(Organism* org) {
    int r, x, y;
    int counter = 0;
    while(counter < xsize*ysize) {
        r = rand();
        for (int i = 0; i<6; i++) {
            x = r%xsize;
            r = r>>2;
            y = r%ysize;
            r = r>>2;
            if (map[x][y].occupied[0]==nullptr) {
                map[x][y].occupied[0] = org;
                return;
            }
        }
    }
    std::cout << "Failed to add organism to Map.\tOrganism:";
    (*org).showOrganism();
}

void Enviroment::sprayFood(int amount) {
    int count = 0;
    int randomgen, xcoord, ycoord;
    while(count < amount) {
        randomgen = rand();
        for (int i=0; i<4; i++) {
            xcoord = randomgen%xsize;            
            randomgen = randomgen>>3;
            ycoord = randomgen%ysize;
            randomgen = randomgen>>3;
            map[xcoord][ycoord].food = true;
            count++;
            if(count>amount) { break; }
        }

    }
}
/*
void Enviroment::reproductionAttempt(int x, int y) {

}

void Enviroment::foodScramble(int x, int y) {

}*/


///////////////////////////////////////////////////
/*  unsigned int age;
    unsigned int generation;
    unsigned int children;
    unsigned int energy;
    GENES:
    adultage:       Amount of cicles that must pass before an organism can reproduce
    size:           Size affects who wins when two organisms want the same piece of food 
                    but also how much energy each step takes
    sight:          Sight affects how far the organism can look to search for food/mate 
                    but also how much energy each step takes
    offspringratio: Percentage of energy that the child is given by that parent upon birth
    
    Gene adultage;
    Gene size;
    Gene sight;
    Gene offspringratio;*/

inline int Organism::offspringEnergy() {
    return static_cast<float>(energy)*(static_cast<float>(offspringratio.geneval())/1000.0f);
}

void Organism::reproduce() {
    energy -= offspringEnergy();
    children++;
}

Organism Organism::operator + (Organism& org) {
    Organism baby(offspringEnergy() + org.offspringEnergy());
    baby.generation = (generation > org.generation) ? generation+1 : org.generation+1;
    baby.adultage = adultage + org.adultage;
    baby.size = size + org.size;
    baby.sight = sight + org.sight;
    baby.offspringratio = offspringratio + org.offspringratio;
    return baby;
}

void Organism::showOrganism() {
    std::cout << "age: "            << age                      << "\t";
    std::cout << "generation: "     << generation               << "\t";
    std::cout << "children: "       << children                 << "\n";
    std::cout << "energy: "         << energy                   << "\n";
    std::cout << "adultage: "       << adultage.geneval()       << "\t";
    std::cout << "size: "           << size.geneval()           << "\t";
    std::cout << "offspringratio: " << offspringratio.geneval() << "\n" << std::endl;
}

char Organism::reprChar() {
    return 'Y';
}
///////////////////////////////////////////////////
Simulation::Simulation(int xs, int ys, int initFood, int foodp, int fooda, int initOrganisms, int baseEnergy)
          : Enviroment(xs, ys), foodperiod(foodp), foodamount(fooda){
    Organism* originals;
    sprayFood(initFood);
    for(int i=0; i<initOrganisms; i++) {
        addOrganism(new Organism(baseEnergy, true));
    }
}

void Simulation::step() {
    for (int x=0; x<xsize; x++) {
        for (int y=0; y<ysize; y++) {

        }
    }
}

void Simulation::run(int cicles=-1) {
    if (cicles==-1) {
        while(true) {
            step();
            printMap();
        }
    } else {
        while(cicles>0) {
            step();
            printMap();
            cicles--;
        }
    }
}