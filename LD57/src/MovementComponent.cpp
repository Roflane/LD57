#include "MovementComponent.h"

void MovementComponent::move(float& posX, float& posY, float& dt) {
    float moveX = 0, moveY = 0;

    if (IsKeyDown(KEY_W)) { moveY -= 1.0f; }
    if (IsKeyDown(KEY_S)) { moveY += 1.0f; }
    if (IsKeyDown(KEY_A)) { moveX -= 1.0f; }
    if (IsKeyDown(KEY_D)) { moveX += 1.0f; }

    float normalizedV = NormalizeVector2(moveX, moveY);
    if (normalizedV > 0) {
        moveX /= normalizedV;
        moveY /= normalizedV;
    }
    
    posX += moveX * _moveSpeed * dt;
    posY += moveY * _moveSpeed * dt;
}