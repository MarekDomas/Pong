#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <sqlite3.h>
#include "Headers/raylib.h"
#include "Headers/structs.h"
#include "Headers/raymath.h"
#include "Headers/functions.h"
#include "Headers/enums.h"
#include "Headers/globals.h"

int main(void)
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic pong");
    SetTargetFPS(144);               
    InitAudioDevice();
    
    Camera2D mainCamera = {0};
    mainCamera.zoom = 1;
    Music menu_song = LoadMusicStream("resources/menu_song.wav");
    Music game_song = LoadMusicStream("resources/game_song.mp3");
    gameState = GAME;  

    loadBackground();

    int offset = 150;
    loadPlayerTexture();
    
    SetMusicVolume(menu_song,0.1);
    SetMusicVolume(game_song,0.1);
    
    PlayMusicStream(menu_song);
    PlayMusicStream(game_song);
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (gameState == MENU)
        {
            if(IsKeyPressed(KEY_ENTER)){
                gameState = GAME;
            }
            UpdateMusicStream(menu_song);
        }
        else if(gameState == GAME)
        {
            UpdateMusicStream(game_song);
            movePlayer();

            player.destRect.x = player.position.x + offset;
            player.destRect.y = player.position.y;

            if(IsKeyPressed(KEY_P)){
                gameState = PAUSED;
            }

            if(IsKeyPressed(KEY_SPACE)){
                playerShoot();
            }
            moveProjectiles();
        }
        else if(gameState == GAME_OVER){
            StopMusicStream(menu_song);
            if(IsKeyPressed(KEY_R)){
                PlayMusicStream(menu_song);
                resetGame();
            }
        }
        else if(gameState == PAUSED){
            if(IsKeyPressed(KEY_P)){
                gameState = GAME;
            }
            if(IsKeyPressed(KEY_R)){
                PlayMusicStream(menu_song);
                resetGame();
            }
        }
        
        // Draw
        {
            char scoreStr[10] = {0};
            snprintf(scoreStr, 10, "%d", score);

            BeginDrawing();
            ClearBackground(WHITE);
            BeginMode2D(mainCamera);
                
                drawBackground();
                if(gameState == GAME_OVER){
                    char msg[60]= "GAME OVER!\nYour score: ";
                    strcat(msg, scoreStr);
                    strcat(msg, "\nPress R to restart!");
                    DrawText(msg, 200, 200, 45, RED);
                }
                else if(gameState == GAME){
                    //DrawRectangleV(player.position, player.size, player.color);
                    
                    DrawTexturePro(player.texture, player.sourceRect, player.destRect, player.origin, player.rotation, WHITE);
                    drawProjectiles();

                    DrawText(scoreStr, SCREEN_WIDTH /2 - 20, 20, 45, GOLD);
                    DrawText("Press P to pause!",10,10,20,BLUE);
                    DrawFPS(1100,20);

                }
                else if(gameState == MENU){
                    DrawText("Press ENTER to Play!", 170, 50, 45, ORANGE);
                }
                else if(gameState == PAUSED){
                    char msg[60] = "Press P to play!\nYour score: ";
                    strcat(msg, scoreStr);
                    DrawText(msg, 200, 205, 45, BLUE);
                }

            EndMode2D();
            EndDrawing();
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    free(shotsPtr);
    //--------------------------------------------------------------------------------------

    return 0;
}