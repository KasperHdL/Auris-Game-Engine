#pragma once

#include <SDL.h>
#include <map>

using namespace std;
class Keys {
public:
	Keys();
	~Keys();
	void setKey(string key, SDL_Scancode mappedkey); ///A method to map a string to a SDL key
	SDL_Scancode getKey(string key);///A method to get the SDL key based on the string input
private:

	map<string, SDL_Scancode> allKeys; ///A map to hold all the SDL keys, and the strings that correspond to that key
};
