#include "characters/frog.hpp"

#include "core/game_scene.hpp"
#include "core/scene_manager.hpp"
#include "characters/arrow.hpp"

const char* Frog::type = "Frog";
const bool Frog::good = GameCharacter::register_class<Frog>(Frog::type);

Frog::Frog(salmon::ActorRef actor, GameScene* scene) : GameCharacter(actor, scene) {}

void Frog::init() {
    // Setup member vars here | example: put(m_speed, "m_speed");
    put(m_gravity, "gravity");
    put(m_jump_sound, "jump_sound");
    put(m_death_sound, "death_sound");
    m_jump = m_scene->get_audio_manager().get_sound(m_jump_sound);
    m_death = m_scene->get_audio_manager().get_sound(m_death_sound);

    m_scene->get_camera().bind_actor(*this);
    m_arrow = m_scene->get_character<Arrow>();
}

void Frog::update() {
    //if(m_first) {m_arrow = m_scene->get_character<Arrow>(); m_first = false;}

    if(m_dead) {
        if(m_death.playing()) {return;}
        else {
            m_scene->get_scene_manager().next_scene("menu.tmx");
            return;
        }
    }

    float delta = m_scene->get_delta_time();

    // Add character logic here
    if(!on_ground()) {
        m_y_speed += m_gravity * delta;
        if(m_y_speed < 0) {
            if(get_animation() != salmon::AnimationType::jump || get_current_anim_frame() < 12) {
                animate(salmon::AnimationType::jump, salmon::Direction::none);
            }
        }
        else {
            if(get_current_anim_frame() < 12) {set_animation(salmon::AnimationType::jump, salmon::Direction::none,12);}
            if(get_animation() != salmon::AnimationType::jump || get_current_anim_frame() < get_anim_frame_count()) {
                animate(salmon::AnimationType::jump, salmon::Direction::none);
            }
        }
    }
    else {
        if(m_arrow->ready()) {
            m_jump.play();
            m_arrow->apply_force(m_x_speed,m_y_speed);
        }
        animate(salmon::AnimationType::idle, salmon::Direction::none);
    }

    if(!move(m_x_speed * delta,m_y_speed * delta)) {
        if(on_ground(salmon::Direction::left) || on_ground(salmon::Direction::right)) {m_x_speed = -0.5f * m_x_speed;}
        else {m_x_speed = 0;}
        m_y_speed = 0;
    };

    for(salmon::CollisionRef c : get_collisions()) {
        if(c.tile() && c.other_hitbox() == "DEADLY") {
            m_dead = true;
            m_death.play();
            register_collisions(false);
        }
    }
    clear_collisions();
}
