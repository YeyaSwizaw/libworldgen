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
// File: src/inc/defines.hpp
// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
/////////////////////////////////////////////////////////////////////////////

#ifndef WG_DEFINES_HPP
#define WG_DEFINES_HPP

#define WG_NS namespace wg {
#define WG_NS_END }

#define WG_DEF_CHUNK 20

#define WG_DEF_SEED "0"
#define WG_DEF_GRID 1
#define WG_DEF_OCTAVES noise::module::DEFAULT_PERLIN_OCTAVE_COUNT
#define WG_DEF_FREQ noise::module::DEFAULT_PERLIN_FREQUENCY
#define WG_DEF_PERS noise::module::DEFAULT_PERLIN_PERSISTENCE
#define WG_DEF_LACU noise::module::DEFAULT_PERLIN_LACUNARITY

#define WG_NO_TILE std::numeric_limits<int>::max()

#endif // WG_DEFINES_HPP
