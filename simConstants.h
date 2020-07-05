#if !defined(_SIM_CONSTANTS_H)
#define _SIM_CONSTANTS_H

typedef int Int;

/* A gene can have a value from 1 to this value */
const Int GENE_MAX_VAL = 1000;

/* After the weighted average of two gene parents, 
there's a small mutation up to this value on either side */
const Int GENE_S_MUTATION = 25;

/* The inverse of this value (1/RADICAL_MUT_FACTOR) will be
the probability of a radical mutation when two genomes mix */
const Int RADICAL_MUT_FACTOR = 20;

/* How much energy a single piece of food will give to the organism */
const Int ENERGY_PER_FOOD = 50;

/* How many cycles will pass before the simulation sprays food again */
const Int DEFAULT_FOOD_CYCLE = 10;

/* How much pieces of food each spraying will give */
const Int DEFAULT_FOOD_AMOUNT = 2;

/* How much energy an organism of size=1000 would need to move */
const Int MAX_SIZE_MOVE_COST = 10;

/* How many rows the default map has */
const Int DEFAULT_XSIZE = 30;

/* How many columns the default map has */
const Int DEFAULT_YSIZE = 50;

#endif