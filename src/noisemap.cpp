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

NoiseMap::NoiseMap()
	: seed(WG_DEF_SEED),
	  gridSizeX(WG_DEF_GRID), gridSizeY(WG_DEF_GRID),
	  octaves(WG_DEF_OCTAVES),
	  frequency(WG_DEF_FREQ),
	  persistence(WG_DEF_PERS),
	  lacunarity(WG_DEF_LACU),

	  isCombination(false) {

} // NoiseMap::NoiseMap();

NoiseMap::NoiseMap(bool combination)
	: isCombination(true) {

} // NoiseMap::NoiseMap(bool combination);

NoiseMap::Ptr NoiseMap::add(Ptr noiseMap, int factor) {
	combinations.push_back(std::make_pair(noiseMap, factor));

	return shared_from_this();

} // Ptr NoiseMap::add(Ptr noiseMap, int factor);

NoiseMap::Ptr NoiseMap::generate(int width, int height, int chunkX, int chunkY) {
	this->chunkX = chunkX;
	this->chunkY = chunkY;
	chunkWidth = width;
	chunkHeight = height;

	if(isCombination) {
		genCombination();

	} // if(isCombination);
	else {
		genNormal();

	} // else;

	generated = true;

	return shared_from_this();

} // NoiseMap::Ptr NoiseMap::generate(int width, int height);

void NoiseMap::genNormal() {
	Generator gen(seed, gridSizeX, gridSizeY, octaves,
			frequency, persistence, lacunarity);

	int yBase = chunkY * chunkHeight;
	int xBase = chunkX * chunkWidth;

	for(int y = yBase; y < (yBase + chunkHeight); ++y) {
		noiseVals.push_back(std::vector<double>());

		for(int x = xBase; x < (xBase + chunkWidth); ++x) {
			noiseVals.back().push_back(gen(x, y));

		} // for(int x = 0; x < width; ++x);

	} // for(int y = 0; y < width; ++y);

} // void NoiseMap::genNormal();

void NoiseMap::genCombination() {
	noiseVals.resize(chunkHeight);
	for(auto& row : noiseVals) {
		row.resize(chunkWidth, 0.0);

	} // for(auto& row : noiseVals);

	int totalFactor = 0;

	for(auto& comb : combinations) {
		totalFactor += abs(comb.second);

		if(!(comb.first->isGenerated(chunkWidth, chunkHeight, chunkX, chunkY))) {
			comb.first->generate(chunkWidth, chunkHeight, chunkX, chunkY);

		} // if(!(comb.first->isGenerated(chunkWidth, chunkHeight, chunkX, chunkY)));

		int xBase = chunkX * chunkWidth;
		int yBase = chunkY * chunkHeight;

		for(int x = xBase; x < (xBase + chunkWidth); ++x) {
			for(int y = yBase; y < (yBase + chunkHeight); ++y) {
				noiseVals[y][x] += (comb.first->noiseVals[y][x] * comb.second);

			} // for(int y = 0; y < height; ++y);

		} // for(int x = 0; x < width; ++x);

	} // for(auto& comb : combinations);

	for(auto& row : noiseVals) {
		for(auto& val : row) {
			val /= totalFactor;

		} // for(auto& val : row);

	} // for(auto& row : noiseVals);

} // void NoiseMap::genCombination(int width, int height);

bool NoiseMap::isGenerated(int chunkWidth, int chunkHeight, int chunkX, int chunkY) {
	return generated && (chunkWidth == this->chunkWidth)
		             && (chunkHeight == this->chunkHeight)
					 && (chunkX == this->chunkX)
					 && (chunkY == this->chunkY);

} // bool NoiseMap::isGenerated(int chunkWidth, int chunkHeight, int chunkX, int chunkY);

WG_NS_END
