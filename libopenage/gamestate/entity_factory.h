// Copyright 2023-2023 the openage authors. See copying.md for legal info.

#pragma once

#include <memory>
#include <shared_mutex>

#include <nyan/nyan.h>

#include "coord/phys.h"
#include "gamestate/types.h"

namespace openage {

namespace event {
class EventLoop;
} // namespace event

namespace renderer {
class RenderFactory;
}

namespace gamestate {
class GameEntity;
class GameState;

/**
 * Creates game entities that contain data of objects inside the game world.
 */
class EntityFactory {
public:
	/**
     * Create a new entity factory for game entities.
     */
	EntityFactory();
	~EntityFactory() = default;

	/**
     * Create a new game entity.
	 *
	 * This just creates the entity. The caller is responsible for initializing
	 * its components and placing it into the game.
     *
	 * @param loop Event loop for the gamestate.
	 * @param state State of the game.
	 * @param nyan_entity fqon of the GameEntity data in the nyan database.
	 *
	 * @return New game entity.
	 */
	std::shared_ptr<GameEntity> add_game_entity(const std::shared_ptr<openage::event::EventLoop> &loop,
	                                            const std::shared_ptr<GameState> &state,
	                                            const nyan::fqon_t &nyan_entity);

	/**
	 * Attach a renderer which enables graphical display options for all ingame entities.
	 *
	 * @param render_factory Factory for creating connector objects for gamestate->renderer
	 *                       communication.
	 */
	void attach_renderer(const std::shared_ptr<renderer::RenderFactory> &render_factory);

private:
	/**
	 * Initialize components of a game entity.
	 *
	 * @param loop Event loop for the gamestate.
	 * @param state State of the game.
	 * @param entity Game entity.
	 * @param nyan_entity fqon of the GameEntity data in the nyan database.
	 */
	void init_components(const std::shared_ptr<openage::event::EventLoop> &loop,
	                           const std::shared_ptr<GameState> &state,
	                           const std::shared_ptr<GameEntity> &entity,
	                           const nyan::fqon_t &nyan_entity);

	/**
     * Get a unique ID for creating a game entity.
     *
     * @return Unique ID for a game entity.
     */
	entity_id_t get_next_id();

	/**
     * ID of the next game entity to be created.
     */
	entity_id_t next_id;

	/**
	 * Factory for creating connector objects to the renderer which make game entities displayable.
	 */
	std::shared_ptr<renderer::RenderFactory> render_factory;

	// TODO: Cache created game entities.

	/**
     * Mutex for thread safety.
     */
	std::shared_mutex mutex;
};
} // namespace gamestate
} // namespace openage
