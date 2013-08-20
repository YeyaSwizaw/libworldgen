#include "inc/generator.hpp"

WG_NS

Generator::Generator(std::string seed, double gridX, double gridY, 
		int octaves, double freq, double pers, double lacu) 
	: gridX(gridX), gridY(gridY) {

	perlinModule.SetSeed(std::hash<std::string>()(seed));
	perlinModule.SetOctaveCount(octaves);
	perlinModule.SetFrequency(freq);
	perlinModule.SetPersistence(pers);
	perlinModule.SetLacunarity(lacu);

} // Generator::Generator(std::string seed, double gridX, double gridY, 
  //	int octaves, double freq, double pers, double lacu);

double Generator::operator()(int x, int y) {
	return perlinModule.GetValue(x * gridX, y * gridY, 0);

} // double Generator::operator()(int x, int y);

WG_NS_END
