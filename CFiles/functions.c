#include <stdlib.h>
#include "../Headers/raylib.h"
#include "../Headers/structs.h"
#include "../Headers/globals.h"
#include "../Headers/raymath.h"

static Texture2D playerTexture;
static Texture2D background;
static Rectangle backgroundSource;
static Rectangle backDest;

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

void loadBackground(void){
    background = LoadTexture("resources/background.png");

    backgroundSource.height = background.height;
    backgroundSource.width = background.width;
    
    backDest.height = SCREEN_HEIGHT;
    backDest.width = SCREEN_WIDTH;
}

void drawBackground(void){
    DrawTexturePro(background, backgroundSource, backDest, Vector2Zero(), 0, WHITE);
}

void playerShoot(void){
    if(shotsPtr == NULL){
        shotsPtr = malloc(sizeof(Projectile));
    }
    else{
        shotsPtr = realloc(shotsPtr, sizeof(Projectile) * (numberOfShots + 1));
    }
    
    Projectile *projectile = malloc(sizeof(Projectile));
    projectile->color = RED;
    projectile->radius = radius;
    projectile->speed.x = projectileSpeed;
    projectile->position.x = player.destRect.x - radius;
    projectile->position.y = player.destRect.y + 0.5 * player.destRect.height - radius;

    shotsPtr[numberOfShots] = projectile;

    numberOfShots++;
    activeShots++;
}

void moveProjectiles(void){
    if(shotsPtr == NULL){
        return;
    }

    for(int i = 0; i < numberOfShots; i++){
        if(shotsPtr[i] != NULL){
            shotsPtr[i]->position.x += projectileSpeed * GetFrameTime();
        }

        if(shotsPtr[i] != NULL){
            if(shotsPtr[i]->position.x > SCREEN_WIDTH + radius){
                free(shotsPtr[i]);
                shotsPtr[i] = NULL;
                activeShots--;
            }
        }
    }
}

void drawProjectiles(void){
    if(shotsPtr == NULL){
        return;
    }

    Vector2 center = {0};
    for(int i = 0; i < numberOfShots; i++){
        if(shotsPtr[i] != NULL){
            center.x = shotsPtr[i]->position.x + radius;
            center.y = shotsPtr[i]->position.y + radius;
            DrawCircleV(center,radius,shotsPtr[i]->color);
        }
    }
}