#include "scenes/template.hpp"

const char* Template::type = "Template";
const bool Template::good = GameScene::register_class<Template>(Template::type);

Template::Template(salmon::MapRef map, SceneManager* scene_manager) :
    GameScene(map,scene_manager) {}

void Template::init() {
    // Initializes all characters in scene
    GameScene::init();
    // Setup member vars here | example: put(m_speed, "m_speed");

    // Clear data accessed via put
    get_data().clear();
}

void Template::update() {
    // Add scene logic here
    
    // Calls update on all characters in scene
    GameScene::update();
}
