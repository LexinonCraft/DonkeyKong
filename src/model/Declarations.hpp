#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

/**
 * @brief Type used for unique entity ids within the game world.
 */
typedef int Id;

class PlayerData;
class Stage;
class StageObserver;

// animations
class AbstractAnimation;
class AnimationVisitor;
class PlayerDeathAnimation;
class Stage25MCompletionAnimation;
class Stage100MCompletionAnimation;

// components
class Climbable;
class ClimbableComponentFactory;
class ClimbableComponentRepository;
class Enemy;
class EnemyComponentFactory;
class EnemyComponentRepository;
class Jumpable;
class JumpableComponentFactory;
class JumpableComponentRepository;
class Pickable;
class PickableComponentFactory;
class PickableComponentRepository;
class Platform;
class PlatformComponentFactory;
class PlatformComponentRepository;
class Updatable;
class UpdatableComponentFactory;
class UpdatableComponentRepository;

// entities
class Barrel;
class BarrelStack;
class Beam;
class DissolvingPlatform;
class DonkeyKong;
class Ghost;
class Girder;
class HammerPowerUp;
class Ladder;
class Pauline;
class Player;

// stages
class Stage25M;
class Stage100M;

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

#endif
