#include <iostream>

#include "src/inc/worldgen.hpp"

int main(int argc, char* argv[]) {
	WG::WorldGen wg;

	wg.setMapHeight(30);
	wg.setMapWidth(60);

	int heightmap = wg.addNoiseMap();
	wg.setNoiseSeed(heightmap, 56345735);
	wg.setNoiseX1(heightmap, 2);

	int rainfall = wg.addNoiseMap();
	wg.setNoiseSeed(rainfall, 765438);

	wg.defineTile({WG::TileConstraint(heightmap, WG::Less, -0.4)});
	wg.defineTile({WG::TileConstraint(heightmap, WG::Greater, 0.2)});
	wg.defineTile({WG::TileConstraint(rainfall, WG::Greater, 0)});
	wg.defineTile({});

	wg.generateWorld();

} // int main(int argc, char* argv[]);
