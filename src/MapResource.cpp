#include "MapResource.hpp"

#include "dialogue.hpp"
#include "str_format.hpp"

#include "TextureManager.hpp"
#include "World.hpp"



MapResource::MapResource(
    World* _worldptr, sf::Vector2i pos, const sf::Texture& texture,
    const char* _name, int _amount, float ingame_height
):
    MapObject(_worldptr, pos, texture, ingame_height), name(_name), amount(_amount)
{}



Dialogue* MapResource::interact() {
    if (amount > 0) {
        return new Dialogue(
            this,
            wstr_format(wstr_format(L"Собрать {}? Доступно {}.", name), amount),
            {
                DialogueOption(L"Собрать всё", [this]() -> Dialogue* {
                    worldptr->player_economy->resources[name] += amount;
                    amount = 0;
                    return nullptr;
                }),
                DialogueOption(L"Отмена", []() -> Dialogue* {
                    return nullptr;
                }),
            }
        );
    } else {
        return new Dialogue(
            this,
            L"Все ресурсы добыты.",
            {}
        );
    }
}

sf::Vector2f MapResource::get_interact_pos() const {
    return sf::Vector2f(pos) + sf::Vector2f(0.5, 0.5);
}
float MapResource::get_interact_distance() const {
    return 1.5f;
}



Dialogue* BirchNPC::interact() {
    if (amount > 0) {
        return new Dialogue(
            this,
            wstr_format(L"Хочешь берёзового сока? Есть {} литров.", amount),
            {
                DialogueOption(L"Спасибо, дорогая берёзка, пока не хочу...", []() -> Dialogue* {
                    return nullptr;
                }),
                DialogueOption(L"Можно чуть-чуть попробовать? (1 литр)", [this]() -> Dialogue* {
                    worldptr->player_economy->resources["birch_juice"] += 1;
                    amount -= 1;
                    return next_dial();
                }),
                DialogueOption(L"Я возьму всё!", [this]() -> Dialogue* {
                    worldptr->player_economy->resources["birch_juice"] += amount;
                    amount = 0;
                    return nullptr;
                }),
            }
        );
    } else {
        return new Dialogue(
            this,
            L"Берёзового сока сейчас нет. Приходи позже!",
            {}
        );
    }
}

Dialogue* BirchNPC::next_dial() {
    if (amount > 0) {
        return new Dialogue(
            this,
            wstr_format(L"Продолжай пить! Всё ещё остаётся {} литров.", amount),
            {
                DialogueOption(L"Спасибо, дорогая берёзка, больше не хочу...", []() -> Dialogue* {
                    return nullptr;
                }),
                DialogueOption(L"Можно ещё чуть-чуть? (1 литр)", [this]() -> Dialogue* {
                    worldptr->player_economy->resources["birch_juice"] += 1;
                    amount -= 1;
                    return next_dial();
                }),
                DialogueOption(L"Я возьму всё!", [this]() -> Dialogue* {
                    worldptr->player_economy->resources["birch_juice"] += amount;
                    amount = 0;
                    return nullptr;
                }),
            }
        );
    } else {
        return new Dialogue(
            this,
            L"Берёзового сока сейчас нет. Приходи позже!",
            {}
        );
    }
}