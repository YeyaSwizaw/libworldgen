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

WG_NS

TileDef::Ptr World::newTile() {
	tileDefinitions.push_back(TileDef::Ptr(new TileDef()));

	return tileDefinitions.back();

} // TileDef::Ptr World::newTile();

World::Ptr World::generate(int chunkX, int chunkY) {
	mapGrid.clear();
	mapGrid.resize(chunkHeight);
	for(auto& row : mapGrid) {
		row.resize(chunkWidth, TileDef::nextId);

	} // for(auto& row : mapGrid);

	for(int x = 0; x < chunkWidth; ++x) {
		for(int y = 0; y < chunkHeight; ++y) {
			for(auto& tDef : tileDefinitions) {
				if(tDef->isValid(chunkWidth, chunkHeight, chunkX, chunkY, x, y)) {
					mapGrid[y][x] = tDef->id;
					break;

				} // if(tDef->isValid(chunkX, chunkY, x, y));

			} // for(auto& tDef : tileDefinitions);

		} // for(int y = 0; y < chunkHeight; ++y);

	} // for(int x = 0; x < chunkWidth; ++x);

	return shared_from_this();

} // World::Ptr World::generate(int chunkX, int chunkY);

WG_NS_END
