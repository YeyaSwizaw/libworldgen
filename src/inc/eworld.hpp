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
// File: src/inc/eworld.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_EWORLD_HPP
#define WG_EWORLD_HPP

#include <map>
#include <vector>

#include "defines.hpp"
#include "worldbase.hpp"
#include "noisemap.hpp"
#include "tiledef.hpp"

WG_NS

template<typename _tp>
class EnhancedWorld;

/**
 * A world class that creates a map of objects of a given type, as well
 * as the map of tile ids.
 *
 *     EnhancedWorld<std::string>* w = (new World())->setChunkSize(50);
 *
 *     RandomNoiseMap* heightmap = w->addRandomNoiseMap()
 *         ->setSeed(std::to_string(rand()))
 *         ->setGridSize(0.05);
 *
 *     TileDef* water = w->addTileDefinition("~")
 *         ->addConstraint({heightmap, ConstraintType::LT, 0});
 *
 *     TileDef* grass = w->addTileDefinition("#");
 *
 *     for(auto row : : w->generate(0, 0)->getObjects()) {
 *         for(auto tile : row) {
 *             std::cout << tile;
 *         }
 *
 *         std::cout << std::endl;
 *     }
 *
 * Notice that addTileDefinition now takes a parameter of type _tp. This is 
 * the object that the map will contain for this tile. In this example, the
 * map will contain "~"s and "#"s.
 *
 * @tparam _tp The type of object for the map.
 */
template<typename _tp>
class EnhancedWorld : public WorldBase<EnhancedWorld<_tp>> {
public:
	EnhancedWorld();

	/**
	 * Adds a new TileDef.
	 * Creates a new TileDef, adds a pointer to the tileDefinitions
	 * vector, and returns a pointer. It also adds an entry to the 
	 * mappedObjects std::map, mapping the tile's id to the given object.
	 *
	 * @param object The object this tile maps to.
	 * @return A pointer to the new TileDef.
	 */
	TileDef* addTileDefinition(_tp object);

	/**
	 * Generates the given chunk of world.
	 * In more detail, it iterates through the noiseMaps vector and
	 * generates all of the noisemaps, and then populates the mapGrid with
	 * the id of the the first valid TileDef for each tile. It then iterates
	 * over the mapGrid and populates the object map with each tile's
	 * respective object.
	 *
	 * @param x The x value of the chunk to be generated.
	 * @param y The y value of the chunk to be generated.
	 * @return this, for method chaining.
	 */
	EnhancedWorld<_tp>* generate(int xChunk, int yChunk);

	/**
	 * Gets a specific object.
	 * Returns the object from the generated world at the given tile.
	 *
	 * @param x The x location of the object.
	 * @param y The y location of the object.
	 * @return The object at the given location.
	 */
	_tp getObject(int x, int y) { return mappedObjMap[y][x]; }

	/**
	 * Gets the entire object map.
	 * Returns the complete generated world, as a vector of vectors of
	 * objects. In rows, as with getMap().
	 *
	 * @return The world's object vector.
	 */
	std::vector<std::vector<_tp>> getObjects() { return mappedObjMap; }

private:
	std::map<unsigned int, _tp> mappedObjects;
	std::vector<std::vector<_tp>> mappedObjMap;

	void mapObjects();

}; // class EnhancedWorld<_tp> : public WorldBase<EnhancedWorld<_tp>>;

#include "eworld.tpp"

WG_NS_END

#endif // WG_EWORLD_HPP
