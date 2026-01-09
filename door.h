#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

extern glm::vec3 doorPos1;
extern float doorOpen1;
extern bool doorOpening1;
extern glm::vec3 doorPos2;
extern float doorOpen2;
extern bool doorOpening2;
extern glm::vec3 doorPos3;
extern float doorOpen3;
extern bool doorOpening3;

void updateDoor(glm::vec3 doorPos, float& openAmount, bool& isOpening);
void drawSlidingDoor(glm::vec3 pos, float openAmount,
    glm::mat4 view, glm::mat4 proj, GLuint program);
void drawCube(glm::mat4 model, glm::mat4 view, glm::mat4 proj, GLuint program, glm::vec4 color);

