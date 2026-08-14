#ifndef TEXTURE_REGISTRY_HPP
#define TEXTURE_REGISTRY_HPP

#include <SFML/Graphics/Texture.hpp>
#include <string>

class TextureRegistry {
public:
    enum class TextureId {
        DonkeyKong,
        // Add more texture identifiers as needed
    };

    TextureRegistry(std::string base_path);

    const sf::Texture &get_texture(TextureId id) const;

private:
    std::string base_path;
    sf::Texture donkey_kong_texture;

    void load(const std::string &filename, sf::Texture &texture);
};

#endif
