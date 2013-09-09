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
// File: src/inc/eworld.tpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_EWORLD_TPP
#define WG_EWORLD_TPP

template<typename _tp>
EnhancedWorld<_tp>::EnhancedWorld()
	: WorldBase<EnhancedWorld<_tp>>() {

} // EnhancedWorld<_tp>::EnhancedWorld();

template<typename _tp>
TileDef* EnhancedWorld<_tp>::addTileDefinition(_tp object) {
	this->tileDefinitions.push_back(new TileDef);
	mappedObjects.insert(std::make_pair(this->tileDefinitions.back()->id, object));

	return this->tileDefinitions.back();

} // TileDef* EnhancedWorld<_tp>::addTileDefinition(_tp object);

template<typename _tp>
EnhancedWorld<_tp>* EnhancedWorld<_tp>::generate(int xChunk, int yChunk) {
	for(NoiseMap* nMap : this->noiseMaps) {
		if(!nMap->generated) {
			if(nMap->combination) {
				this->generateCombination(static_cast<CombinationNoiseMap*>(nMap));

			} // if(nMap->combination);
			else {
				this->generateRandom(static_cast<RandomNoiseMap*>(nMap));

			} // else;

		} // if(!nMap->generated);

	} // for(NoiseMap* nMap : noiseMaps);

	this->setTiles();

	mapObjects();

	return this;

} // EnhancedWorld<_tp>* EnhancedWorld<_tp>::generate(int xChunk, int yChunk);

template<typename _tp>
void EnhancedWorld<_tp>::mapObjects() {
	for(int y = 0; y < this->chunkHeight; ++y) {
		mappedObjMap.push_back(std::vector<_tp>());

		for(int x = 0; x < this->chunkWidth; ++x) {
			mappedObjMap.back().push_back(mappedObjects[this->mapGrid[y][x]]);

		} // for(int x = 0; x < this->chunkWidth; ++x);

	} // for(int y = 0; y < this->chunkHeight; ++y);

} // void EnhancedWorld<_tp>::mapObjects();

#endif // WG_EWORLD_TPP
