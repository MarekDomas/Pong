#ifndef GLOBALS_H
#define GLOBALS_H

#include "structs.h"
#include "raylib.h"
#include "enums.h"
#define SCREEN_WIDTH 800*1.5
#define SCREEN_HEIGHT 550*1.5

#define RADIUS 12
#define PROJECTILE_SPEED 300
#define MOVEMENT_SPEED 300

extern Player player;
extern Projectile **shotsPtr; //Array of shots
extern int numberOfShots;
extern int activeShots;

extern int score;
extern enum screen gameState;

extern int radius;
extern int projectileSpeed;
extern float movementSpeed;

extern const Vector2 screenCenter;
extern const Vector2 projectileSpeedV2;
extern const Vector2 defaultPlayerPos;

#endif