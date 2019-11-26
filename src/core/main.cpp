#include "core/scene_manager.hpp"
int main() {
    SceneManager game(960, 768,false);
    game.load_scene("scenes/menu.tmx");
    while(game.run()) {}
    return 0;
}
