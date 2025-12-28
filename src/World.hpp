#pragma once

#include "Player.hpp"
#include "Utils.hpp"



class World: public sf::Drawable {
	static const int road_width = 8;
public:
	Player player;
	int width, height;
	Tile** tiles;
	
	World(int _width, int _height);
	
	void update(float deltaTime);

	static sf::Vector2f get_iso_pos(sf::Vector2f logicPos);

private:
	virtual void draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const override;
};
