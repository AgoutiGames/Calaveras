#include "characters/cloud.hpp"

#include "core/game_scene.hpp"

const char* Cloud::type = "Cloud";
const bool Cloud::good = GameCharacter::register_class<Cloud>(Cloud::type);

Cloud::Cloud(salmon::ActorRef actor, GameScene* scene) : GameCharacter(actor, scene) {}

void Cloud::init() {
    // Setup member vars here | example: put(m_speed, "m_speed");
    put(m_speed, "speed");
}

void Cloud::update() {
    // Add character logic here
    move(m_speed,0);
    if(get_x() > m_scene->get_w()) {move(1.0f - get_w(),get_y(),true);}
}
