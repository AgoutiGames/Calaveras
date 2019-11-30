#include "characters/button.hpp"

#include "scenes/menu.hpp"

const char* Button::type = "Button";
const bool Button::good = GameCharacter::register_class<Button>(Button::type);

Button::Button(salmon::ActorRef actor, GameScene* scene) : GameCharacter(actor, scene) {}

void Button::init() {
    // Setup member vars here | example: put(m_speed, "m_speed");
    put(m_id, "id");
    put(m_sound, "sound");
}

void Button::update() {
    // Add character logic here

    set_animation(salmon::AnimationType::current, salmon::Direction::current,0);

    for(salmon::CollisionRef& c : get_collisions()) {
        if(c.mouse()) {
            set_animation(salmon::AnimationType::current, salmon::Direction::current,1);
            salmon::InputCacheRef input = m_scene->get_input_cache();
            salmon::MouseState mouse = input.get_mouse_state();
            if(mouse.left.pressed) {
                m_scene->get_audio_manager().get_sound(m_sound,true).play();
                static_cast<Menu*>(m_scene)->button_pressed(m_id);
            }
        }
    }
    clear_collisions();
}
