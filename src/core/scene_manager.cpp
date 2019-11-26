#include "core/scene_manager.hpp"

#include <iostream>

SceneManager::SceneManager(int x_res, int y_res,bool fullscreen) : m_game(x_res, y_res, fullscreen) {}

bool SceneManager::load_scene(std::string map_filename) {
    if(m_game.load_map(map_filename)) {
        GameScene* scene = GameScene::parse_scene(m_game.get_map(), this);
        if(scene == nullptr) {
            std::cerr << "Failed to parse scene: " << map_filename << "!\n";
            return false;
        }
        m_scenes.emplace(scene);
        m_scenes.top()->init();
        return true;
    }
    else {
        std::cerr << "Failed to load scene: " << map_filename << "!\n";
        return false;
    }
}
void SceneManager::close_scene() {
    m_game.close_map();
    m_scenes.pop();
}

bool SceneManager::run() {
    if(!m_run) {return false;}
    if(m_next_scene != "") {
        close_scene();
        if(!load_scene(m_next_scene)) {return false;}
        m_next_scene = std::string("");
    }
    if(!m_scenes.empty() && m_game.update()) {
        m_scenes.top()->update();
        m_game.render();
        return true;
    }
    else {return false;}
}
