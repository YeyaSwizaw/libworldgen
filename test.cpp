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
		->setSeed(std::to_string(rand()));

	wg::CombinationNoiseMap* nMap2 = w->addCombinationNoiseMap()
		->add(nMap1, 10);

} // int main(int argc, char* argv[]);
