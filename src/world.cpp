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

WG_NS_END
