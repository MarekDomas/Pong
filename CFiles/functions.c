#include "../Headers/structs.h"
#include "../Headers/globals.h"

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