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

NoiseMap::NoiseMap(std::string seed, double x0, double x1, double y0, double y1, 
		int octaves, double frequency, double persistence, double lacunarity) 
	: seed(seed),
	  x0(x0), x1(x1), y0(y0), y1(y1),
	  octaves(octaves),
	  frequency(frequency),
	  persistence(persistence),
	  lacunarity(lacunarity),
	  isCombination(false) {

} // NoiseMap::NoiseMap(std::string seed, double x0, double x1, double y0, double y1, 
		//int octaves, double frequency, double persistence, double lacunarity);

NoiseMap::NoiseMap(std::vector<std::pair<int, int>> cmbVect) 
	: isCombination(true),
	  combinations(cmbVect) {

} // NoiseMap::NoiseMap(std::vector<std::pair<int, int>> cmbVect);

void NoiseMap::addRow() {
	noiseVals.push_back(std::vector<double>());

} // void NoiseMap::addRow();

void NoiseMap::addValue(double value) {
	noiseVals.back().push_back(value);

} // void NoiseMap::addValue(double value);

WG_NS_END
