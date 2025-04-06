#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
#include "../base/typedefs.h"
#include "../base/misc.h"
#include "../base/dirs.h"
#include "Card.h"
#include "CardCollection.h"

class Card;  
class CardCollection;

namespace OrbConfig {
    static float offset = 50;
    static float commonOrbOffset = offset * 2;
    static float blueOrbOffset = commonOrbOffset + offset;

    static Vector2 redOrbPos = {
        .x = ScreenSettings::w - offset,
        .y = ScreenSettings::centerY - (ScreenSettings::centerY / 2)
    };
    static Vector2 violetOrbPos = { .x = redOrbPos.x, .y = redOrbPos.y + offset };
    static Vector2 blueOrbPos =   { .x = redOrbPos.x, .y = violetOrbPos.y + offset };


    static void UpdateOrbPositions() {
        redOrbPos = {
            .x = ScreenSettings::w - offset,
            .y = ScreenSettings::centerY - (ScreenSettings::centerY / 2)
        };
        violetOrbPos = { .x = redOrbPos.x, .y =  redOrbPos.y + commonOrbOffset };
        blueOrbPos =   { .x = redOrbPos.x, .y =  violetOrbPos.y + commonOrbOffset };
    }
}

enum OrbType {
    NONE = 0,
    ORB_RED,
    ORB_VIOLET,
    ORB_BLUE
};

struct OrbEffect {
    int redOrbEffect;
    int violetOrbEffect;
};

class Orb {
private:
    const char* _spritePath;
    Texture2D _sprite;
    Vector2 _pos;
    OrbType _type;
    OrbEffect _orbEffect;
    bool _exists;
    bool _windowSpawned; // blue orb moment
public:
    Orb(OrbType type);

    // Properties
    const char* getSpritePath() const { return _spritePath; }

    Vector2 getPos() const { return _pos; }
    void setPosX(float posX) { _pos.x = posX; }
    void setPosY(float posY) { _pos.y = posY; }

    float getW() const { return _sprite.width; }
    float getH() const { return _sprite.height; }

    bool getWindowsSpawned() const { return _windowSpawned; }

    OrbType getOrbType() const { return _type; }

    // Methods
    void draw();
    void update();
    bool destroy();
    void pingRed(Card &card, ushort mx, ushort my);
    void pingRed(CardCollection &cards, ushort mx, ushort my);
    void pingViolet(Card &enemy, ushort mx, ushort my);
    void pingViolet(CardCollection &enemies, ushort mx, ushort my);
    void pingBlue(CardCollection &me, CardCollection &enemies, ushort mx, ushort my);
    void upgradeOrb(ushort currentTier);
};