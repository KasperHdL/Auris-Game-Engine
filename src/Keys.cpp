#include "Keys.hpp"

///maps the string to a SDL scancode
void Keys::setKey(string key, SDL_Scancode mappedkey) {
	allKeys[key] = mappedkey;///save the SDL key in the map all keys
}

///returns the SDL key corresponding to the string that has been set in the allKeys map (If it has not been set, it will return null)
SDL_Scancode Keys::getKey(string key) {
	return allKeys[key]; ///returns the SDL key with the string mapped
}
