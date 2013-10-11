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
// File: src/noisemap.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include "inc/noisemap.hpp"

WG_NS

NoiseMap::NoiseMap(MapType mapType) 
	: mapType(mapType), generated(false) {

} // NoiseMap::NoiseMap(MapType mapType);

RandomNoiseMap::RandomNoiseMap()
	: NoiseMap(MapType::Random),

	  seed(WG_DEF_SEED),
	  gridSizeX(WG_DEF_GRID), gridSizeY(WG_DEF_GRID),
	  octaves(WG_DEF_OCTAVES),
	  frequency(WG_DEF_FREQ),
	  persistence(WG_DEF_PERS),
	  lacunarity(WG_DEF_LACU) {

} // RandomNoiseMap::RandomNoiseMap();

CombinationNoiseMap::CombinationNoiseMap()
	: NoiseMap(MapType::Combination) {

} // CombinationNoiseMap::CombinationNoiseMap();

CombinationNoiseMap* CombinationNoiseMap::add(NoiseMap* mapToAdd, int factor) {
	combinations.push_back({mapToAdd, factor});

	return this;

} // CombinationNoiseMap* CombinationNoiseMap::add(NoiseMap* mapToAdd, int factor);

WG_NS_END
