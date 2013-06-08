#include <iostream>
#include <string>
#include <cstdlib>

#include "src/inc/worldgen.hpp"

int main(int argc, char* argv[]) {
	WG::WorldGen wg(80, 40);
	
	srand(time(NULL));

	int hmap1 = wg.addNoiseMap(std::to_string(rand()));
	wg.setNoiseX1(hmap1, 3);
	wg.setNoiseY1(hmap1, 2);

	int hmap2 = wg.addNoiseMap(std::to_string(rand()));
	wg.setNoiseX1(hmap2, 15);
	wg.setNoiseY1(hmap2, 10);

	int heightmap = wg.addNoiseCombination({std::make_pair(hmap1, 20), std::make_pair(hmap2, 5)});

	int rainfall = wg.addNoiseMap(std::to_string(rand()));
	wg.setNoiseX1(rainfall, 1.5);
	wg.setNoiseY1(rainfall, 1);

	int tileWater = wg.defineTile({WG::TileConstraint(heightmap, WG::Less, -0.3)});
	int tileHighMnt = wg.defineTile({WG::TileConstraint(heightmap, WG::Greater, 0.55)});
	int tileMnt = wg.defineTile({WG::TileConstraint(heightmap, WG::Greater, 0.2)});
	int tileDesert = wg.defineTile({WG::TileConstraint(rainfall, WG::Less, -0.3)});
	int tilePlains = wg.defineTile({});

	wg.generateWorld();

	std::cout << wg.getNoiseSeed(hmap1) << ";" << wg.getNoiseSeed(hmap2) << ";" << wg.getNoiseSeed(rainfall) << "\n";
	for(auto r : wg.getTileMap()) {
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

	} // for(auto r : wg.generateWorld());

	std::cout << "[0m";

} // int main(int argc, char* argv[]);
