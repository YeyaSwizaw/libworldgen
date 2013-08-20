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

#include <memory>
#include <vector>
#include <string>

#include "defines.hpp"
#include "generator.hpp"

#include <noise/noise.h>

WG_NS

class NoiseMap : public std::enable_shared_from_this<NoiseMap> {
public:
	typedef std::shared_ptr<NoiseMap> Ptr;

	static Ptr create() { return Ptr(new NoiseMap()); }
	static Ptr combination() { return Ptr(new NoiseMap(true)); }

	Ptr setSeed(std::string seed) { this->seed = seed; return shared_from_this(); }
	Ptr setGridSize(double value) { this->gridSizeX = value; this->gridSizeY = value; return shared_from_this(); }
	Ptr setGridSize(double width, double height) { this->gridSizeX = width; this->gridSizeY = height; return shared_from_this(); }
	Ptr setGridWidth(double value) { this->gridSizeX = value; return shared_from_this(); }
	Ptr setGridHeight(double value) { this->gridSizeY = value; return shared_from_this(); }
	Ptr setOctaves(int value) { this->octaves = value; return shared_from_this(); }
	Ptr setFrequency(double value) { this->frequency = value; return shared_from_this(); }
	Ptr setPersistence(double value) { this->persistence = value; return shared_from_this(); }
	Ptr setLacunarity(double value) { this->lacunarity = value; return shared_from_this(); }

	std::string getSeed() { return seed; }
	double getGridWidth() { return gridSizeX; }
	double getGridHeight() { return gridSizeY; }
	int getOctaves() { return octaves; }
	double getFrequency() { return frequency; }
	double getPersistence() { return persistence; }
	double getLacunarity() { return lacunarity; }
	bool isGenerated() { return generated; }

	Ptr add(Ptr noiseMap, int factor);

	Ptr generate(int width, int height);

	double getValue(int x, int y) { return noiseVals[y][x]; }
	std::vector<std::vector<double>> getValues() { return noiseVals; }

private:
	NoiseMap();
	NoiseMap(bool combination);

	std::string seed;
	double gridSizeX, gridSizeY;
	int octaves;
	double frequency;
	double persistence;
	double lacunarity;

	bool isCombination;
	std::vector<std::pair<Ptr, int>> combinations;

	void genNormal(int width, int height);
	void genCombination(int width, int height);

	bool generated;

	std::vector<std::vector<double>> noiseVals;

}; // class NoiseMap;

WG_NS_END

#endif // WG_NOISEMAP_HPP
