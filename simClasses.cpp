#include <iostream>
#include <cstdlib>

#include "simClasses.h"
#include "simConstants.h"

/*///////////////////////////////////////////////////
 ██████  ███████ ███    ██ ███████ 
██       ██      ████   ██ ██      
██   ███ █████   ██ ██  ██ █████   
██    ██ ██      ██  ██ ██ ██      
 ██████  ███████ ██   ████ ███████ 
///////////////////////////////////////////////////*/

Gene Gene::operator+(const Gene& b) {
    if(radicalMutationRoll()) {
        return Gene(true);
    } else {
        Int aux = rand();
        Int mutation = aux % GENE_S_MUTATION;
        mutation *= (aux%2 == 0) ? 1 : -1;
        aux = (aux>>5)%100;
        mutation += (static_cast<float>(aux)/100.0f) * value + (1 - (static_cast<float>(aux)/100.0f)) * b.value;
        mutation = mutation>GENE_MAX_VAL ? GENE_MAX_VAL : mutation;
        return Gene(abs(mutation));
    }
}

/*///////////////////////////////////////////////////
 ██████  ██████   ██████   █████  ███    ██ ██ ███████ ███    ███ 
██    ██ ██   ██ ██       ██   ██ ████   ██ ██ ██      ████  ████ 
██    ██ ██████  ██   ███ ███████ ██ ██  ██ ██ ███████ ██ ████ ██ 
██    ██ ██   ██ ██    ██ ██   ██ ██  ██ ██ ██      ██ ██  ██  ██ 
 ██████  ██   ██  ██████  ██   ██ ██   ████ ██ ███████ ██      ██ 
///////////////////////////////////////////////////*/

Organism::Organism(int baseenergy, bool generaterandom=false)
        : age(0), generation(0), children(0), energy(baseenergy) {
    if (generaterandom) {
        adultage.setvalue();
        reprEneFactor.setvalue();
        size.setvalue();

        sight.setvalue();
        offspringratio.setvalue();
    }
}

void Organism::setMoveCost() {
    
}

void Organism::reproduce() {
    energy -= offspringEnergy();
    children++;
    age++;
}

void Organism::move() {
    energy -= moveCost;
    age++;
}

Organism Organism::operator + (Organism& org) {
    Organism baby(offspringEnergy() + org.offspringEnergy());
    baby.generation = (generation > org.generation) ? generation+1 : org.generation+1;
    baby.adultage = adultage + org.adultage;
    baby.reprEneFactor = reprEneFactor + org.reprEneFactor;
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

/*///////////////////////////////////////////////////
 ██████ ███████ ██      ██      
██      ██      ██      ██      
██      █████   ██      ██      
██      ██      ██      ██      
 ██████ ███████ ███████ ███████
///////////////////////////////////////////////////*/
Cell::Cell() : food(false) {
    occupied[0] = nullptr;
    occupied[1] = nullptr;
    occupied[2] = nullptr;
}

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

/*///////////////////////////////////////////////////
███████ ███    ██ ██    ██ ██ ██████   ██████  ███    ███ ███████ ███    ██ ████████ 
██      ████   ██ ██    ██ ██ ██   ██ ██    ██ ████  ████ ██      ████   ██    ██    
█████   ██ ██  ██ ██    ██ ██ ██████  ██    ██ ██ ████ ██ █████   ██ ██  ██    ██    
██      ██  ██ ██  ██  ██  ██ ██   ██ ██    ██ ██  ██  ██ ██      ██  ██ ██    ██    
███████ ██   ████   ████   ██ ██   ██  ██████  ██      ██ ███████ ██   ████    ██
///////////////////////////////////////////////////*/
Enviroment::Enviroment() : xsize(0), ysize(0) {}

Enviroment::Enviroment(Int xs, Int ys) : xsize(xs), ysize(ys) {
    map = new Cell*[xsize];
    for (Int i = 0; i < xsize; i++) { map[i] = new Cell[ysize]; }
}

void Enviroment::initialize(Int xs, Int ys) {
    xsize = xs;
    ysize = ys;
    map = new Cell*[xsize];
    for (Int i = 0; i < xsize; i++) { map[i] = new Cell[ysize]; }
}

void Enviroment::showFoodCells() {
    std::cout << "Foods:  ";
    for (Int x=0; x<xsize; x++) {
        for (Int y=0; y<ysize; y++) {
            if(map[x][y].food) {
                std::cout << "[" << x << "," << y << "]" << " ";
            }
        }
    }
    std::cout << std::endl;
}

void Enviroment::printMap() {
    std::cout << "|";
    for (Int y=0; y<ysize; y++) { std::cout << "="; }
    std::cout << "|";
    for (Int x=0; x<xsize; x++) {
        for (Int y=0; y<ysize; y++) { std::cout << map[x][y].cellshow(); }
        std::cout << "|\n|";
    }
    for (Int y=0; y<ysize; y++) { std::cout << "="; }
    std::cout << "|" << std::endl;
}

Enviroment::~Enviroment() {
    for (Int i = 0; i < xsize; i++) { delete[] map[i]; }
    delete[] map;
}

void Enviroment::addOrganism(Organism* org) {
    Int r, x, y;
    Int counter = 0;
    while(counter < xsize*ysize) {
        r = rand();
        for (Int i = 0; i<6; i++) {
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
    org->showOrganism();
}

void Enviroment::sprayFood(Int amount) {
    Int count = 0;
    Int randomgen, xcoord, ycoord;
    while(count < amount) {
        randomgen = rand();
        for (Int i=0; i<4; i++) {
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
void Enviroment::reproductionAttempt(Int x, Int y) {

}

void Enviroment::foodScramble(Int x, Int y) {

}*/

/*///////////////////////////////////////////////////
███████ ██ ███    ███ ██    ██ ██       █████  ████████ ██  ██████  ███    ██ 
██      ██ ████  ████ ██    ██ ██      ██   ██    ██    ██ ██    ██ ████   ██ 
███████ ██ ██ ████ ██ ██    ██ ██      ███████    ██    ██ ██    ██ ██ ██  ██ 
     ██ ██ ██  ██  ██ ██    ██ ██      ██   ██    ██    ██ ██    ██ ██  ██ ██ 
███████ ██ ██      ██  ██████  ███████ ██   ██    ██    ██  ██████  ██   ████ 
///////////////////////////////////////////////////*/
Simulation::Simulation(Int xs, Int ys, Int initFood, Int foodp, Int fooda, Int initOrganisms, Int baseEnergy)
          : Enviroment(xs, ys), foodperiod(foodp), foodamount(fooda){
    Organism* originals;
    sprayFood(initFood);
    for(Int i=0; i<initOrganisms; i++) {
        addOrganism(new Organism(baseEnergy, true));
    }
}

void Simulation::step() {
    for (Int x=0; x<xsize; x++) {
        for (Int y=0; y<ysize; y++) {

        }
    }
}

void Simulation::run(Int cicles=-1) {
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
