#include "../Headers/globals.h"


const Vector2 defaultPlayerPos = {.x = 30, .y = 150};

Player player = {.position = defaultPlayerPos, .color = GOLD, .health = 3, .size = {.x = 128, .y = 128}};

int score = 0;
enum screen gameState = MENU;

int radius = 12;
int projectileSpeed = 300;
float movementSpeed = 500;

const Vector2 screenCenter = {.x = SCREEN_WIDTH / 2 - ( RADIUS / 2), .y = SCREEN_HEIGHT / 2 - (RADIUS / 2)};
const Vector2 projectileSpeedV2 = {.x = PROJECTILE_SPEED, .y = PROJECTILE_SPEED};
Projectile projectile = {.position = screenCenter, .radius = RADIUS, .speed = projectileSpeedV2, .color = WHITE};
