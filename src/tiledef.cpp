/////////////////////////////////////////////////////////////////////////////
//// Copyright 2013 Samuel Sleight
////
//// Licensed under the Apache License, Version 2.0 (the "License");
//// you may not use this file except in compliance with the License.
//// You may obtain a copy of the License at
////
//// 		http://www.apache.org/licenses/LICENSE-2.0
////
//// Unless required by applicable law or agreed to in writing, software
//// distributed under the License is distributed on an "AS IS" BASIS,
//// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//// See the License for the specific language governing permissions and
//// limitations under the License.
///////////////////////////////////////////////////////////////////////////////
//// Project: World Generation Library
//// File: src/tiledef.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/tiledef.hpp"
#include "inc/noisemap.hpp"

WG_NS

unsigned int TileDef::nextId = 0;

TileDef::TileDef() 
	: id(nextId++) {

} // TileDef::TileDef();

bool TileDef::isValid(int x, int y) {
	for(Constraint& c : constraints) {
		switch(c.type) {
			case ConstraintType::GT:
				if(c.nMap->noiseVals[y][x] < c.threshold) {
					return false;

				} // if(c.nMap->noiseVals[y][x] < c.threshold);

				break;

			case ConstraintType::LT:
				if(c.nMap->noiseVals[y][x] > c.threshold) {
					return false;

				} // if(c.nMap->noiseVals[y][x] > c.threshold);

				break;

		} // switch(c.type);

	} // for(Constraint& c : constraints);

	return true;

} // bool TileDef::isValid(int x, int y);

WG_NS_END
