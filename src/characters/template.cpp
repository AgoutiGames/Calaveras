#include "characters/template.hpp"

const char* Template::type = "Template";
const bool Template::good = GameCharacter::register_class<Template>(Template::type);

Template::Template(salmon::ActorRef actor, GameScene* scene) : GameCharacter(actor, scene) {}

void Template::init() {
    // Setup member vars here | example: put(m_speed, "m_speed");
    
    // Clear data accessed via put
    get_data().clear();
}

void Template::update() {
    // Add character logic here
    
}
