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

#include "defines.hpp"
#include "worldbase.hpp"

WG_NS

/**
 * The standard world class.
 *
 * This is the standard world class, that generates a world based on the
 * given NoiseMaps and TileDefs. The following code shows a working
 * example:
 *
 *     World* w = (new World())->setChunkSize(50);
 *
 *     RandomNoiseMap* heightmap = w->addRandomNoiseMap()
 *         ->setSeed(std::to_string(rand()))
 *         ->setGridSize(0.05);
 *
 *     TileDef* water = w->addTileDefinition()
 *         ->addConstraint({heightmap, ConstraintType::LT, 0});
 *
 *     TileDef* grass = w->addTileDefinition();
 *
 *     for(auto row : : w->generate(0, 0)->getMap()) {
 *         for(auto tile : row) {
 *             std::cout << tile;
 *         }
 *
 *         std::cout << std::endl;
 *     }
 *
 * This will print out a map consisting of 0s and 1s - the ids of the 
 * water and grass tiles respectively.
 */
class World : public WorldBase<World> {
public:
	World();

	/**
	 * Adds a new TileDef.
	 * Creates a new TileDef, adds a pointer to the tileDefinitions
	 * vector, and returns a pointer.
	 *
	 * @return A pointer to the new TileDef.
	 */
	TileDef* addTileDefinition();

	/**
	 * Generates the given chunk of world.
	 * In more detail, it iterates through the noiseMaps vector and
	 * generates all of the noisemaps, and then populates the mapGrid with
	 * the id of the the first valid TileDef for each tile.
	 *
	 * @param x The x value of the chunk to be generated.
	 * @param y The y value of the chunk to be generated.
	 * @return this, for method chaining.
	 */
	World* generate(int xChunk, int yChunk);

}; // class World : public WorldBase<World>;

WG_NS_END

#endif // WG_WORLD_HPP
