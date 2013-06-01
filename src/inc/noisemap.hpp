#ifndef WG_NOISEMAP_HPP
#define WG_NOISEMAP_HPP

#include <vector>

#include "defines.hpp"

#include <noise/noise.h>

WG_NS

typedef std::vector<std::vector<double>> NoiseValues;

class WorldGen;

class NoiseMap {
private:
	friend class WorldGen;
	NoiseMap(double seed, double x0, double x1, double y0, double y1,
			int octaves, double frequency, double persistence, double lacunarity);

	NoiseMap(std::vector<std::pair<int, int>> cmbVect);
	
	double seed;
	double x0, x1;
	double y0, y1;
	int octaves;
	double frequency;
	double persistence;
	double lacunarity;

	NoiseValues noiseVals;
	void addRow();
	void addValue(double value);

	std::vector<double> noiseThresholds;

	bool isCombination;
	std::vector<std::pair<int, int>> combinations;

}; // class NoiseMap;

WG_NS_END

#endif // WG_NOISEMAP_HPP
