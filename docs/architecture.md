# Architecture

## Model View Controller

This project uses the [Model View Controller](https://de.wikipedia.org/wiki/Model_View_Controller) pattern. The source files are organized into three main directories:

* `model`: Contains classes representing the game objects and implementing the game logic.
* `view`: Contains the user interface components and rendering logic.
* `controller`: Contains the input handling and game state management logic.

## Entity Component System

To manage different game entities and their behaviors efficiently and flexibly, we employ a mixture of an inheritance-based design and the [Entity Component System](https://en.wikipedia.org/wiki/Entity_component_system) pattern. This allows for better separation of concerns and easier addition of new game objects and other features (such as saving/loading the game).

* Entity: A game object in a level, such as a player, a barrel or a girder. For each entity type, there is a corresponding child class of `BaseEntity` in the `model/entities` directory, which defines its properties and behaviors. All entities in a level are identified by and ID and managed by an instance of the `EntityRepository` class. Each entity stores its ID and a reference to the repository it belongs to. An entity can also reference other entities in the same level using `std::weak_ptr`, which allows safely deleting entities from the repository. In the future, we might want to refer to other entities additionally by their ID instead of just a `std::weak_ptr`, to allow for more flexible entity management (e.g., when saving/loading levels). The `EntityVisitor` class defines a visitor pattern for entities, allowing for different behaviors to be implemented for each entity type without modifying the entity classes themselves. Each entity implements an `accept` method that calls the appropriate `visit` method of the visitor class.
* Component: An aspect of an entity's behavior and its interaction with the level. For example, attaching `Component<Updatable>` to an entity allows you to define code that is executed every frame (by implementing the `update` method from the abstract `Updatable` class). Meanwhile, `Component<Platform>` lets an entity implementing the abstract `Platform` class act as a platform to other entities. Also, a component might contain additional data, such as `DrawableComponent`, which could store a sprite or animation data. The `ComponentRepository<C>` class maps entity IDs to their corresponding components of type `C` and add/deletes components by oberving the `EntityRepository` for entity creation and deletion events. In the `model/components` directory, you find for each component type `C` (except for those relevant to the view):
    * The definition of the component class itself or an abstract class to be implemented by the entity class (in that case, `Component<C>` will be the component class that simply acts as a pointer to the entity).
    * A factory class that defines for each entity type, whether and how to create a component of type `C` for an entity.
    * A repository class that extends `ComponentRepository<C>` and can add useful methods such as `update_all` or `find_platform_underneath`.

Note that we do not use a pure ECS design, where entities are just IDs and all data is stored in components. Instead, we use a hybrid approach where each entity has its own class that can contain additional data and methods while still allowing for flexible composition of behaviors through components. Also, it simplies adhering to the MVC pattern, as we can move data relevant to the view (such as sprite or animation data) from the entity class to a dedicated component (`DrawableComponent`) whereas the game logic runs directly in the entity classes.
