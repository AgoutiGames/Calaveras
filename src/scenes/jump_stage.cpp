#include "scenes/jump_stage.hpp"

#include "core/scene_manager.hpp"

const char* JumpStage::type = "JumpStage";
const bool JumpStage::good = GameScene::register_class<JumpStage>(JumpStage::type);

JumpStage::JumpStage(salmon::MapRef map, SceneManager* scene_manager) :
    GameScene(map,scene_manager) {}

void JumpStage::init() {
    // Initializes all characters in scene
    GameScene::init();
    // Setup member vars here | example: put(m_speed, "m_speed");

}

void JumpStage::update() {
    // Add scene logic here
    salmon::InputCacheRef input = get_input_cache();
    if(input.just_pressed("Escape")) {
        m_scene_manager->next_scene("menu.tmx");
    }

    // Calls update on all characters in scene
    GameScene::update();
}
