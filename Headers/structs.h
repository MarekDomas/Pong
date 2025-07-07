#include "raylib.h"

typedef struct Player{
    Vector2 position;
    Vector2 size;
    Color color;
    short health;
}Player;

typedef struct Projectile{
    Vector2 speed;
    int radius;
    Vector2 position;
    Color color;
}Projectile;