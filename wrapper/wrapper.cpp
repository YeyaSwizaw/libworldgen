#include "wrapper.h"

#include <string>

// TileDef
void tiledef_add_rand_nm_constraint(tiledef* tiledef, rand_nm* nm, int type, double fact) {
    if(type == CONSTRAINT_LT) {
        tiledef->addConstraint({nm, wg::ConstraintType::LT, fact});
    } else {
        tiledef->addConstraint({nm, wg::ConstraintType::GT, fact});
    }
}

void tiledef_add_comb_nm_constraint(tiledef* tiledef, comb_nm* nm, int type, double fact) {
    if(type == CONSTRAINT_LT) {
        tiledef->addConstraint({nm, wg::ConstraintType::LT, fact});
    } else {
        tiledef->addConstraint({nm, wg::ConstraintType::GT, fact});
    }
}

// CombinationNoiseMap
void comb_nm_add_rand_nm(comb_nm* nm, rand_nm* other, int factor) {
    nm->add(other, factor);
}

void comb_nm_add_comb_nm(comb_nm* nm, comb_nm* other, int factor) {
    nm->add(other, factor);
}

double comb_nm_get_value(comb_nm* nm, int x, int y) {
    return nm->getValue(x, y);
}

// RandomNoiseMap
void rand_nm_set_seed(rand_nm* nm, const char* seed) {
    nm->setSeed(std::string(seed));
}

void rand_nm_set_gridsize(rand_nm* nm, double width, double height) {
    nm->setGridSize(width, height);
}

void rand_nm_set_gridwidth(rand_nm* nm, double width) {
    nm->setGridWidth(width);
}

void rand_nm_set_gridheight(rand_nm* nm, double height) {
    nm->setGridHeight(height);
}

void rand_nm_set_octaves(rand_nm* nm, int octaves) {
    nm->setOctaves(octaves);
}

void rand_nm_set_frequency(rand_nm* nm, double frequency) {
    nm->setFrequency(frequency);
}

void rand_nm_set_persistence(rand_nm* nm, double persistence) {
    nm->setPersistence(persistence);
}

void rand_nm_set_lacunarity(rand_nm* nm, double lacunarity) {
    nm->setLacunarity(lacunarity);
}

double rand_nm_get_gridwidth(rand_nm* nm) {
    return nm->getGridWidth();
}

double rand_nm_get_gridheight(rand_nm* nm) {
    return nm->getGridHeight();
}

int rand_nm_get_octaves(rand_nm* nm) {
    return nm->getOctaves();
}

double rand_nm_get_frequency(rand_nm* nm) {
    return nm->getFrequency();
}

double rand_nm_get_persistence(rand_nm* nm) {
    return nm->getPersistence();
}

double rand_nm_get_lacunarity(rand_nm* nm) {
    return nm->getLacunarity();
}

double rand_nm_get_value(rand_nm* nm, int x, int y) {
    return nm->getValue(x, y);
}

// World
world* world_new() {
    return new wg::World();
}

void world_delete(world* world) {
    delete world;
}

void world_set_chunksize(world* world, int width, int height) {
    world->setChunkSize(width, height);
}

void world_set_chunkwidth(world* world, int width) {
    world->setChunkWidth(width);
}

void world_set_chunkheight(world* world, int height) {
    world->setChunkHeight(height);
}

rand_nm* world_add_rand_nm(world* world) {
    return world->addRandomNoiseMap();
}

comb_nm* world_add_comb_nm(world* world) {
    return world->addCombinationNoiseMap();
}

tiledef* world_add_tiledef(world* world) {
    return world->addTileDefinition();
}

void world_generate(world* world, int chunkx, int chunky) {
    world->generate(chunkx, chunky);
}

int world_get_chunkwidth(world* world) {
    return world->getChunkWidth();
}

int world_get_chunkheight(world* world) {
    return world->getChunkHeight();
}

unsigned int world_get_tile(world* world, int x, int y) {
    return world->getTile(x, y);
}

