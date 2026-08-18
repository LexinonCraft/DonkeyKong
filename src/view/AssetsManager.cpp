#include "AssetsManager.hpp"

AssetsManager::AssetsManager(std::string base_path, std::string font_file) : textures_base_path(base_path), font(font_file) {
    load("DonkeyKong.png", donkey_kong_texture);
    load("jumpman_still.png", jumpman_still_texture);
    load("girder_red.png", girder_red_texture);
    load("girder_blue.png", girder_blue_texture);
    load("jumpman_walking1.png", jumpman_walking1_texture);
    load("jumpman_walking2.png", jumpman_walking2_texture);
    load("jumpman_jumping.png", jumpman_jumping_texture);
    load("jumpman_climbing.png", jumpman_climbing_texture);
}

const sf::Texture &AssetsManager::get_texture(TextureId id) const {
    switch (id) {
        case TextureId::DonkeyKong:
            return donkey_kong_texture;
        case TextureId::JumpmanStill:
            return jumpman_still_texture;
        case TextureId::JumpmanWalking1:
            return jumpman_walking1_texture;
        case TextureId::JumpmanWalking2:
            return jumpman_walking2_texture;
        case TextureId::JumpmanJumping:
            return jumpman_jumping_texture;
        case TextureId::JumpmanClimbing:
            return jumpman_climbing_texture;
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
