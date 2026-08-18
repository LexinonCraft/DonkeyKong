#include "AssetsManager.hpp"

AssetsManager::AssetsManager(std::string base_path, std::string font_file) : textures_base_path(base_path), font(font_file) {
    load("DonkeyKong.png", donkey_kong_texture);
    load("jumpman.png", jumpman_texture);
    load("girder_red.png", girder_red_texture);
    load("girder_blue.png", girder_blue_texture);
}

const sf::Texture &AssetsManager::get_texture(TextureId id) const {
    switch (id) {
        case TextureId::DonkeyKong:
            return donkey_kong_texture;
        case TextureId::Jumpman:
            return jumpman_texture;
        case TextureId::GirderRed:
            return girder_red_texture;
        case TextureId::GirderBlue:
            return girder_blue_texture;
        default:
            throw std::runtime_error("Unknown texture ID");
    }
}

const sf::Font &AssetsManager::get_font() const {
    return font;
}

void AssetsManager::load(const std::string &filename, sf::Texture &texture) {
    if (!texture.loadFromFile(textures_base_path + filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
}
