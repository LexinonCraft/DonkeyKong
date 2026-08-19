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
    load("barrel_front1.png", barrel_front1_texture);
    load("barrel_front2.png", barrel_front2_texture);
    load("barrel_side1.png", barrel_side1_texture);
    load("barrel_side2.png", barrel_side2_texture);
    load("ladder_cyan.png", ladder_cyan_texture);
    load("ladder_yellow.png", ladder_yellow_texture);
    load("hammer.png", hammer_texture);
    load("jumpman_hammer_up_still.png", jumpman_hammer_up_still_texture);
    load("jumpman_hammer_up_walking1.png", jumpman_hammer_up_walking1_texture);
    load("jumpman_hammer_up_walking2.png", jumpman_hammer_up_walking2_texture);
    load("jumpman_hammer_down_still.png", jumpman_hammer_down_still_texture);
    load("jumpman_hammer_down_walking1.png", jumpman_hammer_down_walking1_texture);
    load("jumpman_hammer_down_walking2.png", jumpman_hammer_down_walking2_texture);
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
        case TextureId::BarrelFront1:
            return barrel_front1_texture;
        case TextureId::BarrelFront2:
            return barrel_front2_texture;
        case TextureId::BarrelSide1:
            return barrel_side1_texture;
        case TextureId::BarrelSide2:
            return barrel_side2_texture;
        case TextureId::LadderCyan:
            return ladder_cyan_texture;
        case TextureId::LadderYellow:
            return ladder_yellow_texture;
        case TextureId::Hammer:
            return hammer_texture;
        case TextureId::JumpmanHammerUpStill:
            return jumpman_hammer_up_still_texture;
        case TextureId::JumpmanHammerUpWalking1:
            return jumpman_hammer_up_walking1_texture;
        case TextureId::JumpmanHammerUpWalking2:
            return jumpman_hammer_up_walking2_texture;
        case TextureId::JumpmanHammerDownStill:
            return jumpman_hammer_down_still_texture;
        case TextureId::JumpmanHammerDownWalking1:
            return jumpman_hammer_down_walking1_texture;
        case TextureId::JumpmanHammerDownWalking2:
            return jumpman_hammer_down_walking2_texture;
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
