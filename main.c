#include <stdio.h>
#include <string.h>
#include "Headers/raylib.h"
#include "Headers/structs.h"
#include "Headers/raymath.h"
#include "Headers/functions.h"
#include "Headers/enums.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 550

int main(void)
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic pong");
    SetTargetFPS(144);               
    InitAudioDevice();

    Vector2 defaultPlayerPos = {.x = 30, .y = 150};
    Vector2 defaultEnemyPos = {.x = 745, .y = 150};

    Player player = {.position = defaultPlayerPos, .color = GOLD, .health = 3, .size = {.x = 25, .y = 80}};
    Player enemy = {.position = defaultEnemyPos, .color = WHITE, .health = 3, .size = {.x = 25, .y = 80}};
    
    Camera2D mainCamera = {0};
    mainCamera.zoom = 1;
    
    enum screen gameState = MENU;
    Music music = LoadMusicStream("resources/song.wav");
    int score = 0;
    
    SetMusicVolume(music,0.1);
    
    int radius = 12;
    int projectileSpeed = 300;
    float movementSpeed = 300;
    Vector2 screenCenter = {.x = SCREEN_WIDTH / 2 - ( radius / 2), .y = SCREEN_HEIGHT / 2 - (radius / 2)};
    Vector2 projectileSpeedV2 = {.x = projectileSpeed, .y = projectileSpeed};
    Projectile projectile = {.position = screenCenter, .radius = radius, .speed = projectileSpeedV2, .color = WHITE};

    PlayMusicStream(music);

    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (gameState == MENU)
        {
            if(IsKeyPressed(KEY_ENTER)){
                gameState = GAME;
            }
        }
        else if(gameState == GAME)
        {
            UpdateMusicStream(music);

            if (IsKeyDown(KEY_W) && player.position.y > 0) {
                player.position.y -= movementSpeed * GetFrameTime();
            }
            if (IsKeyDown(KEY_S) && player.position.y < SCREEN_HEIGHT - player.size.y) {
                player.position.y += movementSpeed * GetFrameTime();
            }

            
            if(projectile.position.x - radius <= 0 ){
                gameState = GAME_OVER;
            }
            
            checkProjectileBounds(&projectile, SCREEN_WIDTH, SCREEN_HEIGHT);
            
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
                
            projectile.position = Vector2Add( projectile.position, Vector2Scale(projectile.speed, GetFrameTime()));

            enemy.position.y = projectile.position.y - enemy.size.y /2;

            if(IsKeyPressed(KEY_P)){
                gameState = PAUSED;
            }
        }
        else if(gameState == GAME_OVER){
            StopMusicStream(music);
            if(IsKeyPressed(KEY_R)){
                PlayMusicStream(music);
                player.position = defaultPlayerPos;
                enemy.position = defaultEnemyPos;
                projectile.position = screenCenter;
                projectile.speed = projectileSpeedV2;
                score = 0;
                gameState = GAME;
            }
        }
        else if(gameState == PAUSED){
            if(IsKeyPressed(KEY_P)){
                gameState = GAME;
            }
        }
        
        // Draw
        {
            char scoreStr[10] = {0};
            snprintf(scoreStr, 10, "%d", score);

            BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(mainCamera);

                if(gameState == GAME_OVER){
                    char msg[60]= "GAME OVER!\nYour score: ";
                    strcat(msg, scoreStr);
                    strcat(msg, "\nPRESS R TO RESTART!");
                    DrawText(msg, 200, 200, 45, RED);
                }
                else if(gameState == GAME){

                    DrawText(scoreStr, SCREEN_WIDTH /2 - 20, 20, 45, WHITE);
                    DrawRectangleV(player.position, player.size, player.color);
    
                    DrawRectangleV(enemy.position, enemy.size, enemy.color);
                    DrawCircleV(projectile.position, projectile.radius,projectile.color);
                }
                else if(gameState == MENU){
                    DrawText("PRESS ENTER TO PLAY!", 170, 250, 45, BLUE);
                }
                else if(gameState == PAUSED){
                    DrawText("PRESS P TO PLAY!", 150, 250, 45, BLUE);
                }

            EndMode2D();
            EndDrawing();
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}