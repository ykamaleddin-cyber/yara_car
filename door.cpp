#include "door.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


glm::vec3 doorPos1 = glm::vec3(0.26f, 0.0f, 3.025f);
float doorOpen1 = 0.0f;
bool doorOpening1 = false;

glm::vec3 doorPos2 = glm::vec3(10.26f, 0.0f, 3.025f);
float doorOpen2 = 0.0f;
bool doorOpening2 = false;

glm::vec3 doorPos3 = glm::vec3(20.26f, 0.0f, 3.025f);
float doorOpen3 = 0.0f;
bool doorOpening3 = false;

void drawCube(glm::mat4 model, glm::mat4 view, glm::mat4 proj, GLuint program, glm::vec4 color)
{
    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(glGetUniformLocation(program, "uMVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(glGetUniformLocation(program, "uColor"),
        color.r, color.g, color.b, color.a);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void updateDoor(glm::vec3 doorPos, float& openAmount, bool& isOpening)
{
    float dist = glm::distance(cameraPos, doorPos);
    if (dist < 2.0f)
        isOpening = true;
    else if (dist > 3.0f)
        isOpening = false;
    if (isOpening && openAmount < 1.0f)
        openAmount += deltaTime * 1.5f;
    else if (!isOpening && openAmount > 0.0f)
        openAmount -= deltaTime * 1.5f;
}
void drawSlidingDoor(glm::vec3 pos, float openAmount,
    glm::mat4 view, glm::mat4 proj, GLuint program)
{
    float doorWidth = 3.48f;
    float doorHeight = 5.0f;
    float doorThick = 0.05f;

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, pos);

    float slide = -openAmount * doorWidth;
    model = glm::translate(model, glm::vec3(slide, 0.0f, 0.0f));

    model = glm::scale(model, glm::vec3(doorWidth, doorHeight, doorThick));

    drawCube(model, view, proj, program, glm::vec4(0.4f, 0.7f, 0.9f, 0.35f));
}
