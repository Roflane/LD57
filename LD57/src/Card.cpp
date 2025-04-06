#include "Card.h"

Card::Card(const char* spritePath, Vector2 pos, int cardPower) {
    _spritePath = spritePath;
    _sprite = LoadTexture(spritePath);
    _cardState = { false, false, false }; 
    _power = cardPower;
    _pos = pos;
    _exists = true;
}


//Card::Card(const std::vector<Card>& cardsCollection) : _spritePath(0), _sprite() {
//    _cards = cardsCollection;
//
//    for (size_t i = 0; i < _cards.size(); ++i) {
//        _sprite = LoadTexture(_cards[i].getSpritePath());
//    }
//
//    _cardState = { false, false, false };
//    _pos = { .x = ScreenSettings::centerX / 2, .y = ScreenSettings::centerY + (ScreenSettings::centerY / 2) };
//}

void Card::draw(Color powerNumber, Color active) {
    float fontSize = 30;
    float textPosOffset = 10;
    Vector2 textPos = { _pos.x + textPosOffset, _pos.y + textPosOffset };

    if (_exists) {
        if (_cardState.isActive) { DrawTextureV(_sprite, Vector2{ _pos.x, _pos.y }, active); }
        else { DrawTextureV(_sprite, Vector2{ _pos.x, _pos.y }, WHITE); }

        DrawText(TextFormat("%i", _power), textPos.x, textPos.y, fontSize, powerNumber);
    }
}

void Card::update(Vector2 pos) {
    if (IsWindowResized()) { _pos = pos; }
}

void Card::checkCursor(ushort mx, ushort my) {
    static float originalWidth = _sprite.width;
    static float originalHeight = _sprite.height;

    if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height)) {
        if (!_cardState.isActive) {
            _sprite.width *= 1.2f;
            _sprite.height *= 1.2f;
            _cardState.isActive = true;
        }
    }
    else {
        if (_cardState.isActive) {
            _sprite.width = originalWidth;  
            _sprite.height = originalHeight;
            _cardState.isActive = false;
        }
    }
}

bool Card::select(ushort mx, ushort my) {
    if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        _cardState.isSelected = !_cardState.isSelected;
        std::cout << "card has been clicked\n";
        return true;
    }
    return false;
}

bool Card::dragCard(ushort mx, ushort my) {
    if (isCursorOnImage(mx, my, _pos.x, _pos.y, _sprite.width, _sprite.height) &&
        IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (!get_isHold()) {
            setPosX(mx - _sprite.width / 2);
            setPosY(my - _sprite.height / 2);
            set_isHold(true);
        }
        else if (get_isHold()) {
            setPosX(mx - _sprite.width / 2);
            setPosY(my - _sprite.height / 2);
        }
        return true;
    }
    return false;
}

void Card::destroy(Card &card) {
    UnloadTexture(card._sprite);

    card._spritePath = nullptr;
    card._sprite = {};
    card._cardState = { false, false, false };
    card._power = 0;
    card._pos = { 0, 0 };
    card._exists = false;
}

bool Card::attack(Card &enemy) {
    Rectangle myCard = {_pos.x, _pos.y, _sprite.width, _sprite.height};
    Rectangle enemyCard = {enemy.getPos().x, enemy.getPos().y, enemy.getW(), enemy.getH()};

    if (CheckCollisionRecs(myCard, enemyCard)) {
        if (_power >= enemy.getPower()) {
            destroy(enemy);
            return true;
        }
    }
    return false;
}
