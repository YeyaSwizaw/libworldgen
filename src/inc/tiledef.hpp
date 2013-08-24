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
// File: src/inc/tiledef.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_TILEDEF_HPP
#define WG_TILEDEF_HPP

#include <memory>
#include <vector>

#include "defines.hpp"
#include "constraint.hpp"

WG_NS

class World;

class TileDef : public std::enable_shared_from_this<TileDef> {
public:
	typedef std::shared_ptr<TileDef> Ptr;

	Ptr addConstraint(Constraint c) { constraints.push_back(c); return shared_from_this(); }

	unsigned int getId() { return id; }

private:
	friend class World;

	TileDef();

	static unsigned int nextId;
	unsigned int id;

	std::vector<Constraint> constraints;

	bool isValid(int chunkWidth, int chunkHeight, int chunkX, int chunkY, int x, int y);

}; // class TileDef;

WG_NS_END

#endif // WG_TILEDEF_HPP