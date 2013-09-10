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
// File: src/world.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include "inc/world.hpp"
#include "inc/noisemap.hpp"

WG_NS

World::World()
	: WorldBase<World>() {

} // World::World();

TileDef* World::addTileDefinition() {
	tileDefinitions.push_back(new TileDef);

	return tileDefinitions.back();

} // TileDef* World::addTileDefinition();

World* World::generate(int xChunk, int yChunk) {
	clearNoiseMaps();

	for(NoiseMap* nMap : noiseMaps) {
		if(!nMap->generated) {
			if(nMap->combination) {
				generateCombination(static_cast<CombinationNoiseMap*>(nMap), xChunk, yChunk);

			} // if(nMap->combination);
			else {
				generateRandom(static_cast<RandomNoiseMap*>(nMap), xChunk, yChunk);

			} // else;

		} // if(!nMap->generated);

	} // for(NoiseMap* nMap : noiseMaps);

	setTiles();

	return this;

} // World* World::generate(int xChunk, int yChunk);

WG_NS_END
