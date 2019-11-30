#include "core/scene_manager.hpp"

#include <iostream>

SceneManager::SceneManager(std::string map_filename) {
    load_scene(map_filename);
}

bool SceneManager::load_scene(std::string map_filename) {
    if(load_map(map_filename)) {
        GameScene* scene = GameScene::parse_scene(get_map(), this);
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
    close_map();
    m_scenes.pop();
}

bool SceneManager::run() {
    if(!m_run) {return false;}
    if(m_next_scene != "") {
        close_scene();
        if(!load_scene(m_next_scene)) {return false;}
        m_next_scene = std::string("");
    }
    if(!m_scenes.empty() && update()) {
        m_scenes.top()->update();
        render();
        return true;
    }
    else {return false;}
}
