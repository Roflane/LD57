#include "CardCollection.h"

namespace TierRules {
    int tier10Min = 1;
    int tier10Max = 10;

    int tier9Min = 50;
    int tier9Max = 69;

    int tier8Min = 41;
    int tier8Max = 59;

    int tier7Min = 150;
    int tier7Max = 169;

    int tier6Min = 180;
    int tier6Max = 201;

    int tier5Min = 179;
    int tier5Max = 190;

    int tier4Min = 400;
    int tier4Max = 421;

    int tier3Min = 320;
    int tier3Max = 341;

    int tier2Min = 900;
    int tier2Max = 921;

    int tier1Min = 999991;
    int tier1Max = 999999;
}


void CardCollection::wipe() {
    _cards.clear();
}

void CardCollection::generateRandomCards(ushort tier, Vector2 pos) {
    ushort desiredPower;
    ushort cardOffset = 150;
    

    for (ushort i = 0; i < 6; ++i) {
        Card card(Paths::card, pos, 1);
        if (tier == 10) {
            desiredPower = rand() % (TierRules::tier10Max - TierRules::tier10Min) + TierRules::tier10Min;
            card.setPower(desiredPower);
        }
        else if (tier == 9) {
            desiredPower = rand() % (TierRules::tier9Max - TierRules::tier9Min) + TierRules::tier9Min;
            card.setPower(desiredPower);
        }
        else if (tier == 8) {
            desiredPower = rand() % (TierRules::tier8Max - TierRules::tier8Min) + TierRules::tier8Min;
            card.setPower(desiredPower);
        }
        else if (tier == 7) {
            desiredPower = rand() % (TierRules::tier7Max - TierRules::tier7Min) + TierRules::tier7Min;
            card.setPower(desiredPower);
        }
        else if (tier == 6) {
            desiredPower = rand() % (TierRules::tier6Max - TierRules::tier6Min) + TierRules::tier6Min;
            card.setPower(desiredPower);
        }
        else if (tier == 5) {
            desiredPower = rand() % (TierRules::tier5Max - TierRules::tier5Min) + TierRules::tier5Min;
            card.setPower(desiredPower);
        }
        else if (tier == 4) {
            desiredPower = rand() % (TierRules::tier4Max - TierRules::tier4Min) + TierRules::tier4Min;
            card.setPower(desiredPower);
        }
        else if (tier == 3) {
            desiredPower = rand() % (TierRules::tier3Max - TierRules::tier3Min) + TierRules::tier3Min;
            card.setPower(desiredPower);
        }
        else if (tier == 2) {
            desiredPower = rand() % (TierRules::tier2Max - TierRules::tier2Min) + TierRules::tier2Min;
            card.setPower(desiredPower);
        }
        else if (tier == 1) {
            desiredPower = rand() % (TierRules::tier1Max - TierRules::tier1Min) + TierRules::tier1Min;
            card.setPower(desiredPower);
        }

        card.setPosX(pos.x + (cardOffset * i));
        addCard(card);
    }
}


void CardCollection::addCard(const Card &card) {
    _cards.push_back(card);
}

Card CardCollection::stealCard(ushort index) {
    if (index < _cards.size()) {
        Card card = _cards[index];  
        _cards.erase(_cards.begin() + index);  
        return card; 
    }
}

void CardCollection::draw(Color powerNumber, Color active) {
    for (auto &card : _cards) {
        card.draw(powerNumber, active);
    }
}

void CardCollection::update(Vector2 pos) {
    for (auto &card : _cards) {
        card.update(pos);
    }
}

void CardCollection::checkCursor(ushort mx, ushort my) {
    for (auto &card : _cards) {
        card.checkCursor(mx, my);
    }
}

bool CardCollection::select(ushort mx, ushort my) {
    for (auto &card : _cards) {
        if (card.select(mx, my)) return true;
    }
    return false;
}

bool CardCollection::dragCard(ushort mx, ushort my) {
    for (auto &card : _cards) {
        if (card.dragCard(mx, my)) return true;
    }
    return false;
}

bool CardCollection::attack(CardCollection &enemyCollection) {
    for (auto &card : _cards) {
        for (auto it = enemyCollection._cards.begin(); it != enemyCollection._cards.end(); ) {
            if (CheckCollisionRecs(card.getRect(), it->getRect())) {
                if (card.getPower() >= it->getPower()) {
                    card.attack(*it);
                    it = enemyCollection._cards.erase(it); 
                    return true;
                }
                else { ++it; }
            }
            else { ++it;  }
        }
    }
    return false;
}

bool CardCollection::rndAttack(CardCollection &enemyCollection) {
    if (enemyCollection.getSize() == 0) return false;

    for (auto &card : _cards) {
        if (enemyCollection.getSize() == 0) break; 

        ushort rndIndex = rand() % enemyCollection.getSize(); 
        auto it = enemyCollection._cards.begin() + rndIndex;  

        if (card.getPower() >= it->getPower()) {
            card.attack(*it);
            enemyCollection._cards.erase(it);
            return true;
        }
    }
    return false;
}