#include "../Headers/structs.h"
#include "../Headers/globals.h"

static Texture2D playerTexture;
// static Texture2D playerUp;
// static Texture2D playerDown;


void resetGame(void){
    player.position = defaultPlayerPos;
    score = 0;
    gameState = GAME;
}

void movePlayer(void){
    if (IsKeyDown(KEY_W) && player.position.y > 0) {
        player.position.y -= movementSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) && player.position.y < SCREEN_HEIGHT - player.size.y) {
        player.position.y += movementSpeed * GetFrameTime();
    }
}

void checkColisions(void){
    
}

void loadPlayerTexture(void){
    playerTexture = LoadTexture("resources/player_idle.png");
    Rectangle sourceRect = {.x = 0, .y = 0, .height = playerTexture.height, .width = playerTexture.width};
    Rectangle destRect = {.height = player.size.y, .width = player.size.x};
    Vector2 origin = {0};
    int rotation = 90;

    player.texture = playerTexture;
    player.sourceRect = sourceRect;
    player.destRect = destRect;
    player.origin = origin;
    player.rotation = rotation;
}

void loadTextures(void){
    //TODO animace
}