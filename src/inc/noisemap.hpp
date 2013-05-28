#ifndef WG_NOISEMAP_HPP
#define WG_NOISEMAP_HPP

#include <vector>

#include "defines.hpp"

#include <noise/noise.h>

WG_NS

typedef std::vector<std::vector<double>> NoiseValues;

class WorldGen;

class NoiseMap {
public:
	NoiseMap();

	typedef NoiseValues::iterator iterator;
	typedef NoiseValues::const_iterator const_iterator;
	iterator begin() { return noiseVals.begin(); }
	const_iterator begin() const { return noiseVals.begin(); }
	iterator end() { return noiseVals.end(); }
	const_iterator end() const { return noiseVals.end(); }

	std::vector<double> operator[](int v) { return noiseVals[v]; }
	
private:
	friend class WorldGen;
	
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

}; // class NoiseMap;

WG_NS_END

#endif // WG_NOISEMAP_HPP
