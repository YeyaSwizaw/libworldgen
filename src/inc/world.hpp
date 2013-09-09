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
// File: src/inc/world.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_WORLD_HPP
#define WG_WORLD_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <noise/module/perlin.h>

#include "defines.hpp"

WG_NS

class NoiseMap;
class RandomNoiseMap;
class CombinationNoiseMap;
class TileDef;

class World {
public:
	World();

	World* setChunkSize(int width, int height) { chunkWidth = width; chunkHeight = height; return this; }
	World* setChunkSize(int value) { chunkWidth = value; chunkHeight = value; return this; }
	World* setChunkWidth(int value) { chunkWidth = value; return this; }
	World* setChunkHeight(int value) { chunkHeight = value; return this; }

	RandomNoiseMap* addRandomNoiseMap();
	CombinationNoiseMap* addCombinationNoiseMap();

	TileDef* addTileDefinition();

	World* generate(int xChunk, int yChunk);

	std::vector<std::vector<unsigned int>> getMap() { return this->mapGrid; }
	unsigned int getTile(int x, int y) { return mapGrid[y][x]; }

private:
	int chunkWidth, chunkHeight;

	noise::module::Perlin perlinModule;

	std::vector<NoiseMap*> noiseMaps;
	std::vector<TileDef*> tileDefinitions;

	std::vector<std::vector<unsigned int>> mapGrid;

	void generateRandom(RandomNoiseMap* nMap);
	void generateCombination(CombinationNoiseMap* nMap);
	void setTiles();

}; // class World;

WG_NS_END

#endif // WG_WORLD_HPP
