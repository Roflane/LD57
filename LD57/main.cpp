#include "includes.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    ScreenSettings::Init();
    SetTargetFPS(GameSettings::targetFps);

    InitWindow(ScreenSettings::w, ScreenSettings::h, "Abysmal fate");
    InitAudioDevice();
    GameSettings::InitMusic();
    GameSettings::InitSounds();
    SetWindowSize(ScreenSettings::w - 10, ScreenSettings::h - 10);

    HideCursor();

    MainLoop();
}