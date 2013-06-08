/////////////////////////////////////////////////////////////////////////////
// Copyright 2013 Samuel Sleight
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/////////////////////////////////////////////////////////////////////////////
// Project: World Generation Library
// File: src/inc/noisemap.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_NOISEMAP_HPP
#define WG_NOISEMAP_HPP

#include <vector>
#include <string>

#include "defines.hpp"

#include <noise/noise.h>

WG_NS

typedef std::vector<std::vector<double>> NoiseValues;

class WorldGen;

class NoiseMap {
private:
	friend class WorldGen;
	NoiseMap(std::string seed, double x0, double x1, double y0, double y1,
			int octaves, double frequency, double persistence, double lacunarity);

	NoiseMap(std::vector<std::pair<int, int>> cmbVect);
	
	std::string seed;
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
