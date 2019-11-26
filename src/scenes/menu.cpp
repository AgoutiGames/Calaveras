#include "scenes/menu.hpp"

#include "core/scene_manager.hpp"

#include <iostream>

const char* Menu::type = "Menu";
const bool Menu::good = GameScene::register_class<Menu>(Menu::type);

Menu::Menu(salmon::MapRef map, SceneManager* scene_manager) :
    GameScene(map,scene_manager) {}

void Menu::init() {
    // Initializes all characters in scene
    GameScene::init();
    // Setup member vars here | example: put(m_speed, "m_speed");

}

void Menu::update() {
    // Add scene logic here
    salmon::InputCacheRef input = get_input_cache();
    if(input.just_pressed("Escape")) {
        m_scene_manager->shutdown();
    }

    // Calls update on all characters in scene
    GameScene::update();
}

void Menu::button_pressed(std::string id) {
    if(id == "Quit") {
        m_scene_manager->shutdown();
    }
    else if(id == "Start") {
        m_scene_manager->next_scene("stage1.tmx");
    }
    else {
        std::cerr << "Button type: " << id << " is unrecognized!\n";
    }
}
