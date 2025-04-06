#include "Orb.h"

Orb::Orb(OrbType type) : _type(type), _pos(), _spritePath(), _exists(true), _windowSpawned(false) {
    int initRedOrbEffect = 1;
    int initVioletOrbEffect = 3;
    _orbEffect = { initRedOrbEffect, initVioletOrbEffect };

    switch (type) {
        case ORB_RED:
            _spritePath = Paths::redOrb;
            _pos = OrbConfig::redOrbPos;
            break;
        case ORB_VIOLET:
            _spritePath = Paths::violetOrb;
            _pos = OrbConfig::violetOrbPos;
            break;
        case ORB_BLUE:
            _spritePath = Paths::blueOrb;
            _pos = OrbConfig::blueOrbPos;
            break;
    }

    _sprite = LoadTexture(_spritePath); 
    _sprite.width *= 2;
    _sprite.height *= 2;
}


void Orb::draw() {
    if (_exists) {
        DrawTextureV(_sprite, _pos, WHITE);
    }
}

void Orb::update() {
    OrbConfig::UpdateOrbPositions();
    
    switch (_type) {
        case ORB_RED:
            _pos = OrbConfig::redOrbPos;
            break;
        case ORB_VIOLET:
            _pos = OrbConfig::violetOrbPos;
            break;
        case ORB_BLUE:
            _pos = OrbConfig::blueOrbPos;
            break;
    }
}

bool Orb::destroy() {
    UnloadTexture(_sprite);
    
    _spritePath = nullptr;
    _type = OrbType::NONE;
    _exists = false;
    return true;
}

void Orb::pingRed(Card &card, ushort mx, ushort my) {
    if (_type == ORB_RED) {
        if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            card.setPower(card.getPower() + _orbEffect.redOrbEffect);
            destroy();
        }
    }
}
void Orb::pingViolet(Card &enemy, ushort mx, ushort my) {
    if (_type == ORB_VIOLET) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(GameSettings::orbSound);
            if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height)) {
                enemy.setPower(enemy.getPower() - _orbEffect.violetOrbEffect);
                destroy();
            }
        }
    }
}

void Orb::pingRed(CardCollection &cards, ushort mx, ushort my) {
    if (_type == ORB_RED) {
        if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height)
            && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                for (ushort i = 0; i < cards.getSize(); ++i) {
                    cards[i].setPower(cards[i].getPower() + _orbEffect.redOrbEffect);
                    if (destroy()) { PlaySound(GameSettings::orbSound); }
                }
        }
    }
}


void Orb::pingViolet(CardCollection &enemies, ushort mx, ushort my) {
    if (_type == ORB_VIOLET) {
        if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (ushort i = 0; i < enemies.getSize(); ++i) {
                enemies[i].setPower(enemies[i].getPower() - _orbEffect.violetOrbEffect);
                if (destroy()) { PlaySound(GameSettings::orbSound); }
            }
        }
    }
}

void Orb::pingBlue(CardCollection &me, CardCollection &enemies, ushort mx, ushort my) {
    if (_type == ORB_BLUE) {
        if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(GameSettings::orbSound);
            _windowSpawned = !_windowSpawned;
        }

        if (_windowSpawned) {
            // Window visual
            ClearBackground(LIGHTGRAY);
            DrawRectangle(0, 0, ScreenSettings::w, ScreenSettings::h, Fade(GRAY, 0.8f));

            float windowWidth = ScreenSettings::w / 2;
            float windowHeight = ScreenSettings::h / 2;
            float windowX = ScreenSettings::centerX - windowWidth / 2;
            float windowY = ScreenSettings::centerY - windowHeight / 2;

            DrawRectangle(windowX, windowY, windowWidth, windowHeight, Fade(BLACK, 0.5));

            // Popup text
            ushort textSize = 20;
            const char* popUpText = "Steal one of the following cards ";

            Vector2 textPos = { windowX + (windowWidth - MeasureText(popUpText, textSize)) / 2,
                                windowY + 10 };
            DrawText(popUpText, textPos.x, textPos.y, textSize, RED);

            // Pos adjustment
            float cardWidth = windowWidth / 8; 
            float cardHeight = cardWidth; 
            float startX = windowX + 20; 
            float offsetX = startX; 

            float offsetPowerNumber = 10;
            for (ushort i = 0; i < enemies.getSize(); ++i) {
                Card &enemyCard = enemies[i];

                float scale = cardWidth / enemyCard.getW(); 
                Vector2 cardPos = { offsetX, windowY + 50 };  
                DrawTextureEx(enemyCard.getSprite(), cardPos, 0, scale, WHITE);
                DrawText(TextFormat("%i", enemyCard.getPower()), cardPos.x + (offsetPowerNumber / 2), cardPos.y + (offsetPowerNumber / 2), offsetPowerNumber * 2, RED);

                if (isCursorOnImage(mx, my, cardPos.x, cardPos.y, cardWidth, cardHeight) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Card stolenCard = enemies.stealCard(i);
                    me.addCard(stolenCard);
                    destroy();
                    _windowSpawned = false;
                    break;
                }
                offsetX += cardWidth + 10;
            }
        }
    }
}

void Orb::upgradeOrb(ushort currentTier) {
    switch (currentTier) {
        case 10:
            if (_type == ORB_RED) _orbEffect.redOrbEffect = 19;
            if (_type == ORB_VIOLET) _orbEffect.violetOrbEffect = 3;
            break;
        case 9 || 7 || 5 || 4 || 2 || 1:
            if (_type == ORB_RED) _orbEffect.redOrbEffect = 9;
            if (_type == ORB_VIOLET) _orbEffect.violetOrbEffect = 5;
            break;
    }
}