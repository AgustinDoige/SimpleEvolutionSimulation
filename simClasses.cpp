#include "simClasses.h"
#include <iostream>
#include <cstdlib>

/*const int GENE_MAX_VAL = 1000;
const int GENE_S_MUTATION = 50;*/

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
        //std::cout << "aux:" << aux << "\tmutation:" << mutation << std::endl;
        mutation += (static_cast<float>(aux)/100.0f) * value + (1 - (static_cast<float>(aux)/100.0f)) * b.value;
        mutation = mutation>GENE_MAX_VAL ? GENE_MAX_VAL : mutation;
        return Gene(abs(mutation));
    }
}

///////////////////////////////////////////////////
Enviroment::Enviroment() {
    std::cout << "Enviroment cant be initialized with no dimensions" << std::endl;
    exit(-1);
}

Enviroment::Enviroment(int xs, int ys) : xsize(xs), ysize(ys) {
    map = new Cell*[xsize];
    for (int i = 0; i < xsize; i++) { map[i] = new Cell[ysize]; }
}

Enviroment::~Enviroment() {
    for (int i = 0; i < xsize; i++) { delete[] map[i]; }
    delete[] map;
}

///////////////////////////////////////////////////
/*  
    unsigned int age;
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
    std::cout << "age: " << age << "\t";
    std::cout << "generation: " << generation << "\t";
    std::cout << "children: " << children << "\n";
    std::cout << "energy: " << energy << "\n";
    std::cout << "adultage: " << adultage.geneval() << "\t";
    std::cout << "size: " << size.geneval() << "\t";
    std::cout << "offspringratio: " << offspringratio.geneval() << "\n" << std::endl;
}