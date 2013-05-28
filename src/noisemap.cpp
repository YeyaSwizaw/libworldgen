#include "inc/noisemap.hpp"

WG_NS

NoiseMap::NoiseMap()
	: seed(0),
	  x0(WG_DEF_X0), x1(WG_DEF_X1),
	  y0(WG_DEF_Y0), y1(WG_DEF_Y1),
	  octaves(WG_DEF_OCTAVES),
	  frequency(WG_DEF_FREQ),
	  persistence(WG_DEF_PERS),
	  lacunarity(WG_DEF_LACU) {

} // NoiseMap::NoiseMap();

void NoiseMap::addRow() {
	noiseVals.push_back(std::vector<double>());

} // void NoiseMap::addRow();

void NoiseMap::addValue(double value) {
	noiseVals.back().push_back(value);

} // void NoiseMap::addValue(double value);

WG_NS_END
