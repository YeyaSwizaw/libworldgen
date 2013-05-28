#ifndef WG_WORLDGEN_HPP
#define WG_WORLDGEN_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <initializer_list>
#include <algorithm>
#include <unordered_map>

#include "defines.hpp"
#include "noisemap.hpp"

#include <noise/noise.h>

WG_NS

enum ConstraintOp {
	Greater,
	Less

}; // enum ConstraintOp;

struct TileConstraint {
	int nId;
	ConstraintOp op;
	double val;

	TileConstraint(int nId, ConstraintOp op, double val)
		: nId(nId), op(op), val(val) {}

}; // struct TileConstraint;

class WorldGen {
public:
	WorldGen();

	int addNoiseMap();
	void removeNoiseMap(int id);
	NoiseMap* getNoiseMap(int id);

	void setMapHeight(int value) { mapHeight = value; }
	void setMapWidth(int value) { mapWidth = value; }
	int getMapHeight() { return mapHeight; }
	int getMapWidth() { return mapWidth; }

	void setNoiseSeed(int id, double value);
	void setNoiseX0(int id, double value);
	void setNoiseX1(int id, double value);
	void setNoiseY0(int id, double value);
	void setNoiseY1(int id, double value);
	void setNoiseOctaveCount(int id, int value);
	void setNoiseFrequency(int id, double value);
	void setNoisePersistence(int id, double value);
	void setNoiseLacunarity(int id, double value);

	double getNoiseSeed(int id);
	double getNoiseX0(int id);
	double getNoiseX1(int id);
	double getNoiseY0(int id);
	double getNoiseY1(int id);
	int getNoiseOctaveCount(int id);
	double getNoiseFrequency(int id);
	double getNoisePersistence(int id);
	double getNoiseLacunarity(int id);

	int defineTile(std::initializer_list<TileConstraint> thresholds);
	int defineTile(std::vector<TileConstraint> thresholds);

	void generateWorld();

private:
	int mapWidth, mapHeight;

	int nextId;
	std::unordered_map<int, NoiseMap*> noiseMaps;

	int nextTileId;
	std::vector<std::pair<std::vector<TileConstraint>, int>> tileDefinitions;

	noise::module::Perlin perlin;

}; // class WorldGen;

WG_NS_END

#endif // WG_WORLDGEN_HPP
