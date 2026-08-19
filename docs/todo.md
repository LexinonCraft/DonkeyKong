# To-do

## High priority

- [x] Adapt the `Ladder` and `Player` classes to the ECS architecture
- [x] Add code comments
- [x] Add hammer power-up
- [ ] Add other stages
- [x] Fix bug where player/barrels can fall through two connected girders

## Medium priority

- [x] Implement level transitions and manage player data across levels
- [x] Make sure that entities are deleted only at the end of the update cycle, not during it
- [ ] Polish physics (~~prevent player from falling off girders at edges~~, ~~prevent player from jumping onto next girder~~, adjust hitboxes)
- [x] Add broken ladders
- [x] Allow barrels to roll down ladders
- [x] Seed for RNG

## Low priority

- [ ] Add textures
- [ ] Perform useful generalizations
- [ ] Add a main menu

## Nice to have

- [ ] Add sound effects and music
- [ ] Add persistence

## Things to do at the end

- Revisit code comments
- Update (architecture) documentation
- Implement unit tests
- Check whether entities handle deletion of referenced entities correctly
- Check which methods go to CPP files and which to HPP files
