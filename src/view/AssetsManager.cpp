#include "AssetsManager.hpp"

AssetsManager::AssetsManager(std::string base_path, std::string font_file) : textures_base_path(base_path), font(font_file) {
    load("donkey_kong_still.png", donkey_kong_still_texture);
    load("donkey_kong_angry.png", donkey_kong_angry_texture);
    load("donkey_kong_throwing_side.png", donkey_kong_throwing_side_texture);
    load("donkey_kong_throwing_front.png", donkey_kong_throwing_front_texture);
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
    load("pauline_still.png", pauline_still_texture);
    load("pauline_scream1.png", pauline_scream1_texture);
    load("pauline_scream2.png", pauline_scream2_texture);
    load("help.png", help_texture);
    load("hammer.png", hammer_texture);
}

const sf::Texture &AssetsManager::get_texture(TextureId id) const {
    switch (id) {
        case TextureId::DonkeyKongStill:
            return donkey_kong_still_texture;
        case TextureId::DonkeyKongAngry:
            return donkey_kong_angry_texture;
        case TextureId::DonkeyKongThrowingSide:
            return donkey_kong_throwing_side_texture;
        case TextureId::DonkeyKongThrowingFront:
            return donkey_kong_throwing_front_texture;
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
        case TextureId::PaulineStill:
            return pauline_still_texture;
        case TextureId::PaulineScream1:
            return pauline_scream1_texture;
        case TextureId::PaulineScream2:
            return pauline_scream2_texture;
        case TextureId::Help:
            return help_texture;
        case TextureId::Hammer:
            return hammer_texture;
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
