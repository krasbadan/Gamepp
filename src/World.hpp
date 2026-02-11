#pragma once

#include "sequence.hpp"

#include "Economy.hpp"
#include "Player.hpp"
#include "Time.hpp"
#include "Utils.hpp"





struct StoryState {
    bool birch_juice_ending = false;
};

class World: public sf::Drawable {
	static const int road_width = 8;
    
    virtual void draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const override;

    Player player;
	int width, height;
	Tile** tiles;
    Sequence<MapObject*> map_objects;
    Sequence<NPC*> npcs;
    Sequence<Interactable*> interactables;
    Time time;
    Economy* player_economy;
    StoryState story;

public:
    Player& get_player();
    int get_width() const;
    int get_height() const;
    Tile* const* get_tiles() const;
    Sequence<MapObject*>& get_map_objects();
    Sequence<NPC*>& get_npcs();
    Sequence<Interactable*>& get_interactables();
    Time get_time() const;
    Economy* get_player_economy() const;
    StoryState& get_story();

    static sf::Vector2f get_iso_pos(sf::Vector2f logicPos);
    
	World(int _width, int _height);
    ~World();
	
	void update(float deltaTime);
    
    void spawn_building(Building* building);
    void spawn_map_resource(MapResource* map_resource);
    void spawn_npc(NPC* npc);
};
