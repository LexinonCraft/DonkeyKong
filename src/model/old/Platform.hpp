#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/System/Vector2.hpp>
#include "Declarations.hpp"
#include "../util/RepositoryElement.hpp"
#include "../util/Repository.hpp"

/// An abstract platform in the game world (e. g. a girder).
class Platform : public RepositoryElement<Platform> {
public:
    Platform(Ref<Platform> ref) : RepositoryElement<Platform>(ref) {}

    virtual ~Platform() {}

    /// Returns true iff the platform covers the given horizontal position x.
    virtual bool covers_x(float x) const = 0;
    /// Returns the height (y) of the platform surface at horizontal position x.
    virtual float surface_y_at(float x) const = 0;
    /// Returns the slope (dy/dx) of the platform surface at horizontal position x.
    virtual float slope_at(float x) const = 0;
    /// Returns true iff the player currently should be able to stand on the platform.
    virtual bool is_active() const = 0;
    /// Returns the displacement an object on the platform would experience at horizontal position x over time dt (relevant for moving platforms).
    virtual sf::Vector2f displacement_at(float x, float dt) const = 0;
    // Returns -1 for a platform sloping down to the left, +1 for a platform sloping down to the right, and 0 for a horizontal platform.
    virtual int downhill_sign() const = 0;
    // Returns the endpoint of the platform that is higher in the world coordinates (i. e. has a smaller y value).
    virtual sf::Vector2f high_end() const = 0;
    /// Updates the platform's state over time dt (e. g. for moving platforms).
    virtual void update(float dt) = 0;

    virtual void accept(PlatformVisitor &visitor) const = 0;
};

#endif
