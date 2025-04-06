#include "Game.h"
#include "OrbGroup.h"

namespace Config {  
    // Visual
    ushort starsCount = 100;
    float starSpeed = 1.f;
    float horizontalSpeed = 100.f;

    // Card
    ushort cardH = 50;

    float cardsOffset = 120;
    float cardInitOffset = 250;

}

static void AnimatedCursor(Vector2 pos, float dt) {
    static Texture2D cursor1 = LoadTexture(Paths::cursor[0]);
    static Texture2D cursor2 = LoadTexture(Paths::cursor[1]);
    static Texture2D cursor3 = LoadTexture(Paths::cursor[2]);
    static Texture2D cursor4 = LoadTexture(Paths::cursor[3]);

    static Texture2D cursors[4] = { cursor1, cursor2, cursor3, cursor4 };

    static ushort cursorIndex = 0;
    cursorIndex = (cursorIndex + 1) % 4;

    DrawTexture(cursors[cursorIndex], pos.x, pos.y, WHITE);
}


static bool game_paused = false;
static void UpdateMusic() {
    if (game_paused) { PauseMusicStream(GameSettings::deepspace);  }
    else {  ResumeMusicStream(GameSettings::deepspace); }
}
static void GameState() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        game_paused= !game_paused;
    }
}
static void DrawPauseState() {
    ClearBackground(LIGHTGRAY);
    DrawRectangle(0, 0, ScreenSettings::w, ScreenSettings::h, Fade(GRAY, 0.5f));

    ushort textSize = 30;
    DrawText("Paused", ScreenSettings::centerX - textSize, ScreenSettings::centerY - textSize, textSize, RED);
}
static void DrawFps() {
    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 30, GREEN);
}

static void RunStars(Star &stars, ushort currentTier) {
    stars.draw();

    switch (currentTier) {
        case 10:
            stars.fall(Config::horizontalSpeed);
            break;
        case 9:
            stars.fall(Config::starSpeed * 4);
            break;
        case 8:
            stars.fall(Config::horizontalSpeed);
            break;
        case 7:
            stars.fall(Config::starSpeed * 8);
            break;
        case 6:
            stars.fall(Config::starSpeed * 9);
            break;
        case 5:
            stars.fall(Config::horizontalSpeed);
            break;
        case 4:
            stars.fall(Config::starSpeed * 18);
            break;
        case 3:
            stars.fall(Config::starSpeed * 15);
            break;
        case 2:
            stars.fall(Config::starSpeed * 30);
            break;
        case 1:
            stars.fall(Config::starSpeed * 31);
            break;
    }

    stars.update();
}


//void MyCards(Card &card, Card &enemy, ushort mx, ushort my) {
//    Vector2 myPos = {
//        .x = ScreenSettings::centerX - card.getW() / 2,  
//        .y = ScreenSettings::h - card.getH() - Config::cardsOffset
//    };
//
//    Color powerNumber = GREEN;
//    Color active = TEAL;
//
//    if (&card && &enemy) {
//        card.attack(enemy);
//        card.checkCursor(mx, my);
//        card.draw(powerNumber, active);
//        if (!card.dragCard(mx, my)) {
//            card.update(myPos);
//        }
//    }
//}
//void EnemyCards(Card &card) {
//    Vector2 enemyPos = {
//        .x = ScreenSettings::centerX - card.getW() / 2, 
//        .y = Config::cardsOffset
//    };
//
//    Color powerNumber = RED;
//    Color white = RED;
//
//    if (&card) {
//        card.draw(powerNumber, white);
//        card.update(enemyPos);
//    }
//}
    
namespace BattleManager {
    XStr<ushort> entityTurn = "Player";

    static ushort maxTier = 10;
    static ushort currentTier = 10;
    static bool battleGenerated[10] = { false, false, false, false, false, false, false, false, false, false };
    static bool battleDone[10] = { false, false, false, false, false, false, false, false, false, false };

    ushort winCount = 0;
    int defeatedPowerSum = 0;
}


void OrbLigic(OrbGroup &orbs, CardCollection &me, CardCollection &enemies, ushort mx, ushort my) {
    for (ushort i = 0; i < 3; ++i) {
        if (orbs[i].getOrbType() == ORB_RED) {
            orbs[i].upgradeOrb(BattleManager::currentTier);
            orbs[i].pingRed(me, mx, my);
            orbs[i].draw();
            orbs[i].update();
        } 
        else if (orbs[i].getOrbType() == ORB_VIOLET) {
            orbs[i].upgradeOrb(BattleManager::currentTier);
            orbs[i].pingViolet(enemies, mx, my);
            orbs[i].draw();
            orbs[i].update();
        }
        else if (orbs[i].getOrbType() == ORB_BLUE) {
            orbs[i].upgradeOrb(BattleManager::currentTier);
            orbs[i].pingBlue(me, enemies, mx, my);
            orbs[i].draw();
            orbs[i].update();
        }
    }
}


