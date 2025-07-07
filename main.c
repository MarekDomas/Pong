#include <stdio.h>
#include <string.h>
#include "Headers/raylib.h"
#include "Headers/structs.h"
#include "Headers/raymath.h"
#include "Headers/functions.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 550

int main(void)
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic pong");
    SetTargetFPS(144);               
    InitAudioDevice();

    Player player = {.position = {.x = 30, .y = 150}, .color = GOLD, .health = 3, .size = {.x = 25, .y = 80}};
    Player enemy = {.position = {.x = 745, .y = 150}, .color = WHITE, .health = 3, .size = {.x = 25, .y = 80}};

    Camera2D mainCamera = {0};
    mainCamera.zoom = 1;
    
    Music music = LoadMusicStream("resources/song.wav");
    PlayMusicStream(music);
    SetMusicVolume(music,0.1);
    
    int radius = 12;
    int projectileSpeed = 2;
    float movementSpeed = 3;
    int score = 0;
    Projectile projectile = {.position = {.x = SCREEN_WIDTH / 2 - ( radius / 2), .y = SCREEN_HEIGHT / 2 - (radius / 2)}, .radius = radius, .speed = {.x = projectileSpeed, .y = projectileSpeed}, .color = WHITE};
    bool lost = false;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if(!lost)
        {
            #pragma region update_logic
            UpdateMusicStream(music);

            if(IsKeyDown(KEY_W) && !player.position.y <= 0){
                player.position.y -= movementSpeed;
            }
            if(IsKeyDown(KEY_S) && player.position.y <= SCREEN_HEIGHT - player.size.y){
                player.position.y += movementSpeed;
            }
            
            if(projectile.position.x - radius <= 0 ){
                lost = true;
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
                
            projectile.position = Vector2Add( projectile.position, projectile.speed);

            enemy.position.y = projectile.position.y - enemy.size.y /2;
            #pragma endregion update_logic
        }

        // Draw
        {
            char scoreStr[10] = {0};

            snprintf(scoreStr, 10, "%d", score);

            BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(mainCamera);

                if(lost){
                    char msg[60]= "GAME OVER!\nYour score: ";
                    strcat(msg, scoreStr);
                    DrawText(msg, 250, 250, 45, RED);
                }
                DrawRectangleV(player.position, player.size, player.color);

                DrawRectangleV(enemy.position, enemy.size, enemy.color);
                DrawCircleV(projectile.position, projectile.radius,projectile.color);
                DrawText(scoreStr, SCREEN_WIDTH /2 - 20, 20, 45, GOLD);
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