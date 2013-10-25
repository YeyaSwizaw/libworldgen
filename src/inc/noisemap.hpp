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

/**
 * The base noise map class.
 * As with WorldBase, this class should not be used directly, and one of the
 * classes that inherit from it should be used instead.
 */
class NoiseMap {
public:
	/**
	 * Enum of noise map types.
	 * Each value corresponds to a noise map class, eg Random = RandomNoiseMap
	 */
	enum MapType {
		Random,
		Combination,
		Selector

	}; // enum MapType;

	/**
	 * Gets the type of noise map.
	 *
	 * @return The noise map type.
	 */
	MapType getType() { return mapType; }

	/**
	 * Checks if the noise map is a combination of other noisemaps.
	 * If the noisemap is of type Random, returns true, otherwise false.
	 *
	 * @return Whether the noisemap is a combination.
	 */
	bool isCombination() { return !(mapType == MapType::Random); }

	/**
	 * Checks if the noisemap is generated.
	 *
	 * @return Whether the noisemap is generated.
	 */
	bool isGenerated() { return generated; }

	/**
	 * Gets a specific value.
	 * Gets the noisemap value at a specific coordinate.
	 *
	 * @param x The x coordinate of the value.
	 * @param y The y coordinate of the value.
	 * @return The noisemap value.
	 */
	double getValue(int x, int y) { return noiseVals[y][x]; }

	/**
	 * Gets the entire noisemap.
	 * Gets the complete generated noisemap, as a vector of vectors of
	 * doubles. The vector is of rows, so should be accessed y, then x.
	 *
	 * @return The generated noiemap values.
	 */
	std::vector<std::vector<double>> getValues() { return noiseVals; }

protected:
	NoiseMap(MapType mapType);

private:
	friend class TileDef;
	friend class World;

	template<typename _t>
	friend class WorldBase;

	template<typename _tp>
	friend class EnhancedWorld;

	MapType mapType;
	bool generated;
	std::vector<std::vector<double>> noiseVals;

}; // class NoiseMap;

/**
 * This class is a randomly generated noisemap.
 * A noisemap which gets generated
 * based on a large number of parameters. It is then combined either
 * by other noisemaps or TileDef constraints to generate the complete
 * world.
 *
 * To create one, use World::addRandomNoiseMap()
 */
class RandomNoiseMap : public NoiseMap {
public:
	/**
	 * Sets the noisemap seed.
	 *
	 * @param seed The new seed for the noisemap.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setSeed(std::string seed) { this->seed = seed; return this; }

	/**
	 * Sets the noisemap grid size.
	 *
	 * @param value The width and height of the grid.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setGridSize(double value) { this->gridSizeX = value; this->gridSizeY = value; return this; }

	/**
	 * Sets the noisemap grid size.
	 *
	 * @param width The width of the grid.
	 * @param height The height of the grid.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setGridSize(double width, double height) { this->gridSizeX = width; this->gridSizeY = height; return this; }

	/**
	 * Sets the noisemap grid width.
	 *
	 * @param value The width of the grid.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setGridWidth(double value) { this->gridSizeX = value; return this; }

	/**
	 * Sets the noisemap grid height.
	 *
	 * @param value The height of the grid.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setGridHeight(double value) { this->gridSizeY = value; return this; }

	/**
	 * Sets the number of octaves for the noise.
	 *
	 * @param value The new number of noise octaves.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setOctaves(int value) { this->octaves = value; return this; }

	/**
	 * Sets the noise frequency.
	 *
	 * @param value The new frequency.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setFrequency(double value) { this->frequency = value; return this; }

	/**
	 * Sets the noise persistence.
	 *
	 * @param value The new persistence.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setPersistence(double value) { this->persistence = value; return this; }

	/**
	 * Sets the noise lacunarity.
	 *
	 * @param value The new lacunarity.
	 * @return this, for method chaining.
	 */
	RandomNoiseMap* setLacunarity(double value) { this->lacunarity = value; return this; }

	/**
	 * Gets the noise seed.
	 *
	 * @return The noise seed.
	 */
	std::string getSeed() { return seed; }

	/**
	 * Gets the grid width.
	 *
	 * @return The grid width.
	 */
	double getGridWidth() { return gridSizeX; }

	/**
	 * Gets the grid height.
	 *
	 * @return The grid height.
	 */
	double getGridHeight() { return gridSizeY; }

	/**
	 * Gets the number of noise octaves.
	 *
	 * @return The number of noise octaves.
	 */
	int getOctaves() { return octaves; }

	/**
	 * Gets the noise frequency.
	 *
	 * @return The noise frequency.
	 */
	double getFrequency() { return frequency; }

	/**
	 * Gets the noise persistence.
	 *
	 * @return The noise persistence.
	 */
	double getPersistence() { return persistence; }

	/**
	 * Gets the noise lacunarity.
	 *
	 * @return The noise lacunarity.
	 */
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

/**
 * A combination of other noisemaps.
 * This class takes other noisemaps, and combines them all to make
 * a new one. To do this, for each tile, it multiplies the value of each 
 * map added to it by it's factor, then divides the total by the sum
 * of all the factors.
 */
class CombinationNoiseMap : public NoiseMap {
public:
	/**
	 * Adds a noisemap to be combined.
	 * Takes a noisemap and a scaling factor and pushes them to the
	 * combinations vector.
	 *
	 * @param mapToAdd The noisemap to be added.
	 * @param factor The scaling factor of the noisemap.
	 * @return this, for method chaining.
	 */
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
