#include "../Headers/structs.h"
#include "../Headers/globals.h"

void checkProjectileBounds(void){
    if (projectile.position.x + projectile.radius >= SCREEN_WIDTH){
        projectile.speed.x *= -1;
    }
    if (projectile.position.y - projectile.radius <= 0 ||
        projectile.position.y + projectile.radius >= SCREEN_HEIGHT)
        projectile.speed.y *= -1;
}

void resetGame(void){
    player.position = defaultPlayerPos;
    enemy.position = defaultEnemyPos;
    projectile.position = screenCenter;
    projectile.speed = projectileSpeedV2;
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
    Vector2 projectileCenter = {.x = projectile.position.x , .y = projectile.position.y + projectile.radius};
    Rectangle playerRectangle = {.height = player.size.y, .width = player.size.x, .x = player.position.x, .y = player.position.y};
    Rectangle enemyRectangle = {.height = enemy.size.y, .width = enemy.size.x, .x = enemy.position.x, .y = enemy.position.y};

    if (CheckCollisionCircleRec(projectileCenter,projectile.radius,playerRectangle))
    {
        projectile.speed.x *= - 1;
        score++;
    }
    else if(CheckCollisionCircleRec(projectileCenter,projectile.radius,enemyRectangle)){
        projectile.speed.x *= - 1;
    }
}