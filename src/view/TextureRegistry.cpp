#include "TextureRegistry.hpp"

TextureRegistry::TextureRegistry(std::string base_path) : base_path(base_path) {
    load("DonkeyKong.png", donkey_kong_texture);
}

const sf::Texture &TextureRegistry::get_texture(TextureId id) const {
    switch (id) {
        case TextureId::DonkeyKong:
            return donkey_kong_texture;
        // Add more cases for other textures as needed
        default:
            throw std::runtime_error("Unknown texture ID");
    }
}

void TextureRegistry::load(const std::string &filename, sf::Texture &texture) {
    if (!texture.loadFromFile(base_path + filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
}
