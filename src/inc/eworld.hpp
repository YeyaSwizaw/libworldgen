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
// File: src/inc/eworld.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_EWORLD_HPP
#define WG_EWORLD_HPP

#include <map>
#include <vector>

#include "defines.hpp"
#include "worldbase.hpp"
#include "noisemap.hpp"
#include "tiledef.hpp"

WG_NS

template<typename _tp>
class EnhancedWorld;

template<typename _tp>
class EnhancedWorld : public WorldBase<EnhancedWorld<_tp>> {
public:
	EnhancedWorld();

	TileDef* addTileDefinition(_tp object);

	EnhancedWorld<_tp>* generate(int xChunk, int yChunk);

	_tp getObject(int x, int y) { return mappedObjects[y][x]; }
	std::vector<std::vector<_tp>> getObjects() { return mappedObjMap; }

private:
	std::map<unsigned int, _tp> mappedObjects;
	std::vector<std::vector<_tp>> mappedObjMap;

	void mapObjects();

}; // class EnhancedWorld<_tp> : public WorldBase<EnhancedWorld<_tp>>;

#include "eworld.tpp"

WG_NS_END

#endif // WG_EWORLD_HPP
