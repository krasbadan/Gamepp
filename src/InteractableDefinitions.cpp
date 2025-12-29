#include "dialogue.hpp"

#include <format>

#include "MapResource.hpp"
#include "NPC.hpp"



Dialogue* BirchTree::interact() {
    if (amount > 0) {
        return new Dialogue(
            std::format(L"Хочешь берёзового сока? Есть {} литров.", amount).data(),
            3,
            {
                DialogueOption(L"Спасибо, дорогая берёзка, пока не хочу...", []() -> Dialogue* {
                    return nullptr;
                }),
                DialogueOption(L"Можно чуть-чуть попробовать? (1 литр)", [this]() -> Dialogue* {
                    amount -= 1;
                    return next_dial();
                }),
                DialogueOption(L"Я возьму всё!", [this]() -> Dialogue* {
                    amount = 0;
                    return nullptr;
                }),
            }
        );
    } else {
        return new Dialogue(
            L"Берёзового сока сейчас нет. Приходи позже!",
            0,
            {}
        );
    }
}

Dialogue* BirchTree::next_dial() {
    if (amount > 0) {
        return new Dialogue(
            std::format(L"Продолжай пить! Всё ещё остаётся {} литров.", amount).data(),
            3,
            {
                DialogueOption(L"Спасибо, дорогая берёзка, больше не хочу...", []() -> Dialogue* {
                    return nullptr;
                }),
                DialogueOption(L"Можно ещё чуть-чуть? (1 литр)", [this]() -> Dialogue* {
                    amount -= 1;
                    return next_dial();
                }),
                DialogueOption(L"Я возьму всё!", [this]() -> Dialogue* {
                    amount = 0;
                    return nullptr;
                }),
            }
        );
    } else {
        return new Dialogue(
            L"Берёзового сока сейчас нет. Приходи позже!",
            0,
            {}
        );
    }
}