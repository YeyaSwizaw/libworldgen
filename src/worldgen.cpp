#include "inc/worldgen.hpp"

WG_NS

WorldGen::WorldGen()
	: mapWidth(WG_DEF_W), mapHeight(WG_DEF_H),
	  nextId(0), nextTileId(0) {

} // WorldGen::WorldGen();

int WorldGen::addNoiseMap() {
	noiseMaps.insert(std::make_pair(nextId, new NoiseMap));
	nextId++;

	return (nextId - 1);

} // int WorldGen::addNoiseMap();

void WorldGen::removeNoiseMap(int id) {
	delete (noiseMaps.at(id));
	noiseMaps.erase(id);

} // void WorldGen::removeNoiseMap(int id);

NoiseMap* WorldGen::getNoiseMap(int id) {
	return noiseMaps.at(id);

} // NoiseMap* WorldGen::getNoiseMap(int id);

void WorldGen::setNoiseSeed(int id, double value) {
	noiseMaps.at(id)->seed = value;

} // void WorldGen::setNoiseSeed(int id, double value);

void WorldGen::setNoiseX0(int id, double value) {
	noiseMaps.at(id)->x0 = value;

} // void WorldGen::setNoiseX0(int id, double value);

void WorldGen::setNoiseX1(int id, double value) {
	noiseMaps.at(id)->x1 = value;

} // void WorldGen::setNoiseX1(int id, double value);

void WorldGen::setNoiseY0(int id, double value) {
	noiseMaps.at(id)->y0 = value;

} // void WorldGen::setNoiseY0(int id, double value);

void WorldGen::setNoiseY1(int id, double value) {
	noiseMaps.at(id)->y1 = value;

} // void WorldGen::setNoiseY1(int id, double value);

void WorldGen::setNoiseOctaveCount(int id, int value) {
	noiseMaps.at(id)->octaves = value;

} // void WorldGen::setNoiseOctaveCount(int id, double value);

void WorldGen::setNoiseFrequency(int id, double value) {
	noiseMaps.at(id)->frequency = value;

} // void WorldGen::setNoiseFrequency(int id, double value);

void WorldGen::setNoisePersistence(int id, double value) {
	noiseMaps.at(id)->persistence = value;

} // void WorldGen::setNoisePersistence(int id, double value);

void WorldGen::setNoiseLacunarity(int id, double value) {
	noiseMaps.at(id)->lacunarity = value;

} // void WorldGen::setNoiseLacunarity(int id, double value);

double WorldGen::getNoiseSeed(int id) {
	return noiseMaps.at(id)->seed;

} // double WorldGen::getNoiseSeed(int id);

double WorldGen::getNoiseX0(int id) {
	return noiseMaps.at(id)->x0;

} // double WorldGen::getNoiseX0(int id);

double WorldGen::getNoiseX1(int id) {
	return noiseMaps.at(id)->x1;

} // double WorldGen::getNoiseX1(int id);

double WorldGen::getNoiseY0(int id) {
	return noiseMaps.at(id)->y0;

} // double WorldGen::getNoiseY0(int id);

double WorldGen::getNoiseY1(int id) {
	return noiseMaps.at(id)->y1;

} // double WorldGen::getNoiseY1(int id);

int WorldGen::getNoiseOctaveCount(int id) {
	return noiseMaps.at(id)->octaves;

} // int WorldGen::getNoiseOctaveCount(int id);

double WorldGen::getNoiseFrequency(int id) {
	return noiseMaps.at(id)->frequency;

} // double WorldGen::getNoiseFrequency(int id);

double WorldGen::getNoisePersistence(int id) {
	return noiseMaps.at(id)->persistence;

} // double WorldGen::getNoisePersistence(int id);

double WorldGen::getNoiseLacunarity(int id) {
	return noiseMaps.at(id)->lacunarity;

} // double WorldGen::getNouseLacunarity(int id);

int WorldGen::defineTile(std::initializer_list<TileConstraint> thresholds) {
	return defineTile(std::vector<TileConstraint>(thresholds));

} // int WorldGen::defineTile(std::initializer_list<TileConstraint> thresholds);

int WorldGen::defineTile(std::vector<TileConstraint> thresholds) {
	tileDefinitions.push_back(std::make_pair(thresholds, nextTileId));
	
	nextTileId++;
	return (nextTileId - 1);

} // int WorldGen::defineTile(std::vector<TileConstraint> thresholds);

void WorldGen::generateWorld() {
	NoiseMap *nMap;

	for(auto pair : noiseMaps) {
		nMap = pair.second;
		perlin.SetSeed(nMap->seed);
		perlin.SetOctaveCount(nMap->octaves);
		perlin.SetFrequency(nMap->frequency);
		perlin.SetPersistence(nMap->persistence);
		perlin.SetLacunarity(nMap->lacunarity);

		double xStep = (nMap->x1 - nMap->x0) / mapWidth;
		double yStep = (nMap->y1 - nMap->y0) / mapHeight;

		for(double y = nMap->y0; y < nMap->y1; y += yStep) {
			nMap->addRow();

			for(double x = nMap->x0; x < nMap->x1; x += xStep) {
				nMap->addValue(perlin.GetValue(x, y, 0));
				std::cout << x << ", " << y << ", " << "YAY\n";

			} // for(double x = nMap->x0; x < nMap->x1; x += xStep);

		} // for(double y = nMap->y0; y < nMap->y1; y += yStep);

	} // for(NoiseMap *nMap : noiseMaps);

	// TEST vv
	
	bool matchesDefinition = true;
	bool tileFound = false;

	for(int y = 0; y <= mapHeight; y++) {
		for(int x = 0; x <= mapWidth; x++) {
			tileFound = false;
			for(auto tDef : tileDefinitions) {
				matchesDefinition = true;

				for(auto con : tDef.first) {
					if(con.op == Greater) {
						if(!(noiseMaps.at(con.nId)->noiseVals[y][x] >= con.val)) {
							matchesDefinition = false;
							break;

						} // if(noiseMaps.at(con.nId)->noiseVals[y][x] >= con.val);

					} // if(con.op == Greater);
					else {
						if(!(noiseMaps.at(con.nId)->noiseVals[y][x] <= con.val)) {
							matchesDefinition = false;
							break;

						} // if(!(noiseMaps.at(con.nId)->noiseVals[y][x] <= con.val));

					} // else;

				} // for(auto con : tDef.first);

				if(matchesDefinition) {
					std::cout << tDef.second << " ";
					tileFound = true;
					break;

				} // if(matchesDefinition);

			} // for(auto tDef : tileDefinitions);

			if(!tileFound) {
				std::cout << "  ";

			} // if(!tileFound);

		} // for(int x = 0; x < mapWidth; x++);

		std::cout << "\n";

	} // for(int y = 0; y > mapHeight; y++);

} // void WorldGen::generateWorld();

WG_NS_END
