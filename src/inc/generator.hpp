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
// File: src/inc/generator.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_GENERATOR_HPP
#define WG_GENERATOR_HPP

#include "defines.hpp"

#include <string>

#include <noise/noise.h>

WG_NS

class NoiseMap;
class World;

class Generator {
private:
	friend class NoiseMap;
	friend class World;

	Generator(std::string seed, double gridX, double gridY,
			int octaves, double freq, double pers, double lacu);

	double operator()(int x, int y);

	double gridX, gridY;

	noise::module::Perlin perlinModule;

}; // class Generator;

WG_NS_END

#endif // WG_GENERATOR_HPP
