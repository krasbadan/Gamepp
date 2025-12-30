#pragma once

#include "MapObject.hpp"
#include "Utils.hpp"
#include "TextureManager.hpp"
#include "AnimationHandler.hpp"

class Campfire : public MapObject {
    AnimationHandler animation_handler;

public:
    Campfire(World* _worldptr, sf::Vector2i pos, float ingame_height = 2.f);
};