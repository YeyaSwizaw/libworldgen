/////////////////////////////////////////////////////////////////////////////
// Project: World Generation Library
// File: test.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstdlib>

#include "src/inc/noisemap.hpp"

int main(int argc, char* argv[]) {
	srand(time(NULL));

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

	// wg::World::Ptr w = wg::World::create();

	/*
	wg::TileDef::Ptr tileWater = w->newTile()->addConstraint(heightmap < -0.3);
	wg::TileDef::Ptr tileHighMnt = w->newTile()->addConstraint(heightmap > 0.55);
	wg::TileDef::Ptr tileMnt = w->newTile()->addConstraint(heightmap > 0.2);
	wg::TileDef::Ptr tileDesert = w->newTile()->addConstraint(rainfall < -0.3);
	wg::TileDef::Ptr tilePlains = w->newTile();
	*/

	rainfall->generate(10, 10);
	heightmap->generate(10, 10);

	std::cout << hmap1->getSeed() << ";" << hmap2->getSeed() << ";" << rainfall->getSeed() << std::endl;

	for(auto vals : rainfall->getValues()) {
		for(double v : vals) {
			std::cout << v << ",";

		} // for(double v : vals);

		std::cout << std::endl;

	} // for(auto vals : rainfall->getValues());

	std::cout << std::endl;

	for(auto vals : heightmap->getValues()) {
		for(double v : vals) {
			std::cout << v << ",";

		} // for(double v : vals);

		std::cout << std::endl;

	} // for(auto vals : rainfall->getValues());



	/*;
	for(auto r : w->getTileMap()) {
		for(auto t : r) {
			if(t == tileWater) {
				std::cout << "[0;34m";

			} // if(t == tileWater);
			else if(t == tileMnt) {
				std::cout << "[0;37m";

			} // else if(t == tileMnt);
			else if(t == tileHighMnt) {
				std::cout << "[1;37m";

			} // else if(t == tileHighMnt);
			else if(t == tilePlains) {
				std::cout << "[0;32m";

			} // else if(t == tilePlains);
			else if(t == tileDesert) {
				std::cout << "[0;33m";

			} // else if(t == tileDesert);

			std::cout << t << " ";

		} // for(auto t : r);

		std::cout << "\n";

	} // for(auto r : w->getTileMap());

	std::cout << "[0m";
	*/

} // int main(int argc, char* argv[]);
