#ifndef ARROW_HPP_INCLUDED
#define ARROW_HPP_INCLUDED

#include "core/game_character.hpp"

class GameScene;

class Arrow : public GameCharacter {
    public:
        Arrow(salmon::ActorRef actor, GameScene* scene);
        virtual Arrow* create(salmon::ActorRef actor, GameScene* scene) const override {return new Arrow(actor,scene);}

        void init() override;
        void update() override;

        bool ready() {return m_ready;}
        void apply_force(float& x, float& y);

        static const char* type;
    protected:
        // Add members here
        bool m_first = true;
        float m_cooldown = 0.2;
        float m_base_force = 1000;

        float m_x_base = 0;
        float m_y_base = 0;

        float m_length = 0;
        float m_rotation = 0;

        float m_strength = 0;
        bool m_ready = false;

    private:
        static const bool good;
};


#endif // ARROW_HPP_INCLUDED
