#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

/**
 * @brief Manages game assets (textures, fonts, and contributors list).
 */
class AssetsManager {
public:
    /**
     * @brief Identifiers for game textures.
     */
    enum class TextureId {
        JumpmanStill,
        JumpmanWalking1,
        JumpmanWalking2,
        JumpmanJumping,
        JumpmanClimbing,
        JumpmanDying1,
        JumpmanDying2,
        JumpmanDead,
        JumpmanHammerUpStill,
        JumpmanHammerUpWalking1,
        JumpmanHammerUpWalking2,
        JumpmanHammerDownStill,
        JumpmanHammerDownWalking1,
        JumpmanHammerDownWalking2,
        DonkeyKongStill,
        DonkeyKongAngry1,
        DonkeyKongAngry2,
        DonkeyKongThrowingSide,
        DonkeyKongThrowingFront,
        DonkeyKongNice,
        DonkeyKongClimbing1,
        DonkeyKongClimbing2,
        DonkeyKongFalling1,
        DonkeyKongFalling2,
        DonkeyKongFalling3,
        PaulineStill,
        PaulineScream1,
        PaulineScream2,
        BarrelFront1,
        BarrelFront2,
        BarrelSide1,
        BarrelSide2,
        Ghost1,
        Ghost2,
        GirderRed,
        GirderBlue,
        LadderCyan,
        LadderYellow,
        Help,
        Hammer,
        HeartNormal,
        HeartBroken,
    };

    /**
     * @brief Initializes the AssetsManager. Loads all assets into memory
     * for later retrieval. Fails if any asset cannot be loaded.
     */
    AssetsManager();

    /**
     * @brief Get the SFML texture object corresponding to the given TextureId.
     *
     * @param id Identifier of the texture to retrieve
     * @returns Reference to the corresponding sf::Texture object
     */
    const sf::Texture &get_texture(TextureId id) const;

    /**
     * @brief Get the SFML font object for the font used in the game.
     *
     * @returns Reference to the sf::Font object
     */
    const sf::Font &get_font() const { return font; }

    /**
     * @brief Get the contributors list as a string, loaded from the contributors file if present or a fallback string otherwise.
     *
     * @returns Reference to the contributors string
     */
    const std::string &get_contributors() const { return contributors; }

private:
    sf::Texture jumpman_still_texture;
    sf::Texture jumpman_walking1_texture;
    sf::Texture jumpman_walking2_texture;
    sf::Texture jumpman_jumping_texture;
    sf::Texture jumpman_climbing_texture;
    sf::Texture jumpman_dying1_texture;
    sf::Texture jumpman_dying2_texture;
    sf::Texture jumpman_dead_texture;
    sf::Texture jumpman_hammer_up_still_texture;
    sf::Texture jumpman_hammer_up_walking1_texture;
    sf::Texture jumpman_hammer_up_walking2_texture;
    sf::Texture jumpman_hammer_down_still_texture;
    sf::Texture jumpman_hammer_down_walking1_texture;
    sf::Texture jumpman_hammer_down_walking2_texture;
    sf::Texture donkey_kong_still_texture;
    sf::Texture donkey_kong_angry1_texture;
    sf::Texture donkey_kong_angry2_texture;
    sf::Texture donkey_kong_throwing_side_texture;
    sf::Texture donkey_kong_throwing_front_texture;
    sf::Texture donkey_kong_nice_texture;
    sf::Texture donkey_kong_climbing1_texture;
    sf::Texture donkey_kong_climbing2_texture;
    sf::Texture donkey_kong_falling1_texture;
    sf::Texture donkey_kong_falling2_texture;
    sf::Texture donkey_kong_falling3_texture;
    sf::Texture pauline_still_texture;
    sf::Texture pauline_scream1_texture;
    sf::Texture pauline_scream2_texture;
    sf::Texture barrel_front1_texture;
    sf::Texture barrel_front2_texture;
    sf::Texture barrel_side1_texture;
    sf::Texture barrel_side2_texture;
    sf::Texture ghost1_texture;
    sf::Texture ghost2_texture;
    sf::Texture ladder_cyan_texture;
    sf::Texture ladder_yellow_texture;
    sf::Texture girder_red_texture;
    sf::Texture girder_blue_texture;
    sf::Texture help_texture;
    sf::Texture hammer_texture;
    sf::Texture heart_normal_texture;
    sf::Texture heart_broken_texture;

    sf::Font font;
    std::string contributors;

    /**
     * @brief Load a texture from a file.
     *
     * @param filename The name of the texture file to load (without the base path).
     * @param texture Reference to the sf::Texture object to load the texture into.
     */
    void load(const std::string &filename, sf::Texture &texture);

    /**
     * @brief Read the contributors list from the file.
     *
     * @returns A string with the contributors list from the file if present or a fallback string.
     */
    std::string read_contributors() const;
};

#endif
