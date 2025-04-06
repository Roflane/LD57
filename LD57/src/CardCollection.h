#pragma once
#include <raylib.h>
#include <vector>
#include "../base/typedefs.h"
#include "../base/misc.h"
#include "../base/dirs.h"
#include "Card.h"


class CardCollection {
private:
    // Fields
    std::vector<Card> _cards;
public:
    // Properties
    ushort getSize() const { return _cards.size(); }
     
    // Operator overloads
    Card& operator[](size_t index) {
        return _cards[index];
    }

    // Methods
    void wipe();
    void generateRandomCards(ushort tier, Vector2 pos);

    void draw(Color powerNumber, Color active);
    void update(Vector2 pos);

    Card stealCard(ushort index);

    void addCard(const Card &card);
    void checkCursor(ushort mx, ushort my);
    bool select(ushort mx, ushort my);
    bool dragCard(ushort mx, ushort my);
    bool attack(CardCollection &enemyCollection);
    bool rndAttack(CardCollection &foeCollection);
};
