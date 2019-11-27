#include "characters/arrow.hpp"

#include <cmath>

#include "core/game_scene.hpp"
#include "core/scene_manager.hpp"

#define PI 3.14159265

const char* Arrow::type = "Arrow";
const bool Arrow::good = GameCharacter::register_class<Arrow>(Arrow::type);

Arrow::Arrow(salmon::ActorRef actor, GameScene* scene) : GameCharacter(actor, scene) {}

void Arrow::init() {
    // Setup member vars here | example: put(m_speed, "m_speed");
    put(m_base_force, "base_force");
    set_hidden(true);
    //set_static_mode(true);
}

void Arrow::update() {
    // Add character logic here
    if(m_first) {
        if(m_cooldown < 0) {m_first = false;}
        else {
            m_cooldown -= m_scene->get_delta_time();
            return;
        }
    }

    constexpr float min_strength = 0.05;
    const salmon::InputCacheRef input = m_scene->get_input_cache();
    salmon::MouseState mouse = input.get_mouse_state();
    if(mouse.left.pressed) {
        m_ready = false;
        m_x_base = mouse.x_pos;
        m_y_base = mouse.y_pos;
    }
    else if(mouse.left.down) {
        float x_delta = mouse.x_pos - m_x_base;
        float y_delta = mouse.y_pos - m_y_base;
        m_length = std::sqrt(x_delta * x_delta + y_delta * y_delta);
        if(m_length > 256) {m_length = 256;}
        m_strength = m_length / 256;
        if(m_strength > min_strength) {
            set_hidden(false);
            scale(m_strength, 1);
            int frame = m_strength * get_anim_frame_count() - 1;
            set_animation(salmon::AnimationType::current, salmon::Direction::current, frame);
            m_rotation = std::atan2(x_delta,y_delta);
            set_angle(-(m_rotation  * 180 / PI) + 90);
            float x_middle = (mouse.x_pos + m_x_base) * 0.5;
            float y_middle = (mouse.y_pos + m_y_base) * 0.5;
            salmon::CameraRef cam = m_scene->get_camera();
            move(cam.get_x() + x_middle - get_w() * 0.5, cam.get_y() + y_middle + get_h() * 0.5, true);
        }
        else {
            set_hidden(true);
        }
    }
    else if(mouse.left.released) {
        if(m_strength > min_strength) {m_ready = true;}
    }
}

void Arrow::apply_force(float& x, float& y) {
    m_ready = false;
    x = std::sin(m_rotation) * m_strength * m_base_force;
    y = std::cos(m_rotation) * m_strength * m_base_force;
    set_hidden(true);
}
