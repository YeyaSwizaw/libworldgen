/////////////////////////////////////////////////////////////////////////////
// Project: World Generation Library
// File: test.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstdlib>

#include "src/inc/noisemap.hpp"
#include "src/inc/tiledef.hpp"
#include "src/inc/world.hpp"

int main(int argc, char* argv[]) {
	// Seed random number gen.
	srand(time(NULL));

	// Create noise maps, with random seed
	wg::NoiseMap::Ptr hmap1 = wg::NoiseMap::create()
		->setSeed(std::to_string(rand()))
		->setGridSize(0.05);

	wg::NoiseMap::Ptr hmap2 = wg::NoiseMap::create()
		->setSeed(std::to_string(rand()))
		->setGridSize(0.5);

	wg::NoiseMap::Ptr heightmap = wg::NoiseMap::combination()
		->add(hmap1, 20)->add(hmap2, 5);

	wg::NoiseMap::Ptr rainfall = wg::NoiseMap::create()
		->setSeed(std::to_string(rand()))
		->setGridSize(0.01);

	// Create world
	wg::World::Ptr w = wg::World::create()
		->setChunkSize(40, 40);

	// Set tile definitions
	wg::TileDef::Ptr tileWater = w->newTile()->addConstraint(heightmap < -0.3);
	wg::TileDef::Ptr tileHighMnt = w->newTile()->addConstraint(heightmap > 0.55);
	wg::TileDef::Ptr tileMnt = w->newTile()->addConstraint(heightmap > 0.2);
	wg::TileDef::Ptr tileDesert = w->newTile()->addConstraint(rainfall < -0.3);
	wg::TileDef::Ptr tilePlains = w->newTile();

	// Generate the world (specifically the chunk of world at 0,0)
	w->generate(0, 0);

	// Output world (looks nice on linux, windows will spew codes or something)
	for(auto r : w->getMap()) {
		for(auto t : r) {
			if(t == tileWater->getId()) {
				std::cout << "[0;34m";

			} // if(t == tileWater);
			else if(t == tileMnt->getId()) {
				std::cout << "[0;37m";

			} // else if(t == tileMnt);
			else if(t == tileHighMnt->getId()) {
				std::cout << "[1;37m";

			} // else if(t == tileHighMnt);
			else if(t == tilePlains->getId()) {
				std::cout << "[0;32m";

			} // else if(t == tilePlains);
			else if(t == tileDesert->getId()) {
				std::cout << "[0;33m";

			} // else if(t == tileDesert);

			std::cout << t << " ";

		} // for(auto t : r);

		std::cout << "\n";

	} // for(auto r : w->getTileMap());

	std::cout << "[0m";

} // int main(int argc, char* argv[]);
