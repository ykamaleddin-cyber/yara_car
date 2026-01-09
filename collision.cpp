#include "collision.h"

bool checkCollision(const AABB& box, const glm::vec3& point)
{
    return (
        point.x >= box.min.x && point.x <= box.max.x &&
        point.y >= box.min.y && point.y <= box.max.y &&
        point.z >= box.min.z && point.z <= box.max.z
        );
}

AABB wall1 = { glm::vec3(-5, 0, -3), glm::vec3(-4.9f, 2, 3) };
AABB wall2 = { glm::vec3(5, 0, -3), glm::vec3(4.9f, 2, 3) };
AABB doorAABB;
