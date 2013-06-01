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
	WorldGen(int mapWidth = WG_DEF_W, int mapHeight = WG_DEF_H);

	int addNoiseMap(double seed = 0, 
			double x0 = WG_DEF_X0, double x1 = WG_DEF_X1,
			double y0 = WG_DEF_Y0, double y1 = WG_DEF_Y1,
			int octaves = WG_DEF_OCTAVES,
			double frequency = WG_DEF_FREQ,
			double persistence = WG_DEF_PERS,
			double lacunarity = WG_DEF_LACU);

	void removeNoiseMap(int id);

	int addNoiseCombination(std::initializer_list<std::pair<int, int>> combList);
	int addNoiseCombination(std::vector<std::pair<int, int>> combVect);

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
	void deleteTile(int id);

	void generateWorld();
	std::vector<std::vector<int>> getTileMap();
	std::vector<std::vector<double>> getNoiseMap(int id);

private:
	int mapWidth, mapHeight;

	int nextId;
	std::unordered_map<int, NoiseMap*> noiseMaps;

	std::vector<int> cmbPriorities;

	int nextTileId;
	std::unordered_map<int, std::vector<TileConstraint>> tileDefinitions;
	std::vector<int> tilePriorities;

	std::vector<std::vector<int>> finalMap;

	noise::module::Perlin perlin;

}; // class WorldGen;

WG_NS_END

#endif // WG_WORLDGEN_HPP
