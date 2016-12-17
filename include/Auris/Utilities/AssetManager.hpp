#pragma once

#include "SRE/Texture.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Utilities/picojson.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <SDL.h>

#ifdef _WIN32 // Windows
#include <SDL_mixer.h>
#elif __linux__ // Linux
#include <SDL2/SDL_mixer.h>
#else
cout << "Error: Unsupported OS" << endl;
#endif

namespace Auris{
    class AssetManager{
    private:

        static std::map<std::string, SRE::Texture*> textures;
        static std::map<std::string, SpriteSheet*> spritesheets;

        static std::map<std::string, Mix_Music*> music;
        static std::map<std::string, Mix_Chunk*> sounds;

        static void createSheet(SpriteSheet* sheet, std::string pathToJson, bool createFlipped = false, bool filterSampling = false);
    public:
        static SRE::Texture* getTexture(std::string filename, bool filterSampling = false);
        static SpriteSheet* getSpriteSheet(std::string jsonFilename, bool createFlipped = false, bool filterSampling = false);

        static Mix_Chunk* getSound(std::string filename);
        static Mix_Music* getMusic(std::string filename);

        //! Helper Function to get the datafolder
        /*! returns the data folder path and is windows safe, it can be parsed a string which is simply appended
         * \param optional - string which will be appended, defaults to ""
         * \return string with path to data folder and file param
         */
        static std::string getDataPath(const std::string &file = ""){
            //We need to choose the path separator properly based on which
            //platform we're running on, since Windows uses a different
            //separator than most systems
#ifdef _WIN32
            const char PATH_SEP = '\\';
#else
            const char PATH_SEP = '/';
#endif
            //This will hold the base data path:
            //We give it static lifetime so that we'll only need to call
            //SDL_GetBasePath once to get the executable path
            static std::string baseRes;
            if (baseRes.empty()){
                //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
                char *basePath = SDL_GetBasePath();
                if (basePath){
                    baseRes = basePath;
                    SDL_free(basePath);
                }
                else {
                    std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
                    return "";
                }

                baseRes = baseRes + "data" + PATH_SEP;
            }

            //If we want a specific file path in the data dir or just the data dir
            return file.empty() ? baseRes: baseRes + file;
        }


    };

}
