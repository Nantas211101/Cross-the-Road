#include "ResourceHolder.hpp"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    std::unique_ptr<Resource> resource(new Resource()); // new pointer
    if (!resource->loadFromFile(filename))              // loading from file
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second); // checking the succesfull of the insertion
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename,
                                                const Parameter &secondpara)
{
    std::unique_ptr<Resource> resource(new Resource()); // new pointer
    if (!resource->loadFromFile(filename, secondpara))  // loading from file
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second); // checking the succesfull of the insertion
}

template <typename Resource,
          typename Identifier> // need template before every function
auto ResourceHolder<Resource, Identifier>::get(Identifier id) const -> Resource &
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}
