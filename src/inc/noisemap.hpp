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

#include <string>
#include <vector>
#include <utility>

#include <noise/module/perlin.h>

#include "defines.hpp"

WG_NS

class World;
class TileDef;

template<typename _t>
class WorldBase;

template<typename _tp>
class EnhancedWorld;

class NoiseMap {
protected:
	NoiseMap(bool combination);

public:
	bool isCombination() { return combination; }
	bool isGenerated() { return generated; }

	double getValue(int x, int y) { return noiseVals[y][x]; }
	std::vector<std::vector<double>> getValues() { return noiseVals; }

private:
	friend class TileDef;
	friend class World;

	template<typename _t>
	friend class WorldBase;

	template<typename _tp>
	friend class EnhancedWorld;

	bool combination, generated;
	std::vector<std::vector<double>> noiseVals;

}; // class NoiseMap;

class RandomNoiseMap : public NoiseMap {
public:
	RandomNoiseMap* setSeed(std::string seed) { this->seed = seed; return this; }
	RandomNoiseMap* setGridSize(double value) { this->gridSizeX = value; this->gridSizeY = value; return this; }
	RandomNoiseMap* setGridSize(double width, double height) { this->gridSizeX = width; this->gridSizeY = height; return this; }
	RandomNoiseMap* setGridWidth(double value) { this->gridSizeX = value; return this; }
	RandomNoiseMap* setGridHeight(double value) { this->gridSizeY = value; return this; }
	RandomNoiseMap* setOctaves(int value) { this->octaves = value; return this; }
	RandomNoiseMap* setFrequency(double value) { this->frequency = value; return this; }
	RandomNoiseMap* setPersistence(double value) { this->persistence = value; return this; }
	RandomNoiseMap* setLacunarity(double value) { this->lacunarity = value; return this; }

	std::string getSeed() { return seed; }
	double getGridWidth() { return gridSizeX; }
	double getGridHeight() { return gridSizeY; }
	int getOctaves() { return octaves; }
	double getFrequency() { return frequency; }
	double getPersistence() { return persistence; }
	double getLacunarity() { return lacunarity; }

private:
	template<typename _t>
	friend class WorldBase;

	template<typename _tp>
	friend class EnhancedWorld;

	RandomNoiseMap();

	std::string seed;
	double gridSizeX, gridSizeY;
	int octaves;
	double frequency;
	double persistence;
	double lacunarity;

}; // class RandomNoiseMap : public NoiseMap;

class CombinationNoiseMap : public NoiseMap {
public:
	CombinationNoiseMap* add(NoiseMap* mapToAdd, int factor);

private:
	template<typename _t>
	friend class WorldBase;

	template<typename _tp>
	friend class EnhancedWorld;

	CombinationNoiseMap();

	std::vector<std::pair<NoiseMap*, int>> combinations;

}; // class CombinationNoiseMap : public NoiseMap;

WG_NS_END

#endif // WG_NOISEMAP_HPP