void UpdatePos(Vector2 &myPos, Vector2 &enemyPos) {
    myPos = { .x = GetScreenWidth() * 0.25f,  .y = GetScreenHeight() - Config::cardInitOffset };
    enemyPos = { .x = GetScreenWidth() * 0.25f,  .y = 50 };
}

Vector2 myPos = { .x = GetScreenWidth() * 0.25f,  .y = GetScreenHeight() - Config::cardInitOffset };
Vector2 enemyPos = { .x = GetScreenWidth() * 0.25f,  .y = 50 };

void HandleCardPos(CardCollection &myCards, CardCollection &enemyCards) {
    float cardOffset = 150;
    
    UpdatePos(myPos, enemyPos);
    for (ushort i = 0; i < myCards.getSize(); ++i) {
        Vector2 newPos = { myPos.x + (cardOffset * i), myPos.y };
        myCards[i].update(newPos);
    }
    for (ushort i = 0; i < enemyCards.getSize(); ++i) {
        Vector2 newPos = { enemyPos.x + (cardOffset * i), enemyPos.y };
        enemyCards[i].update(newPos);
    }

    myCards.draw(GREEN, Fade(TEAL, 0.3f));
    enemyCards.draw(RED, BLUE);
}

void StartOverAgain(CardCollection &me, CardCollection &enemy) {
    for (ushort i = 0; i < BattleManager::maxTier; ++i) {
        BattleManager::battleGenerated[i] = false;
    }
    for (ushort i = 0; i < BattleManager::maxTier; ++i) {
        BattleManager::battleDone[i] = false;
    }
         
    BattleManager::currentTier = BattleManager::maxTier;
    me.generateRandomCards(BattleManager::currentTier, myPos);
    enemy.generateRandomCards(BattleManager::currentTier, enemyPos);
}

void BattleResultWon(CardCollection &me, CardCollection &enemy, ushort mx, ushort my) {
    static bool restarted = false;
    static bool restartButtonSpawned = false;

    float restartButtonOffset = 100;
    Rectangle restartButton = { ScreenSettings::centerX, ScreenSettings::centerY - restartButtonOffset, 50, 50 };

    if (BattleManager::currentTier == 1 && enemy.getSize() == 0) {
        restartButtonSpawned = true;
     
    }
    if (restartButtonSpawned && !restarted) {
        DrawRectangleRec(restartButton, DARKGRAY); 
        DrawRectangleLinesEx(restartButton, 2, BLACK);  
        if (isCursorOnImage(mx, my, restartButton.x, restartButton.y,
            restartButton.width, restartButton.height) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            BattleManager::winCount += 1;
            StartOverAgain(me, enemy);
            restarted = true;
        }
    }
    if (restarted) { restartButtonSpawned = false; restarted = false; }
}

void HandleTiers(OrbGroup &orbs, CardCollection &me, CardCollection &enemy) {
    for (int tier = BattleManager::currentTier - 1; tier >= 0; --tier) {
        if (!BattleManager::battleGenerated[tier] &&
            (tier == BattleManager::maxTier - 1 || BattleManager::battleDone[tier + 1])) {
            me.generateRandomCards(tier + 1, myPos);
            enemy.generateRandomCards(tier + 1, enemyPos);
            BattleManager::battleGenerated[tier] = true;
        }

        if (BattleManager::battleGenerated[tier] && !BattleManager::battleDone[tier]) {
            if (me.getSize() == 0 || enemy.getSize() == 0) {
                orbs.fillOrbs();

                me.wipe();
                enemy.wipe();

                BattleManager::battleDone[tier] = true;

                if (tier > 0) {
                    BattleManager::currentTier = tier;
                    BattleManager::battleGenerated[tier - 1] = false;
                }
            }
        }
    }
}


void HandleBattle(CardCollection &me, CardCollection &enemy) {
    if (enemy.getSize() == 0 && BattleManager::currentTier == 1) {
        DrawText("Thanks for playing!", ScreenSettings::centerX - 50, ScreenSettings::centerY, 25, DARKGREEN);
        float textSize = MeasureText("Deeper, farther... the stars blur, the void whispers.", 25);
        DrawText("Deeper, farther... the stars blur, the void whispers.",
            ScreenSettings::centerX - (textSize / 3), ScreenSettings::centerY + 35, 25, DARKGREEN);
    }
}

