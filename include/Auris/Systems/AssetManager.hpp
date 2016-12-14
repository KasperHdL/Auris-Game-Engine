#pragma once

#include "SRE/Texture.hpp"
#include <string>
#include <map>
#include <iostream>
#include <SDL.h>

namespace Auris{

    class AssetManager{
    public:
        static SRE::Texture* getTexture(std::string path);

    private:

        static std::map<std::string, SRE::Texture*> textures;

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
