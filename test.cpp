/////////////////////////////////////////////////////////////////////////////
// Project: World Generation Library
// File: test.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstdlib>

#include "src/inc/noisemap.hpp"
#include "src/inc/world.hpp"

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

	w->generate(0, 0);

	std::cout << nMap1->getValue(10, 10) << std::endl
		<< nMap2->getValue(10, 10) << std::endl
		<< nMap3->getValue(10, 10) << std::endl;

} // int main(int argc, char* argv[]);
