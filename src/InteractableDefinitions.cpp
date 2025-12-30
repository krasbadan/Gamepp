#include "dialogue.hpp"
#include "str_format.hpp"

#include "Map.hpp"
#include "MapResource.hpp"
#include "NPC.hpp"
#include "World.hpp"



Dialogue* BirchTree::interact() {
    if (amount > 0) {
        return new Dialogue(
            this,
            wstr_format(L"Хочешь берёзового сока? Есть {} литров.", amount),
            3,
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
            0,
            {}
        );
    }
}

Dialogue* BirchTree::next_dial() {
    if (amount > 0) {
        return new Dialogue(
            this,
            wstr_format(L"Продолжай пить! Всё ещё остаётся {} литров.", amount),
            3,
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
            0,
            {}
        );
    }
}