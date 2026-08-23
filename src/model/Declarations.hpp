#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

/**
 * @brief Type used for unique entity ids within the game world.
 */
typedef int Id;

class PlayerData;
class Stage;
class StageObserver;

// util
template <typename C> class AbstractComponentFactory;
class BaseEntity;
template <typename E> class Component;
template <typename C> class ComponentRepository;
class EntityFromComponentAux;
class EntityRepository;
class EntityRepositoryObserver;
class EntityVisitor;
class Ref;

class Platform;
class Barrel;
class PlatformComponentRepository;
class Girder;
class Player;
class Ladder;
class Climbable;
class Updatable;
class Enemy;
class Pickable;
class HammerPowerUp;
class DonkeyKong;
class BarrelStack;
class Pauline;
class DissolvingPlatform;
class Stage25MCompletionAnimation;
class Stage100MCompletionAnimation;
class PlayerDeathAnimation;
class AbstractAnimation;
class Jumpable;
class Ghost;
class Stage100M;
class Beam;

#endif
