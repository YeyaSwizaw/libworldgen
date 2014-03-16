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

/**
 * The base class for all world types (World and EnhancedWorld). This class
 * should not be used directly - the classes that inherit from it should be
 * used instead.
 *
 * @tparam _t The world type that inherits this class, so the functions know
 * what type to return for method chaining.
 */
template<typename _t>
class WorldBase {
public:
	/** 
	 * Sets the size of the generated world chunk.
	 *
	 * @param width The width of the chunk.
	 * @param height The height of the chunk.
	 * @return this, for method chaining.
	 */
	_t* setChunkSize(int width, int height) { chunkWidth = width; chunkHeight = height; return static_cast<_t*>(this); }

	/**
	 * Sets the size of the generated world chunk.
	 *
	 * @param value The width and height of the chunk.
	 * @return this, for method chaining.
	 */
	_t* setChunkSize(int value) { chunkWidth = value; chunkHeight = value; return static_cast<_t*>(this); }

	/**
	 * Sets the width of the generated world chunk.
	 *
	 * @param value The width of the chunk.
	 * @return this, for method chaining.
	 */
	_t* setChunkWidth(int value) { chunkWidth = value; return static_cast<_t*>(this); }

	/**
	 * Sets the height of the generated world chunk.
	 *
	 * @param value The height of the chunk.
	 * @return this, for method chaining.
	 */
	_t* setChunkHeight(int value) { chunkHeight = value; return static_cast<_t*>(this); }

	/**
	 * Adds a new RandomNoiseMap.
	 * Creates a new RandomNoiseMap, adds a pointer to the noiseMaps vector,
	 * and returns a pointer.
	 * 
	 * @return A pointer to the new RandomNoiseMap.
	 */
	RandomNoiseMap* addRandomNoiseMap();

	/**
	 * Adds a new CombinationNoiseMap.
	 * Creates a new CombinationNoiseMap, adds a pointer to the noiseMaps vector,
	 * and returns a pointer.
	 * 
	 * @return A pointer to the new CombinationNoiseMap.
	 */
	CombinationNoiseMap* addCombinationNoiseMap();

	/**
	 * Gets the generated world.
	 * Gets the complete generated world, as a vector of vectors of tile ids.
	 * The vector is of rows, so should be accessed y, then x.
	 *
	 * @return The generated world.
	 */
	std::vector<std::vector<unsigned int>> getMap() { return this->mapGrid; }

	/**
	 * Gets a specific tile.
	 * Gets the id of the tile at a specific coordinate;
	 *
	 * @param x The x coordinate of the tile.
	 * @param y The y coordinate of the tile.
	 * @return The id of the tile.
	 */
	unsigned int getTile(int x, int y) { return mapGrid[y][x]; }

    /**
     * Gets the width of the generated world chunk.
     *
     * @return The chunk width.
     */
    int getChunkWidth() { return chunkWidth; }

    /**
     * Gets the height of the generated world chunk.
     *
     * @return The chunk height.
     */
    int getChunkHeight() { return chunkHeight; }

protected:
	WorldBase();

	int chunkWidth, chunkHeight;

	noise::module::Perlin perlinModule;

	std::vector<NoiseMap*> noiseMaps;
	std::vector<TileDef*> tileDefinitions;

	std::vector<std::vector<unsigned int>> mapGrid;

	void clearNoiseMaps();
	void generateRandom(RandomNoiseMap* nMap, int xChunk, int yChunk);
	void generateCombination(CombinationNoiseMap* nMap, int xChunk, int yChunk);
	void setTiles();

}; // class WorldBase;

#include "worldbase.tpp"

WG_NS_END

#endif // WG_WORLDBASE_HPP
