#include "street.h"
#include "door.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tree.h"

void drawStreet (GLuint program, glm::mat4 view, glm::mat4 proj) {
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.05f, 10.0f)), glm::vec3(60.0f, 0.05f, 15.0f)),
        view, proj, program, { 0.15f, 0.15f, 0.15f, 1.0f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 4.5f)), glm::vec3(40.0f, 0.1f, 1.0f)),
        view, proj, program, { 0.6f, 0.6f, 0.6f, 1.0f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 18.0f)), glm::vec3(40.0f, 0.1f, 1.0f)),
        view, proj, program, { 0.6f, 0.6f, 0.6f, 1.0f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 3.51f)), glm::vec3(40.0f, 0.1f, 0.98f)),
        view, proj, program, { 0.2f, 0.6f, 0.2f, 0.7f });
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 20.5f)), glm::vec3(40.0f, 0.1f, 4.0f)),
        view, proj, program, { 0.2f, 0.6f, 0.2f, 0.7f });
    for (float x = -6.8f; x <= 32.0f; x += 4.6f)
    {
        drawTree(glm::vec3(x, -1.0f, 3.6f), view, proj, program);
        drawTree(glm::vec3(x, -1.0f, 20.0f), view, proj, program);
    }
}
