#ifndef GAME_CHARACTER_HPP_INCLUDED
#define GAME_CHARACTER_HPP_INCLUDED

#include <map>
#include <string>

#include "actor_ref.hpp"

class GameScene;

class GameCharacter : public salmon::ActorRef {
    public:
        GameCharacter(salmon::ActorRef actor, GameScene* scene);
        static GameCharacter* parse_character(salmon::ActorRef actor, GameScene* scene);

        virtual void init() = 0;
        virtual void update() = 0;
        virtual GameCharacter* create(salmon::ActorRef actor, GameScene* scene) const = 0;

        bool put(bool& var, std::string name);
        bool put(int& var, std::string name);
        bool put(float& var, std::string name);
        bool put(std::string& var, std::string name);

    protected:
        GameScene* m_scene;

        template <class T>
        static bool register_class(std::string type);
    private:
        static std::map<std::string, GameCharacter*>& get_dict();
};

template <class T>
bool GameCharacter::register_class(std::string type) {
    ActorRef dummy(nullptr);
    GameCharacter* character = new T(dummy,nullptr);
    get_dict()[type] = character;
    return true;
}

#endif // GAME_CHARACTER_HPP_INCLUDED
