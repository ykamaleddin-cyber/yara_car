#include "tree.h"
#include "door.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void drawTree(glm::vec3 pos, glm::mat4 view, glm::mat4 proj, GLuint program)
{
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 0.65f, 0.0f)), glm::vec3(0.5f, 2.5f, 0.2f)),
        view, proj, program, { 0.55f, 0.27f, 0.07f, 1.0f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 1.5f, 0.0f)), glm::vec3(1.1f, 0.7f, 0.9f)),
        view, proj, program, { 0.0f, 0.6f, 0.0f, 1.0f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 2.1f, 0.0f)), glm::vec3(0.9f, 0.7f, 0.8f)),
        view, proj, program, { 0.0f, 0.7f, 0.0f, 1.0f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 2.7f, 0.0f)), glm::vec3(0.7f, 0.7f, 0.6f)),
        view, proj, program, { 0.0f, 0.8f, 0.0f, 1.0f });
}
