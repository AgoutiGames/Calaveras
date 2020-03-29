#ifndef SCENE_MANAGER_HPP_INCLUDED
#define SCENE_MANAGER_HPP_INCLUDED

#include <memory>
#include <stack>
#include <string>

#include "gameinfo.hpp"
#include "core/game_scene.hpp"

/**
 * @brief Takes care of securely loading the next scene or shutting down the game
 * @note Inherits from GameInfo and deals with updating, rendering and map loading and closing.
 */
class SceneManager : public salmon::GameInfo {
public:
    SceneManager(std::string map_filename);

    /**
     * @brief Changes to this scene in next frame
     * @param relative path to next map/ .tmx file
     * @note The path is always relative to the directory of the currently loaded map
     */
    void next_scene(std::string map_filename) {m_next_scene = map_filename;}

    /// Shuts down the game in next frame
    void shutdown() {m_run = false;}

    /**
     * @brief Runs the game by updating, rendering, checking for next scene
     * @return false if game has ended/ shutdown was called or fatal error occured
     * @warning Don't call this outside of main!
     */
    bool run();

private:
    bool load_scene(std::string map_filename);
    void close_scene();

    bool m_run = true;
    std::stack<std::unique_ptr<GameScene>> m_scenes;
    std::string m_next_scene;
};

#endif // SCENE_MANAGER_HPP_INCLUDED
