#include "inc/noisemap.hpp"

WG_NS

NoiseMap::NoiseMap(std::string seed, double x0, double x1, double y0, double y1, 
		int octaves, double frequency, double persistence, double lacunarity) 
	: seed(seed),
	  x0(x0), x1(x1), y0(y0), y1(y1),
	  octaves(octaves),
	  frequency(frequency),
	  persistence(persistence),
	  lacunarity(lacunarity),
	  isCombination(false) {

} // NoiseMap::NoiseMap(std::string seed, double x0, double x1, double y0, double y1, 
		//int octaves, double frequency, double persistence, double lacunarity);

NoiseMap::NoiseMap(std::vector<std::pair<int, int>> cmbVect) 
	: isCombination(true),
	  combinations(cmbVect) {

} // NoiseMap::NoiseMap(std::vector<std::pair<int, int>> cmbVect);

void NoiseMap::addRow() {
	noiseVals.push_back(std::vector<double>());

} // void NoiseMap::addRow();

void NoiseMap::addValue(double value) {
	noiseVals.back().push_back(value);

} // void NoiseMap::addValue(double value);

WG_NS_END
