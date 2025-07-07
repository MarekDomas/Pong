#include "structs.h"

void checkProjectileBounds(Projectile *projectile, int screenWidth, int screenHeight){
    if (projectile->position.x + projectile->radius >= screenWidth){
        projectile->speed.x *= -1;
    }
    if (projectile->position.y - projectile->radius <= 0 ||
        projectile->position.y + projectile->radius >= screenHeight)
        projectile->speed.y *= -1;
}