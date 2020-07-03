#include <iostream>
#include "simClasses.h"

int Organism::population = 0;

int main() {
    const int MAXPOP = 1000;
    Organism creatureArr[MAXPOP];
    for (int i=0; i<MAXPOP; i++) {
        creatureArr[i].showCreature();
    }
}