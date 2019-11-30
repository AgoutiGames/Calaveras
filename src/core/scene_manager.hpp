#ifndef SCENE_MANAGER_HPP_INCLUDED
#define SCENE_MANAGER_HPP_INCLUDED

#include <memory>
#include <stack>
#include <string>

#include "gameinfo.hpp"
#include "core/game_scene.hpp"

class SceneManager : public salmon::GameInfo {
public:
    SceneManager(std::string map_filename);
    void next_scene(std::string map_filename) {m_next_scene = map_filename;}
    void shutdown() {m_run = false;}
    bool run();

private:
    bool load_scene(std::string map_filename);
    void close_scene();

    bool m_run = true;
    std::stack<std::unique_ptr<GameScene>> m_scenes;
    std::string m_next_scene;
};

#endif // SCENE_MANAGER_HPP_INCLUDED
