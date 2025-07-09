#include "../Headers/globals.h"
#include <stdlib.h>

const Vector2 defaultPlayerPos = {.x = 30, .y = 150};

Player player = {.position = defaultPlayerPos, .color = GOLD, .health = 3, .size = {.x = 128, .y = 128}};

int score = 0;
enum screen gameState = MENU;

int radius = 12;
int projectileSpeed = 700;
float movementSpeed = 700;

const Vector2 screenCenter = {.x = SCREEN_WIDTH / 2 - ( RADIUS / 2), .y = SCREEN_HEIGHT / 2 - (RADIUS / 2)};
const Vector2 projectileSpeedV2 = {.x = PROJECTILE_SPEED, .y = 0};
Projectile **shotsPtr = NULL;
int numberOfShots = 0;
int activeShots = 0;

//Projectile projectile = {.position = screenCenter, .radius = RADIUS, .speed = projectileSpeedV2, .color = WHITE};
