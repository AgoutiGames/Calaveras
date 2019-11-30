#include "core/scene_manager.hpp"
int main() {
    SceneManager game("scenes/menu.tmx");
    while(game.run()) {}
    return 0;
}
