#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetsManager {
public:
    enum class TextureId {
        DonkeyKong,
        Jumpman,
        GirderRed,
    };

    AssetsManager(std::string textures_base_path, std::string font_file);

    const sf::Texture &get_texture(TextureId id) const;

    const sf::Font &get_font() const;

private:
    std::string textures_base_path;
    sf::Texture donkey_kong_texture;
    sf::Texture jumpman_texture;
    sf::Texture girder_red_texture;
    sf::Font font;

    void load(const std::string &filename, sf::Texture &texture);
};

#endif
