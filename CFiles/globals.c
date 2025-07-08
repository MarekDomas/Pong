#include "../Headers/globals.h"


const Vector2 defaultPlayerPos = {.x = 30, .y = 150};
const Vector2 defaultEnemyPos = {.x = 745, .y = 150};

Player player = {.position = defaultPlayerPos, .color = GOLD, .health = 3, .size = {.x = 25, .y = 80}};
Player enemy = {.position = defaultEnemyPos, .color = WHITE, .health = 3, .size = {.x = 25, .y = 80}};

int score = 0;
enum screen gameState = MENU;

int radius = 12;
int projectileSpeed = 300;
float movementSpeed = 300;

const Vector2 screenCenter = {.x = SCREEN_WIDTH / 2 - ( RADIUS / 2), .y = SCREEN_HEIGHT / 2 - (RADIUS / 2)};
const Vector2 projectileSpeedV2 = {.x = PROJECTILE_SPEED, .y = PROJECTILE_SPEED};
Projectile projectile = {.position = screenCenter, .radius = RADIUS, .speed = projectileSpeedV2, .color = WHITE};
