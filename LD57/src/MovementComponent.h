#pragma once
#include <cmath>
#include "raylib.h"

#include "../base/misc.h"
#include "../base/typedefs.h"

#include "settings/GlobalSettings.h"

class MovementComponent {
private:
    // Fields
    ushort _moveSpeed;
public:
    MovementComponent(ushort moveSpeed) : _moveSpeed(moveSpeed) {}

    // Methods
    void move(float& posX, float& posY, float& dt);
};