void BattleLoop(Orb &blue, CardCollection &me, CardCollection &enemy, ushort mx, ushort my) {
    std::cout << "Current Turn: " << BattleManager::entityTurn.c_str() << std::endl;

    if (enemy.getSize() == 0) {          
        me.wipe();
        BattleManager::entityTurn = "Player";  
    }

    std::cout << "Enemy's cards: " << enemy.getSize() << std::endl;


    if (!blue.getWindowsSpawned()) {
        me.checkCursor(mx, my);
        me.select(mx, my);
        me.dragCard(mx, my);
    }

    if (BattleManager::entityTurn == "Player") {
        if (me.attack(enemy) && enemy.getSize() > 1) {
            BattleManager::entityTurn = "Enemy";  
        }
    }
    else if (BattleManager::entityTurn == "Enemy") {
        enemy.rndAttack(me);
        BattleManager::entityTurn = "Player";
    }
    
    HandleBattle(me, enemy);
}


void DrawTierInfo() {
    DrawText(TextFormat("Current tier: %hu", BattleManager::currentTier), 0, 0, 30, WHITE);
}


void IntroGuide(Tooltip *tooltip, ushort mx, ushort my) {
    Color tooltipColor = RAYWHITE;

    float rectWidth = 400;
    float rectHeight = 250;
   
    ushort fontSize = 10;

    Vector2 rectPos = Vector2(ScreenSettings::centerX - (rectWidth / 2), ScreenSettings::centerY);
    Rectangle introTipRect = { .x = rectPos.x,     .y = rectPos.y - (rectHeight / 2), .width = rectWidth / 2, .height = rectHeight / 2 };
    Rectangle orbTipRect = { .x = rectPos.x + 200, .y = rectPos.y - (rectHeight / 2), .width = rectWidth / 2, .height = rectHeight / 2 };

    tooltip[0].setPos(Vector2(introTipRect.x, introTipRect.y));
    tooltip[0].spawn(
    "The goal - to reach tier 1 cards\nYou will learn something about\nthis place...", fontSize, tooltipColor);
    tooltip[0].update(tooltip[0].getPos(), mx, my);

    tooltip[1].setPos(Vector2(orbTipRect.x, orbTipRect.y));
    tooltip[1].spawn(
    "Red orb - upgrades all you cards\nViolet orb - debuffes enemy cards\nBlue - ability to steal enemy card", fontSize, tooltipColor);
    tooltip[1].update(tooltip[1].getPos(), mx, my);
}


void MainLoop() {
    PlayMusicStream(GameSettings::deepspace);
    SetMusicVolume(GameSettings::deepspace, 0.1f);

    srand(time(0));
    SetExitKey(0);

    Texture2D cursor = LoadTexture(Paths::cursor[0]);

    // Tooltip
    float rectWidth = 400;
    float rectHeight = 250;
    Vector2 rectPos = Vector2(ScreenSettings::centerX - (rectWidth / 2), ScreenSettings::centerY);
    Rectangle introTipRect = { .x = rectPos.x,       .y = rectPos.y - (rectHeight / 2), .width = rectWidth / 2, .height = rectHeight / 2 };
    Rectangle orbTipRect =   { .x = rectPos.x + 200, .y = rectPos.y - (rectHeight / 2), .width = rectWidth / 2, .height = rectHeight / 2 };

    Tooltip introTip(introTipRect, Fade(GRAY, 0.8f));
    Tooltip orbTip(orbTipRect, Fade(GRAY, 0.8f));

    Tooltip tooltips[2] = {introTip, orbTip};

    // Core
    Star stars(Paths::star, Config::starsCount);

    CardCollection myCards;
    CardCollection enemyCards;
 
    // Orb system
    OrbGroup orbs;
    orbs.fillOrbs();
    Orb blueOrb = orbs[2];

    bool battleStarted = false;
    while (!WindowShouldClose()) {
        UpdateMusicStream(GameSettings::deepspace);
        UpdateMusic();
        BeginDrawing();
        ScreenSettings::Update();
        float dt = GetFrameTime();
        ushort mx = GetMouseX(), my = GetMouseY();
         
        DrawTierInfo();

            if (!game_paused) {
                ClearBackground(DEEPBLUE);
                RunStars(stars, BattleManager::currentTier);
                
                BattleResultWon(myCards, enemyCards, mx, my);

                HandleCardPos(myCards, enemyCards);
                BattleLoop(blueOrb, myCards, enemyCards, mx, my);
                HandleTiers(orbs, myCards, enemyCards);
            
                OrbLigic(orbs, myCards, enemyCards, mx, my);

                IntroGuide(tooltips, mx, my);
            }
            else { DrawPauseState(); }


        AnimatedCursor(Vector2(mx, my), dt);
        GameState();
        EndDrawing();
    }
    UnloadMusicStream(GameSettings::deepspace);
    CloseAudioDevice();
    CloseWindow();
}