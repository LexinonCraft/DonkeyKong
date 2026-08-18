#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetsManager {
public:
    enum class TextureId {
        DonkeyKong,
        JumpmanStill,
        JumpmanWalking1,
        JumpmanWalking2,
        JumpmanJumping,
        JumpmanClimbing,
        GirderRed,
        GirderBlue,
        BarrelFront1,
        BarrelFront2,
        BarrelSide1,
        BarrelSide2,
        LadderCyan,
        LadderYellow
    };

    AssetsManager(std::string textures_base_path, std::string font_file);

    const sf::Texture &get_texture(TextureId id) const;

    const sf::Font &get_font() const;

private:
    std::string textures_base_path;

    sf::Texture donkey_kong_texture;
    sf::Texture jumpman_still_texture;
    sf::Texture jumpman_walking1_texture;
    sf::Texture jumpman_walking2_texture;
    sf::Texture jumpman_jumping_texture;
    sf::Texture jumpman_climbing_texture;
    sf::Texture girder_red_texture;
    sf::Texture girder_blue_texture;
    sf::Texture barrel_front1_texture;
    sf::Texture barrel_front2_texture;
    sf::Texture barrel_side1_texture;
    sf::Texture barrel_side2_texture;
    sf::Texture ladder_cyan_texture;
    sf::Texture ladder_yellow_texture;

    sf::Font font;

    void load(const std::string &filename, sf::Texture &texture);
};

#endif
