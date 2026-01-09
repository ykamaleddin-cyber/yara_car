#pragma once
#include <glm/glm.hpp>

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

bool checkCollision(const AABB& box, const glm::vec3& point);
