#include <iostream>
#include <cstdlib>
#include <ctime>

#include "simClasses.h"

int main() {
    srand(time(NULL));
    Enviroment env1(40,40);
    env1.sprayFood(40);
    env1.printMap();
    
    return EXIT_SUCCESS;
    Organism o1(100, true);
    Organism o2(100, true);
    o1.showOrganism();
    o2.showOrganism();
    std::cout << "\t--Reproduction--\nBaby:" << std::endl;
    (o1+o2).showOrganism();
    o1.reproduce();
    o2.reproduce();
    std::cout << "Parents:" << std::endl;
    o1.showOrganism();
    o2.showOrganism();
}