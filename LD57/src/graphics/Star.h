#pragma once
#include <raylib.h>
#include <stdlib.h>
#include "../../base/typedefs.h"

class Star {
private:
    Texture2D _sprite;
    Vector2 *_stars;
    ushort _starsCount;
public:
    Star(const char *spritePath, ushort starsCount);
    ~Star();

    void draw();
    void fall(float fallSpeed);
    void update();
};