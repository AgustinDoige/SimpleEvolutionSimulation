#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simClasses.h"

int main() {
    srand(time(NULL));
    /*Gene g1, g2, g3;
    std::cout << "g1: " << g1.genval() << std::endl;
    std::cout << "g2: " << g2.genval() << std::endl;
    for (int i=0; i<5; i++) {
        g3 = g1+g2;
        std::cout << "g1+g2= " << g3.genval() << "\n" << std::endl;

    }*/

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