#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "core/game_character.hpp"
#include "actor_ref.hpp"

class GameScene;

class Player : public GameCharacter {
    public:
        Player(salmon::ActorRef actor, GameScene* scene);
        virtual Player* create(salmon::ActorRef actor, GameScene* scene) const override {return new Player(actor,scene);}

        void init() override;
        void update() override;

        static const char* type;
    private:
        static const bool good;

        std::string m_left_key = "Left";
        std::string m_right_key = "Right";
        std::string m_up_key = "Up";
        std::string m_down_key = "Down";

        std::string m_left_key_alt = "a";
        std::string m_right_key_alt = "d";
        std::string m_up_key_alt = "w";
        std::string m_down_key_alt = "s";

        float m_base_speed = 250;
        float m_current_speed = 250;
};


#endif // PLAYER_HPP_INCLUDED
