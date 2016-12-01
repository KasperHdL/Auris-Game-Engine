#include "Auris/GameObjects/Components/Animation.hpp"
using namespace Auris;
void Animation::setTexture(Texture* tex){
	textures.push_back(tex);
}

void Animation::setMesh(Mesh *mesh){
    meshes.push_back(mesh);
}

void Animation::setSheet(SpriteSheet* spritesheet){
    for(map<std::string,Material*>::iterator it = spritesheet->sprites.begin(); it != spritesheet->sprites.end(); ++it) {
        setTexture(it->second->texture);
        setMesh(it->second->mesh);
    }
}

void Animation::makeSequence(SpriteSheet* spritesheet, string name){
    for(map<std::string,Material*>::iterator it = spritesheet->sprites.begin(); it != spritesheet->sprites.end(); ++it) {
        //cout << name << " : " << it->first << endl;
        if(!it->first.compare(0,name.size(),name)){
        setTexture(it->second->texture);
        setMesh(it->second->mesh);
        }
    }
}

void Animation::delLastTexture()
{
	textures.pop_back();
}

void Animation::delLastMest(){
    meshes.pop_back();
}

void Animation::updateAnim(float dt)
{
	frameLength = length / textures.size();
	time += dt;
	if (time >= frameLength) {
		index++;
		if (index >= textures.size()) {
			index = 0;
		}
		time = glm::mod<float>(time, frameLength);
	}
}

Texture* Animation::getSprite()
{
	return textures[index];
}

void Animation::setSprite(Sprite *sprite){
    sprite->mesh = meshes[index];
}

