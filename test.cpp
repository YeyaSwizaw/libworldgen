#include <iostream>
#include <cstdlib>

#include "src/inc/worldgen.hpp"

int main(int argc, char* argv[]) {
	WG::WorldGen wg;

	wg.setMapHeight(40);
	wg.setMapWidth(80);
	
	srand(time(NULL));

	int heightmap = wg.addNoiseMap();
	wg.setNoiseSeed(heightmap, rand());
	wg.setNoiseX1(heightmap, 3);
	wg.setNoiseY1(heightmap, 2);

	int rainfall = wg.addNoiseMap();
	wg.setNoiseSeed(rainfall, rand());
	wg.setNoiseX1(rainfall, 1.5);
	wg.setNoiseY1(rainfall, 1);

	int tileWater = wg.defineTile({WG::TileConstraint(heightmap, WG::Less, -0.4)});
	int tileSwamp = wg.defineTile({WG::TileConstraint(heightmap, WG::Less, 0), WG::TileConstraint(rainfall, WG::Greater, 0.3)});
	int tileMnt = wg.defineTile({WG::TileConstraint(heightmap, WG::Greater, 0.2), WG::TileConstraint(heightmap, WG::Less, 0.6)});
	int tileHighMnt = wg.defineTile({WG::TileConstraint(heightmap, WG::Greater, 0.6)});
	int tilePlains = wg.defineTile({});

	wg.generateWorld();

	for(auto r : wg.getTileMap()) {
		for(auto t : r) {
			if(t == tileWater) {
				std::cout << "[1;34m";

			} // if(t == tileWater);
			else if(t == tileSwamp) {
				std::cout << "[1;32m";

			} // else if(t == tileSwamp);
			else if(t == tileMnt) {
				std::cout << "[0;37m";

			} // else if(t == tileMnt);
			else if(t == tileHighMnt) {
				std::cout << "[1;37m";

			} // else if(t == tileHighMnt);
			else if(t == tilePlains) {
				std::cout << "[0;32m";

			} // else if(t == tilePlains);

			std::cout << t << " ";

		} // for(auto t : r);

		std::cout << "\n";

	} // for(auto r : wg.generateWorld());

	std::cout << "[0m";

} // int main(int argc, char* argv[]);
