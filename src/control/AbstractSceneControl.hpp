#ifndef ABSTRACT_SCENE_CONTROL_HPP
#define ABSTRACT_SCENE_CONTROL_HPP

#include <functional>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief Abstract base class for a control class managing a specific scene (e.g. title screen, stage screen, game over screen).
 *
 */
class AbstractSceneControl {
public:
    /**
     * @brief An instruction to the main game loop about whether and which scene to switch to next.
     */
    enum class NextScene {
        Stay,            // Stay in the current scene
        TitleScreen,     // Switch to the title screen
        StageTransition, // Switch to the stage transition screen
        Stage,           // Switch to the stage screen
        GameOver,        // Switch to the game over screen
    };

    /**
     * @brief Construct a new Abstract Scene Control object without a window. This is useful for testing purposes.
     */
    AbstractSceneControl() = default;

    /**
     * @brief Construct a new Abstract Scene Control object
     *
     * @param window The window to draw the scene to.
     */
    AbstractSceneControl(sf::RenderWindow &window) : window(std::ref(window)) {}

    virtual ~AbstractSceneControl() {}

    /**
     * @brief Handle an SFML event (e.g. key press, mouse click, window close).
     *
     * @param event The SFML event to handle.
     */
    virtual void handle_event(sf::Event *event) = 0;

    /**
     * @brief Handle continuous input (e.g. holding down a key). Called once per frame.
     */
    virtual void handle_input() = 0;

    /**
     * @brief Update the scene. Called once per frame.
     *
     * @param dt The time elapsed since the last frame, in seconds.
     */
    virtual void update(float dt) = 0;

    /**
     * @brief Draw the scene to the window. Called once per frame.
     */
    virtual void draw() = 0;

    /**
     * @brief Get the instruction for the main game loop about whether and which scene to switch to next.
     *
     * @returns The scene switch instruction.
     */
    virtual NextScene get_next_scene() const = 0;

protected:
    std::optional<std::reference_wrapper<sf::RenderWindow>> window;
};

#endif
