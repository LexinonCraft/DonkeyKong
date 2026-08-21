#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetsManager {
public:
    enum class TextureId {
        DonkeyKongStill,
        DonkeyKongAngry1,
        DonkeyKongAngry2,
        DonkeyKongThrowingSide,
        DonkeyKongThrowingFront,
        DonkeyKongNice,
        JumpmanStill,
        JumpmanWalking1,
        JumpmanWalking2,
        JumpmanJumping,
        JumpmanClimbing,
        JumpmanDying1,
        JumpmanDying2,
        JumpmanDead,
        GirderRed,
        GirderBlue,
        BarrelFront1,
        BarrelFront2,
        BarrelSide1,
        BarrelSide2,
        LadderCyan,
        LadderYellow,
        PaulineStill,
        PaulineScream1,
        PaulineScream2,
        Help,
        Hammer,
        HeartNormal,
        HeartBroken,
        JumpmanHammerUpStill,
        JumpmanHammerUpWalking1,
        JumpmanHammerUpWalking2,
        JumpmanHammerDownStill,
        JumpmanHammerDownWalking1,
        JumpmanHammerDownWalking2,
    };

    AssetsManager(std::string textures_base_path, std::string font_file);

    const sf::Texture &get_texture(TextureId id) const;

    const sf::Font &get_font() const;

private:
    std::string textures_base_path;

    sf::Texture donkey_kong_still_texture;
    sf::Texture donkey_kong_angry1_texture;
    sf::Texture donkey_kong_angry2_texture;
    sf::Texture donkey_kong_throwing_side_texture;
    sf::Texture donkey_kong_throwing_front_texture;
    sf::Texture donkey_kong_nice_texture;
    sf::Texture jumpman_still_texture;
    sf::Texture jumpman_walking1_texture;
    sf::Texture jumpman_walking2_texture;
    sf::Texture jumpman_jumping_texture;
    sf::Texture jumpman_climbing_texture;
    sf::Texture jumpman_dying1_texture;
    sf::Texture jumpman_dying2_texture;
    sf::Texture jumpman_dead_texture;
    sf::Texture girder_red_texture;
    sf::Texture girder_blue_texture;
    sf::Texture barrel_front1_texture;
    sf::Texture barrel_front2_texture;
    sf::Texture barrel_side1_texture;
    sf::Texture barrel_side2_texture;
    sf::Texture ladder_cyan_texture;
    sf::Texture ladder_yellow_texture;
    sf::Texture pauline_still_texture;
    sf::Texture pauline_scream1_texture;
    sf::Texture pauline_scream2_texture;
    sf::Texture help_texture;
    sf::Texture hammer_texture;
    sf::Texture heart_normal_texture;
    sf::Texture heart_broken_texture;
    sf::Texture jumpman_hammer_up_still_texture;
    sf::Texture jumpman_hammer_up_walking1_texture;
    sf::Texture jumpman_hammer_up_walking2_texture;
    sf::Texture jumpman_hammer_down_still_texture;
    sf::Texture jumpman_hammer_down_walking1_texture;
    sf::Texture jumpman_hammer_down_walking2_texture;

    sf::Font font;

    void load(const std::string &filename, sf::Texture &texture);
};

#endif
