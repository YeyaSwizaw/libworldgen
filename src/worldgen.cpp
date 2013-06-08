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
// File: src/worldgen.cpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#include "inc/worldgen.hpp"

WG_NS

WorldGen::WorldGen(int mapWidth, int mapHeight)
	: mapWidth(mapWidth), mapHeight(mapHeight),
	  nextId(0), nextTileId(0) {

} // WorldGen::WorldGen(int mapWidth, int mapHeight);

int WorldGen::addNoiseMap(std::string seed, double x0, double x1, double y0, double y1, 
		int octaves, double frequency, double persistence, double lacunarity) {

	noiseMaps.insert(std::make_pair(nextId,
			new NoiseMap(seed, x0, x1, y0, y1, octaves, frequency, persistence, lacunarity)));

	nextId++;
	return (nextId - 1);

} // int WorldGen::addNoiseMap(std::string seed, double x0, double x1, double y0, double y1, 
		// int octaves, double frequency, double persistence, double lacunarity);

void WorldGen::removeNoiseMap(int id) {
	if(noiseMaps.at(id)->isCombination) {
		for(auto it = cmbPriorities.begin(); it != cmbPriorities.end(); ++it) {
			if(*it == id) {
				cmbPriorities.erase(it);
				break;

			} // if(*it == id);

		} // for(auto it = cmbPriorities.begin(); it != cmbPriorities.end(); ++it);

	} // if(noiseMaps.at(id)->isCombination);

	delete (noiseMaps.at(id));
	noiseMaps.erase(id);

} // void WorldGen::removeNoiseMap(int id);

int WorldGen::addNoiseCombination(std::initializer_list<std::pair<int, int>> combList) {
	return addNoiseCombination(std::vector<std::pair<int, int>>(combList));

} // int WorldGen::addNoiseCombination(std::initializer_list<std::pair<int, int>> combList);

int WorldGen::addNoiseCombination(std::vector<std::pair<int, int>> combVect) {
	noiseMaps.insert(std::make_pair(nextId, new NoiseMap(combVect)));

	cmbPriorities.push_back(nextId);

	nextId++;
	return (nextId - 1);

} // int WorldGen::addNoiseCombination(std::vector<std::pair<int, int>> combVect);

void WorldGen::setNoiseSeed(int id, std::string value) {
	noiseMaps.at(id)->seed = value;

} // void WorldGen::setNoiseSeed(int id, std::string value);

void WorldGen::setNoiseX0(int id, double value) {
	noiseMaps.at(id)->x0 = value;

} // void WorldGen::setNoiseX0(int id, double value);

void WorldGen::setNoiseX1(int id, double value) {
	noiseMaps.at(id)->x1 = value;

} // void WorldGen::setNoiseX1(int id, double value);

void WorldGen::setNoiseY0(int id, double value) {
	noiseMaps.at(id)->y0 = value;

} // void WorldGen::setNoiseY0(int id, double value);

void WorldGen::setNoiseY1(int id, double value) {
	noiseMaps.at(id)->y1 = value;

} // void WorldGen::setNoiseY1(int id, double value);

void WorldGen::setNoiseOctaveCount(int id, int value) {
	noiseMaps.at(id)->octaves = value;

} // void WorldGen::setNoiseOctaveCount(int id, double value);

void WorldGen::setNoiseFrequency(int id, double value) {
	noiseMaps.at(id)->frequency = value;

} // void WorldGen::setNoiseFrequency(int id, double value);

void WorldGen::setNoisePersistence(int id, double value) {
	noiseMaps.at(id)->persistence = value;

} // void WorldGen::setNoisePersistence(int id, double value);

void WorldGen::setNoiseLacunarity(int id, double value) {
	noiseMaps.at(id)->lacunarity = value;

} // void WorldGen::setNoiseLacunarity(int id, double value);

std::string WorldGen::getNoiseSeed(int id) {
	return noiseMaps.at(id)->seed;

} // std::string WorldGen::getNoiseSeed(int id);

double WorldGen::getNoiseX0(int id) {
	return noiseMaps.at(id)->x0;

} // double WorldGen::getNoiseX0(int id);

double WorldGen::getNoiseX1(int id) {
	return noiseMaps.at(id)->x1;

} // double WorldGen::getNoiseX1(int id);

double WorldGen::getNoiseY0(int id) {
	return noiseMaps.at(id)->y0;

} // double WorldGen::getNoiseY0(int id);

double WorldGen::getNoiseY1(int id) {
	return noiseMaps.at(id)->y1;

} // double WorldGen::getNoiseY1(int id);

int WorldGen::getNoiseOctaveCount(int id) {
	return noiseMaps.at(id)->octaves;

} // int WorldGen::getNoiseOctaveCount(int id);

double WorldGen::getNoiseFrequency(int id) {
	return noiseMaps.at(id)->frequency;

} // double WorldGen::getNoiseFrequency(int id);

