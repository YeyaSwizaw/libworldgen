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
// File: src/inc/worldbase.tpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_WORLDBASE_TPP
#define WG_WORLDBASE_TPP

template<typename _t>
WorldBase<_t>::WorldBase()
	: chunkWidth(WG_DEF_CHUNK), chunkHeight(WG_DEF_CHUNK) {

} // WorldBase<_t>::WorldBase();

template<typename _t>
WorldBase<_t>::~WorldBase() {
    for(auto* nm : noiseMaps) {
        delete nm;
    }

    for(auto* td : tileDefinitions) {
        delete td;
    }
}

template<typename _t>
RandomNoiseMap* WorldBase<_t>::addRandomNoiseMap() {
	noiseMaps.push_back(new RandomNoiseMap);

	return static_cast<RandomNoiseMap*>(noiseMaps.back());

} // RandomNoiseMap* WorldBase<_t>::addRandomNoiseMap();

template<typename _t>
CombinationNoiseMap* WorldBase<_t>::addCombinationNoiseMap() {
	noiseMaps.push_back(new CombinationNoiseMap);

	return static_cast<CombinationNoiseMap*>(noiseMaps.back());

} // CombinationNoiseMap* WorldBase<_t>::addCombinationNoiseMap();

template<typename _t>
void WorldBase<_t>::clearNoiseMaps() {
	for(NoiseMap* nMap : noiseMaps) {
		nMap->generated = false;
		nMap->noiseVals.clear();

	} // for(NoiseMap* nMap : noiseMaps);

} // void WorldBase<_t>::clearNoiseMaps();

template<typename _t>
void WorldBase<_t>::generateRandom(RandomNoiseMap* nMap, int xChunk, int yChunk) {
	perlinModule.SetSeed(std::hash<std::string>()(nMap->seed));
	perlinModule.SetOctaveCount(nMap->octaves);
	perlinModule.SetFrequency(nMap->frequency);
	perlinModule.SetPersistence(nMap->persistence);
	perlinModule.SetLacunarity(nMap->lacunarity);

	for(int y = yChunk * chunkHeight; y < (yChunk + 1) * chunkHeight; ++y) {
		nMap->noiseVals.push_back(std::vector<double>());

		for(int x = xChunk * chunkWidth; x < (xChunk + 1) * chunkWidth; ++x) {
			nMap->noiseVals.back().push_back(perlinModule.GetValue(x * nMap->gridSizeX, y * nMap->gridSizeY, 0));

		} // for(int x = 0; x < chunkWidth; ++x);

	} // for(int y = 0; y < chunkHeight; ++y);

	nMap->generated = true;

} // void WorldBase<_t>::generateRandom(RandomNoiseMap* nMap);

template<typename _t>
void WorldBase<_t>::generateCombination(CombinationNoiseMap* nMap, int xChunk, int yChunk) {
	int factor = 0;

	nMap->noiseVals.resize(chunkHeight);
	for(int y = 0; y < chunkHeight; ++y) {
		nMap->noiseVals[y].resize(chunkWidth, 0);

	} // for(int y = 0; y < chunkHeight; ++y);

	for(auto& combPair : nMap->combinations) {
		if(!combPair.first->generated) {
			switch(combPair.first->mapType) {
				case NoiseMap::MapType::Random:
					generateRandom(static_cast<RandomNoiseMap*>(combPair.first), xChunk, yChunk);
					break;

				case NoiseMap::MapType::Combination:
					generateCombination(static_cast<CombinationNoiseMap*>(combPair.first), xChunk, yChunk);
					break;

			} // switch(combPair.mapType);

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

} // void WorldBase<_t>::generateCombination(CombinationNoiseMap* nMap);

template<typename _t>
void WorldBase<_t>::setTiles() {
	mapGrid.resize(chunkHeight);
	for(int y = 0; y < chunkHeight; ++y) {
		mapGrid[y].resize(chunkWidth, TileDef::nextId);

		for(int x = 0; x < chunkWidth; ++x) {
			for(TileDef* tDef : tileDefinitions) {
				if(tDef->isValid(x, y)) {
					mapGrid[y][x] = tDef->id;
					break;

				} // if(tDef->isValid(x, y));

			} // for(TileDef* tDef : tileDefinitions);

		} // for(int x = 0; x < chunkWidth; ++x);

	} // for(int y = 0; y < chunkHeight; ++y);

} // void WorldBase<_t>::setTiles();

#endif // WG_WORLDBASE_TPP
