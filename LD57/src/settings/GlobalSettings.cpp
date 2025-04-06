#include "GlobalSettings.h"

ushort GameSettings::targetFps = 144;

Music GameSettings::deepspace;
Sound GameSettings::orbSound;

void GameSettings::InitSounds() {
    orbSound = LoadSound(Paths::orbSound);
    SetSoundVolume(orbSound, 0.3f);
}
void GameSettings::InitMusic() {
    deepspace = LoadMusicStream(Paths::deepspace);
}

float ScreenSettings::w;
float ScreenSettings::h;
float ScreenSettings::centerX;
float ScreenSettings::centerY;

void ScreenSettings::Init() {
    w = 1280; h = 720;
    centerX = w / 2; centerY = h / 2;
}
void ScreenSettings::Update() {
    w = GetScreenWidth(); h = GetScreenHeight();
    centerX = w / 2; centerY = h / 2;
}
