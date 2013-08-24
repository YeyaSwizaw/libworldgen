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
// File: src/constraint.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include "inc/constraint.hpp"

#define WG_IMP_NOISEMAP
#include "inc/noisemap.hpp"
#undef WG_IMP_NOISEMAP

WG_NS

Constraint::Constraint(std::shared_ptr<NoiseMap> noiseMap, Type type, double value) 
	: noiseMap(noiseMap), type(type), value(value) {

} // Constraint::Constraint(NoiseMap::Ptr noiseMap, Type type, double value);

bool Constraint::isValid(int chunkWidth, int chunkHeight, int chunkX, int chunkY, int x, int y) {
	if(!(noiseMap->isGenerated(chunkWidth, chunkHeight, chunkX, chunkY))) {
		noiseMap->generate(chunkWidth, chunkHeight, chunkX, chunkY);

	} // if(!(noiseMap->isGenerated(chunkWidth, chunkHeight, chunkX, chunkY)));

	bool retval = false;

	switch(type) {
		case GT:
			retval = (noiseMap->noiseVals[y][x] > value);
			break;

		case LT:
			retval = (noiseMap->noiseVals[y][x] < value);
			break;

	} // switch(type);

	return retval;

} // bool Constraint::isValid(int chunkWidth, int chunkHeight, int chunkX, int chunkY, int x, int y);

WG_NS_END
