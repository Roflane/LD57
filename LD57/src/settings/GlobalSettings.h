#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct GameSettings {
    static ushort targetFps;
    static Sound orbSound;
    static Music deepspace;

    static void InitMusic();
    static void InitSounds();
};

struct ScreenSettings {
    static float w;
    static float h;
    static float centerX;
    static float centerY;

    static void Init();
    static void Update();
};
