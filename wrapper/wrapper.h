#ifndef WORLDGEN_WRAPPER_H
#define WORLDGEN_WRAPPER_H

#ifdef __cplusplus
    #include "../src/inc/world.hpp"
    #include "../src/inc/noisemap.hpp"
    #include "../src/inc/tiledef.hpp"

    #define WRAPPER extern "C"

    using world = wg::World;
    using tiledef = wg::TileDef;
    using rand_nm = wg::RandomNoiseMap;
    using comb_nm = wg::CombinationNoiseMap;
#else
    #define WRAPPER

    typedef struct world world;
    typedef struct tiledef tiledef;
    typedef struct rand_nm rand_nm;
    typedef struct comb_nm comb_nm;
#endif

#define CONSTRAINT_LT 0
#define CONSTRAINT_GT 1

// TileDef
WRAPPER void tiledef_add_rand_nm_constraint(tiledef* tiledef, rand_nm* nm, int type, double fact);
WRAPPER void tiledef_add_comb_nm_constraint(tiledef* tiledef, comb_nm* nm, int type, double fact);

// CombinationNoiseMap
WRAPPER void comb_nm_add_rand_nm(comb_nm* nm, rand_nm* other, int factor);
WRAPPER void comb_nm_add_comb_nm(comb_nm* nm, comb_nm* other, int factor);

WRAPPER double comb_nm_get_value(comb_nm* nm, int x, int y);

// RandomNoiseMap
WRAPPER void rand_nm_set_seed(rand_nm* nm, const char* seed);
WRAPPER void rand_nm_set_gridsize(rand_nm* nm, double width, double height);
WRAPPER void rand_nm_set_gridwidth(rand_nm* nm, double width);
WRAPPER void rand_nm_set_gridheight(rand_nm* nm, double height);
WRAPPER void rand_nm_set_octaves(rand_nm* nm, int octaves);
WRAPPER void rand_nm_set_frequency(rand_nm* nm, double frequency);
WRAPPER void rand_nm_set_persistence(rand_nm* nm, double persistence);
WRAPPER void rand_nm_set_lacunarity(rand_nm* nm, double lacunarity);

WRAPPER double rand_nm_get_gridwidth(rand_nm* nm);
WRAPPER double rand_nm_get_gridheight(rand_nm* nm);
WRAPPER int rand_nm_get_octaves(rand_nm* nm);
WRAPPER double rand_nm_get_frequency(rand_nm* nm);
WRAPPER double rand_nm_get_persistence(rand_nm* nm);
WRAPPER double rand_nm_get_lacunarity(rand_nm* nm);
WRAPPER double rand_nm_get_value(rand_nm* nm, int x, int y);

// World
WRAPPER world* world_new();
WRAPPER void world_delete(world* world);

WRAPPER void world_set_chunksize(world* world, int width, int height);
WRAPPER void world_set_chunkwidth(world* world, int width);
WRAPPER void world_set_chunkheight(world* world, int height);

WRAPPER rand_nm* world_add_rand_nm(world* world);
WRAPPER comb_nm* world_add_comb_nm(world* world);
WRAPPER tiledef* world_add_tiledef(world* world);
WRAPPER void world_generate(world* world, int chunkx, int chunky);

WRAPPER int world_get_chunkwidth(world* world);
WRAPPER int world_get_chunkheight(world* world);
WRAPPER unsigned int world_get_tile(world* world, int x, int y);

#endif
