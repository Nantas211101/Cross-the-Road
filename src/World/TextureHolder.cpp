#include "../../include/World/TextureHolder.h"

void TextureHolder::load(Textures::ID id, const std::string& filename){
	// Create and load resource
	std::unique_ptr<sf::Texture> resource(new sf::Texture());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

sf::Texture& TextureHolder::get(Textures::ID id){
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

const sf::Texture&	TextureHolder::get(Textures::ID id) const {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

void TextureHolder::insertResource(Textures::ID id, std::unique_ptr<sf::Texture> resource){
	// Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}