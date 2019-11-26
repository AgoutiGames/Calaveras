#ifndef GAME_SCENE_HPP_INCLUDED
#define GAME_SCENE_HPP_INCLUDED

#include <map>
#include <vector>
#include <memory>
#include <string>

#include "map_ref.hpp"
#include "audio_manager_ref.hpp"
#include "input_cache_ref.hpp"
#include "core/game_character.hpp"

class SceneManager;

class GameScene : public salmon::MapRef {
    public:
        GameScene(salmon::MapRef map, SceneManager* scene_manager);
        static GameScene* parse_scene(salmon::MapRef map, SceneManager* scene_manager);

        virtual void init();
        virtual void update();
        virtual GameScene* create(salmon::MapRef map, SceneManager* scene_manager) const = 0;

        bool put(bool& var, std::string name);
        bool put(int& var, std::string name);
        bool put(float& var, std::string name);
        bool put(std::string& var, std::string name);

        GameCharacter* get_character_by_name(std::string name);
        GameCharacter* get_character_by_id(unsigned id);
        GameCharacter* get_character_by_template_type(std::string template_type);
        GameCharacter* get_character_by_attribute(std::string name, bool attribute);
        GameCharacter* get_character_by_attribute(std::string name, int attribute);
        GameCharacter* get_character_by_attribute(std::string name, float attribute);
        GameCharacter* get_character_by_attribute(std::string name, const char* attribute);
        GameCharacter* get_character_by_attribute(std::string name, std::string attribute);
        template <class T>
        T* get_character();

        std::vector<GameCharacter*> get_characters_by_name(std::string name);
        std::vector<GameCharacter*> get_characters_by_layer(std::string name);
        std::vector<GameCharacter*> get_characters_by_template_type(std::string template_type);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, bool attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, int attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, float attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, const char* attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, std::string attribute);
        template <class T>
        std::vector<T*> get_characters();

        std::vector<GameCharacter*> filter_characters_by_name(std::vector<GameCharacter*> characters, std::string name);
        std::vector<GameCharacter*> filter_characters_by_layer(std::vector<GameCharacter*> characters, std::string name);
        std::vector<GameCharacter*> filter_characters_by_template_type(std::vector<GameCharacter*> characters, std::string template_type);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, bool attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, int attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, float attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, const char* attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, std::string attribute);
        template <class T>
        std::vector<T*> filter_characters(std::vector<GameCharacter*>);

        std::vector<GameCharacter*> get_characters();

        // Take an already generated and added actor
        GameCharacter* add_character(salmon::ActorRef actor);

        // Add character by its template name
        GameCharacter* add_character(std::string actor_template_name, std::string layer_name, std::string actor_name = "GENERATED");
        GameCharacter* add_character(const char* actor_template_name, std::string layer_name, std::string actor_name = "GENERATED")
        {return add_character(std::string(actor_template_name),layer_name,actor_name);}

        // This duplicates the actor inside the character, the new characters mebers are reset and init is called
        GameCharacter* add_character(GameCharacter* character, std::string layer_name, std::string actor_name = "GENERATED");
        // This also duplicates the members of the character, but init is called again nevertheless
        template <class T>
        GameCharacter* add_character(T* character, std::string layer_name, std::string actor_name = "GENERATED");

        void remove_character(GameCharacter* game_character);

        SceneManager& get_scene_manager() {return *m_scene_manager;}
        salmon::InputCacheRef get_input_cache();
        salmon::AudioManagerRef get_audio_manager();

    protected:
        SceneManager* m_scene_manager;
        std::vector<std::unique_ptr<GameCharacter>> m_characters;

        std::vector<GameCharacter*> m_kill_characters;
        void trigger_kill();
        std::vector<GameCharacter*> m_add_characters;
        void trigger_add();

        template <class T>
        static bool register_class(std::string type);
    private:
        bool remove_character_internal(GameCharacter* game_character);
        static std::map<std::string, GameScene*>& get_dict();
};

template <class T>
std::vector<T*> GameScene::filter_characters(std::vector<GameCharacter*> characters) {
    std::vector<T*> new_characters;
    for(auto c : characters) {new_characters.push_back(static_cast<T*>(c));}
    return new_characters;
}

template <class T>
std::vector<T*> GameScene::get_characters() {
    std::vector<GameCharacter*> characters = get_characters_by_attribute("type",T::type);
    std::vector<T*> new_characters;
    for(auto c : characters) {new_characters.push_back(static_cast<T*>(c));}
    return new_characters;
}

template <class T>
T* GameScene::get_character() {
    std::vector<T*> characters = get_characters<T>();
    if(characters.empty()) {return nullptr;}
    else {return characters.front();}
}

template <class T>
bool GameScene::register_class(std::string type) {
    MapRef dummy(nullptr);
    GameScene* scene = new T(dummy,nullptr);
    get_dict()[type] = scene;
    return true;
}

template <class T>
GameCharacter* GameScene::add_character(T* character, std::string layer_name, std::string actor_name) {
    // Duplicate the derived character type | Both reference the same actor
    T* new_char = new T(*character);
    // Duplicate the actor
    salmon::ActorRef actor = add_actor(*static_cast<salmon::ActorRef*>(character),layer_name,actor_name);
    if(!actor.good()) {return nullptr;}
    else {
        // Assign the actor to the new character
        *static_cast<salmon::ActorRef*>(new_char) = actor;
        m_add_characters.push_back(new_char);
        return m_add_characters.back();
    }
}


#endif // GAME_SCENE_HPP_INCLUDED
