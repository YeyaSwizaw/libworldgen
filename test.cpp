/////////////////////////////////////////////////////////////////////////////
// Project: World Generation Library
// File: test.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstdlib>

#include "src/inc/world.hpp"
#include "src/inc/noisemap.hpp"
#include "src/inc/tiledef.hpp"

int main(int argc, char* argv[]) {
	srand(time(NULL));

	wg::World* w = (new wg::World())->setChunkSize(30);

	wg::RandomNoiseMap* nMap1 = w->addRandomNoiseMap()
		->setSeed(std::to_string(rand()))
		->setGridSize(0.05);

	wg::RandomNoiseMap* nMap2 = w->addRandomNoiseMap()
		->setSeed(std::to_string(rand()))
		->setGridSize(0.02);

	wg::CombinationNoiseMap* nMap3 = w->addCombinationNoiseMap()
		->add(nMap1, 10)
		->add(nMap2, 20);

	wg::TileDef* t1 = w->addTileDefinition()
		->addConstraint({nMap3, wg::ConstraintType::LT, 0});

	for(auto row : w->generate(0, 0)->getMap()) {
		for(unsigned int t : row) {
			std::cout << t;

		} // for(unsigned int t : row);

		std::cout << std::endl;

	} // for(auto row : w->generate(0, 0)->getMap());

	std::cout << std::endl;

} // int main(int argc, char* argv[]);
