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
// File: src/inc/worldbase.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_WORLDBASE_HPP
#define WG_WORLDBASE_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <noise/module/perlin.h>

#include "defines.hpp"
#include "tiledef.hpp"
#include "noisemap.hpp"

WG_NS

template<typename _t>
class WorldBase {
public:
	_t* setChunkSize(int width, int height) { chunkWidth = width; chunkHeight = height; return static_cast<_t*>(this); }
	_t* setChunkSize(int value) { chunkWidth = value; chunkHeight = value; return static_cast<_t*>(this); }
	_t* setChunkWidth(int value) { chunkWidth = value; return static_cast<_t*>(this); }
	_t* setChunkHeight(int value) { chunkHeight = value; return static_cast<_t*>(this); }

	RandomNoiseMap* addRandomNoiseMap();
	CombinationNoiseMap* addCombinationNoiseMap();

	std::vector<std::vector<unsigned int>> getMap() { return this->mapGrid; }
	unsigned int getTile(int x, int y) { return mapGrid[y][x]; }

protected:
	WorldBase();

	int chunkWidth, chunkHeight;

	noise::module::Perlin perlinModule;

	std::vector<NoiseMap*> noiseMaps;
	std::vector<TileDef*> tileDefinitions;

	std::vector<std::vector<unsigned int>> mapGrid;

	void generateRandom(RandomNoiseMap* nMap);
	void generateCombination(CombinationNoiseMap* nMap);
	void setTiles();

}; // class WorldBase;

#include "worldbase.tpp"

WG_NS_END

#endif // WG_WORLDBASE_HPP
