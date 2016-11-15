#include "Animation.hpp"

void Animation::setTexture(Texture* tex){
	textures.push_back(tex);
}

void Animation::setMesh(Mesh *mesh){
    meshes.push_back(mesh);
}

void Animation::setSheet(SpriteSheet* spritesheet){

    vector<std::string> v;
    for(map<std::string,Material*>::iterator it = spritesheet->sprites.begin(); it != spritesheet->sprites.end(); ++it) {
        cout << it->first << ": " << it->second->texture << endl;
        setTexture(it->second->texture);
        setMesh(it->second->mesh);
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
    sprite->texture = textures[index];
    sprite->mesh = meshes[index];
}

