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
	: chunkWidth(WG_DEF_CHUNK), chunkHeight(WG_DEF_CHUNK) {

} // World::World();

RandomNoiseMap* World::addRandomNoiseMap() {
	noiseMaps.push_back(new RandomNoiseMap);

	return static_cast<RandomNoiseMap*>(noiseMaps.back());

} // RandomNoiseMap* World::addRandomNoiseMap();

CombinationNoiseMap* World::addCombinationNoiseMap() {
	noiseMaps.push_back(new CombinationNoiseMap);

	return static_cast<CombinationNoiseMap*>(noiseMaps.back());

} // CombinationNoiseMap* World::addCombinationNoiseMap();

World* World::generate(int xChunk, int yChunk) {
	// First generate all noisemaps
	for(NoiseMap* nMap : noiseMaps) {
		if(!nMap->generated) {
			if(nMap->combination) {
				generateCombination(static_cast<CombinationNoiseMap*>(nMap));

			} // if(nMap->combination);
			else {
				generateRandom(static_cast<RandomNoiseMap*>(nMap));

			} // else;

		} // if(!nMap->generated);

	} // for(NoiseMap* nMap : noiseMaps);

	return this;

} // World* World::generate(int xChunk, int yChunk);

void World::generateRandom(RandomNoiseMap* nMap) {
	perlinModule.SetSeed(std::hash<std::string>()(nMap->seed));
	perlinModule.SetOctaveCount(nMap->octaves);
	perlinModule.SetFrequency(nMap->frequency);
	perlinModule.SetPersistence(nMap->persistence);
	perlinModule.SetLacunarity(nMap->lacunarity);

	for(int y = 0; y < chunkHeight; ++y) {
		nMap->noiseVals.push_back(std::vector<double>());

		for(int x = 0; x < chunkWidth; ++x) {
			nMap->noiseVals.back().push_back(perlinModule.GetValue(x * nMap->gridSizeX, y * nMap->gridSizeY, 0));

		} // for(int x = 0; x < chunkWidth; ++x);

	} // for(int y = 0; y < chunkHeight; ++y);

	nMap->generated = true;

} // void World::generateRandom(RandomNoiseMap* nMap);

void World::generateCombination(CombinationNoiseMap* nMap) {
	int factor = 0;

	nMap->noiseVals.resize(chunkHeight);
	for(int y = 0; y < chunkHeight; ++y) {
		nMap->noiseVals[y].resize(chunkWidth, 0);

	} // for(int y = 0; y < chunkHeight; ++y);

	for(auto& combPair : nMap->combinations) {
		if(!combPair.first->generated) {
			if(combPair.first->combination) {
				generateCombination(static_cast<CombinationNoiseMap*>(combPair.first));

			} // if(combPair.first->combination);
			else {
				generateRandom(static_cast<RandomNoiseMap*>(combPair.first));

			} // else;

		} // if(!combPair.first->generated);

		factor += combPair.second;

		for(int y = 0; y < chunkHeight; ++y) {
			for(int x = 0; x < chunkWidth; ++x) {
				nMap->noiseVals[y][x] += (combPair.first->noiseVals[y][x] * combPair.second);

			} // for(int x = 0; x < chunkWidth; ++x);

		} // for(int y = 0; y < chunkHeight; ++y);

	} // for(NoiseMap* combMap : nMap->combinations);

	for(int y = 0; y < chunkHeight; ++y) {
		for(int x = 0; x < chunkWidth; ++x) {
			nMap->noiseVals[y][x] /= factor;

		} // for(int x = 0; x < chunkWidth; ++x);

	} // for(int y = 0; y < chunkHeight; ++y);

	nMap->generated = true;

} // void World::generateCombination(CombinationNoiseMap* nMap);

WG_NS_END
