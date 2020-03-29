#ifndef FROG_HPP_INCLUDED
#define FROG_HPP_INCLUDED

#include "core/game_character.hpp"
#include "characters/arrow.hpp"

#include "sound_ref.hpp"

class GameScene;

class Frog : public GameCharacter {
    public:
        Frog(salmon::ActorRef actor, GameScene* scene);
        virtual Frog* create(salmon::ActorRef actor, GameScene* scene) const override {return new Frog(actor,scene);}

        void init() override;
        void update() override;
        std::string get_type() const override {return type;}

        bool move(float x, float y) {return move_relative(x,y,salmon::Collidees::tile,{salmon::DEFAULT_HITBOX},{salmon::DEFAULT_HITBOX},false);}
        bool on_ground(salmon::Direction dir = salmon::Direction::down) {return GameCharacter::on_ground(salmon::Collidees::tile,salmon::DEFAULT_HITBOX,{salmon::DEFAULT_HITBOX},dir);}

        static const char* type;
    protected:
        // Add members here
        bool m_first = true;
        float m_x_speed = 0;
        float m_y_speed = 0;

        float m_gravity = 2000;
        Arrow* m_arrow = nullptr;

        std::string m_jump_sound;
        std::string m_death_sound;

        bool m_dead = false;

        salmon::SoundRef m_jump;
        salmon::SoundRef m_death;

    private:
        static const bool good;
};


#endif // FROG_HPP_INCLUDED
