#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.hpp"
#include "Presenter.hpp"
#include "World.hpp"



int main() {
    World world(500, 500);
    world.player.presenter.main();
    
    return 0;
}
