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
// File: src/inc/constraint.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_CONSTRAINT_HPP
#define WG_CONSTRAINT_HPP

#include <memory>

#include "defines.hpp"

WG_NS

class NoiseMap;
class TileDef;

class Constraint {
public:
	enum Type {
		GT,
		LT

	}; // enum Type;

	Constraint(std::shared_ptr<NoiseMap> noiseMap, Type type, double value);

private:
	friend class TileDef;

	std::shared_ptr<NoiseMap> noiseMap;
	Type type;
	double value;

	bool isValid(int chunkWidth, int chunkHeight, int chunkX, int chunkY, int x, int y);

}; // class Constraint;

WG_NS_END

#endif // WG_CONSTRAINT_HPP
