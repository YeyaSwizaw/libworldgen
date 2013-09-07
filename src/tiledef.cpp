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
// File: src/tiledef.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include "inc/tiledef.hpp"

WG_NS

unsigned int TileDef::nextId = 0;

TileDef::TileDef()
	: id(nextId++) {

} // TileDef::TileDef();

TileDef::~TileDef() {
	for(auto& c : constraints) {
		c.clear();

	} // for(auto& c : constraints);

	constraints.clear();

} // TileDef::~TileDef();

bool TileDef::isValid(int chunkWidth, int chunkHeight, int chunkX, int chunkY, int x, int y) {
	for(auto& c : constraints) {
		if(!(c.isValid(chunkWidth, chunkHeight, chunkX, chunkY, x, y))) {
			return false;

		} // if(!(c.isValid(chunkX, chunkY, x, y)));

	} // for(auto& c : constraints);

	return true;

} // bool TileDef::isValid(int chunkX, int chunkY, int x, int y);

WG_NS_END
