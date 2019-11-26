#ifndef SCENE_MANAGER_HPP_INCLUDED
#define SCENE_MANAGER_HPP_INCLUDED

#include <memory>
#include <stack>
#include <string>

#include "gameinfo.hpp"
#include "core/game_scene.hpp"

class SceneManager {
public:
    SceneManager(int x_res, int y_res,bool fullscreen);
    bool load_scene(std::string map_filename);
    void close_scene();
    void next_scene(std::string map_filename) {m_next_scene = map_filename;}
    void shutdown() {m_run = false;}
    bool run();

    salmon::GameInfo& get_game() {return m_game;}
private:
    bool m_run = true;
    salmon::GameInfo m_game;
    std::stack<std::unique_ptr<GameScene>> m_scenes;
    std::string m_next_scene;
};

#endif // SCENE_MANAGER_HPP_INCLUDED