double WorldGen::getNoisePersistence(int id) {
	return noiseMaps.at(id)->persistence;

} // double WorldGen::getNoisePersistence(int id);

double WorldGen::getNoiseLacunarity(int id) {
	return noiseMaps.at(id)->lacunarity;

} // double WorldGen::getNouseLacunarity(int id);

int WorldGen::defineTile(std::initializer_list<TileConstraint> thresholds) {
	return defineTile(std::vector<TileConstraint>(thresholds));

} // int WorldGen::defineTile(std::initializer_list<TileConstraint> thresholds);

int WorldGen::defineTile(std::vector<TileConstraint> thresholds) {
	tileDefinitions.insert(std::make_pair(nextTileId, thresholds));
	tilePriorities.push_back(nextTileId);
	
	nextTileId++;
	return (nextTileId - 1);

} // int WorldGen::defineTile(std::vector<TileConstraint> thresholds);

void WorldGen::deleteTile(int id) {
	tileDefinitions.erase(id);

	for(auto it = tilePriorities.begin(); it != tilePriorities.end(); ++it) {
		if(*it == id) {
			tilePriorities.erase(it);

		} // if(*it == id);

	} // for(auto it = tilePriorities.begin(); it != tilePriorities.end(); ++it);

} // void WorldGen::deleteTile(int id);

void WorldGen::generateWorld() {
	NoiseMap *nMap;

	for(auto pair : noiseMaps) {
		nMap = pair.second;

		if(!(nMap->isCombination)) {
			perlin.SetSeed(std::hash<std::string>()(nMap->seed));
			perlin.SetOctaveCount(nMap->octaves);
			perlin.SetFrequency(nMap->frequency);
			perlin.SetPersistence(nMap->persistence);
			perlin.SetLacunarity(nMap->lacunarity);

			double xStep = (nMap->x1 - nMap->x0) / (mapWidth + 1);
			double yStep = (nMap->y1 - nMap->y0) / (mapHeight + 1);

			for(double y = nMap->y0; y <= nMap->y1; y += yStep) {
				nMap->addRow();

				for(double x = nMap->x0; x <= nMap->x1; x += xStep) {
					nMap->addValue(perlin.GetValue(x, y, 0));

				} // for(double x = nMap->x0; x < nMap->x1; x += xStep);

			} // for(double y = nMap->y0; y < nMap->y1; y += yStep);

		} // if(!(nMap->isCombination));

	} // for(NoiseMap *nMap : noiseMaps);

	double val;
	int factor;

	for(auto i : cmbPriorities) {
		nMap = noiseMaps.at(i);

		for(int y = 0; y < mapHeight; y++) {
			nMap->addRow();

			for(int x = 0; x < mapWidth; x++) {
				val = 0;
				factor = 0;

				for(auto &pair : nMap->combinations) {
					val += (pair.second * noiseMaps.at(pair.first)->noiseVals[y][x]);
					factor += (pair.second);

				} // for(auto *pair : nMap->combinations);

				nMap->addValue(val / factor);

			} // for(int x = 0; x <= mapWidth; x++);

		} // for(int y = 0; y <= mapHeight; y++);

	} // for(auto i : cmbs);
	
	bool matchesDefinition = true;
	bool tileFound = false;

	for(int y = 0; y < mapHeight; y++) {
		finalMap.push_back(std::vector<int>());

		for(int x = 0; x < mapWidth; x++) {
			tileFound = false;
			for(auto i : tilePriorities) {
				matchesDefinition = true;

				for(auto &con : tileDefinitions.at(i)) {
					if(con.op == Greater) {
						if(!(noiseMaps.at(con.nId)->noiseVals[y][x] >= con.val)) {
							matchesDefinition = false;
							break;

						} // if(noiseMaps.at(con.nId)->noiseVals[y][x] >= con.val);

					} // if(con.op == Greater);
					else {
						if(!(noiseMaps.at(con.nId)->noiseVals[y][x] <= con.val)) {
							matchesDefinition = false;
							break;

						} // if(!(noiseMaps.at(con.nId)->noiseVals[y][x] <= con.val));

					} // else;

				} // for(auto con : tDef.first);

				if(matchesDefinition) {
					finalMap.back().push_back(i);
					tileFound = true;
					break;

				} // if(matchesDefinition);

			} // for(auto i : tilePriorities);

			if(!tileFound) {
				finalMap.back().push_back(WG_NO_TILE);

			} // if(!tileFound);

		} // for(int x = 0; x < mapWidth; x++);

	} // for(int y = 0; y > mapHeight; y++);

} // void WorldGen::generateWorld();

std::vector<std::vector<int>> WorldGen::getTileMap() {
	return finalMap;

} // std::vector<std::vector<int>> WorldGen::getTileMap();

std::vector<std::vector<double>> WorldGen::getNoiseMap(int id) {
	return noiseMaps.at(id)->noiseVals;

} // std::vector<std::vector<double>> WorldGen::getNoiseMap(int id);

WG_NS_END
