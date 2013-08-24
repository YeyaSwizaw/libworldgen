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

#include <vector>

#include "defines.hpp"
#include "tiledef.hpp"

WG_NS

class World : public std::enable_shared_from_this<World> {
public:
	typedef std::shared_ptr<World> Ptr;

	static Ptr create() { return Ptr(new World()); }

	TileDef::Ptr newTile();
	
	Ptr setChunkSize(int width, int height) { chunkWidth = width; chunkHeight = height; return shared_from_this(); }
	Ptr setChunkWidth(int value) { chunkWidth = value; return shared_from_this(); }
	Ptr setChunkHeight(int value) { chunkHeight = value; return shared_from_this(); }

	Ptr generate(int chunkX = 0, int chunkY = 0);

	std::vector<std::vector<unsigned int>> getMap() { return this->mapGrid; }

private:
	int chunkWidth, chunkHeight;

	std::vector<TileDef::Ptr> tileDefinitions;

	std::vector<std::vector<unsigned int>> mapGrid;

}; // class World : public std::enable_shared_from_this<World>;

WG_NS_END

#endif // WG_WORLD_HPP
