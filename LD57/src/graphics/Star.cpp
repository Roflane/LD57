#include "Star.h"

Star::Star(const char *spritePath, ushort starsCount) :
    _sprite(LoadTexture(spritePath)), _starsCount(starsCount)
{
    _stars = new Vector2[starsCount];

    for (ushort i = 0; i < starsCount; i++) {
        _stars[i] = { (float)(rand() % GetScreenWidth()),
                      (float)(rand() % GetScreenHeight()) };
    }
}

void Star::draw() {
    for (ushort i = 0; i < _starsCount; i++) {
        DrawTextureV(_sprite, _stars[i], WHITE);
    }
}

void Star::fall(float fallSpeed) {
    for (ushort i = 0; i < _starsCount; i++) {
        _stars[i].y += fallSpeed;

        if (_stars[i].y > GetScreenHeight()) {
            _stars[i].x = (float)(rand() % GetScreenWidth());
            _stars[i].y = 0;
        }
    }
}

void Star::update() {
    if (IsWindowResized()) {
        for (ushort i = 0; i < _starsCount; i++) {
            _stars[i] = { (float)(rand() % GetScreenWidth()),
                          (float)(rand() % GetScreenHeight()) };


        }
    }
}

Star::~Star() {
    delete[] _stars;
}