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
#endif


//! The Animation class that extend the Nugget class
    /*! Used to make sprite animations
    */
namespace Auris{


//! The Animation class that extend the Nugget class
    /*! Used to make sprite animations
    */
    class AssetManager{
    private:

        static std::map<std::string, SRE::Texture*> textures; /*!< A map of string values, and Texture pointers: textures. That has a reference to all textures loaded. */
        static std::map<std::string, SpriteSheet*> spritesheets; /*!< A map of string values, and Spritesheet pointers: spritesheets. That has a reference to all spritesheets loaded. */

        static std::map<std::string, Mix_Music*> music; /*!< A map of string values, and Mix_Music pointers: music. That has a reference to all music loaded. */
        static std::map<std::string, Mix_Chunk*> sounds; /*!< A map of string values, and Mix_Chunk pointers: sound. That has a reference to all sound loaded. */

        //! A createSheet method, taking 2 arguments.
        /*! Creates a new spritesheet, based on the parth to the json file
         * \param  sheet a SpriteSheet pointer. An instance of the SpriteSheet to create.
         * \param pathToJson a string value. The string to the path of the json file.
         * \param bool whether or not the spritesheet will create flipped meshes for. (default value is false)
         * \param bool whether or not the texture will be filtered, default is false and results in point sampling
         */
        static void createSheet(SpriteSheet* sheet, std::string pathToJson, bool createFlipped = false, bool filterSampling = false);
    public:

        //! A getTexture method, taking 1 arguments.
        /*! Gives a new Texture pointer based on the filename inputted
         * \param  filename a string value. The name of the Texture file.
         * \return Texture pointer. An instance of the texture loaded from the file.
         */
        static SRE::Texture* getTexture(std::string filename, bool filterSampling = false);

        //! A getSpriteSheet method, taking 1 arguments.
        /* Gives a new SpriteSheet pointer based on the filename inputted
         * \param  filename a string value. The name of the SpriteSheet file.
         * \param bool whether or not the spritesheet will create flipped meshes for. (default value is false)
         * \param bool whether or not the texture will be filtered, default is false and results in point sampling
         * \return SpriteSheet pointer. An instance of the spritesheet loaded from the file.
         */
        static SpriteSheet* getSpriteSheet(std::string jsonFilename, bool createFlipped = false, bool filterSampling = false);

        //! A getSound method, taking 1 arguments.
        /*! Gives a new sound pointer based on the filename inputted
         * \param  filename a string value. The name of the sound file.
         * \return Mix_Chunk pointer. An instance of the sound loaded from the file.
         * \sa getMusic(std::string filename)
         */
        static Mix_Chunk* getSound(std::string filename);

        //! A getMusic method, taking 1 arguments.
        /*! Gives a new music pointer based on the filename inputted
         * \param  filename a string value. The name of the music file.
         * \return Mix_Music pointer. An instance of the music loaded from the file.
         * \sa getSound(std::string filename)
         */
        static Mix_Music* getMusic(std::string filename);

        //! A getDataPath method, taking 0-1 argument.
        /*! Helper Function to get the datafolder.
         * Returns the data folder path and is windows safe, it can be parsed a string which is simply appended
         * \param  file a string pointer. String which will be appended (default is "").
         * \return string. The path to data folder and file param
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
