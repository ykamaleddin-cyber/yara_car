#include "rooms.h"
#include "door.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

void drawRooms (GLuint program, glm::mat4 view, glm::mat4 proj)
    {
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0)), glm::vec3(10, 0.05f, 6)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 3, 0)), glm::vec3(10, 0.05f, 6)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        float doorW1 = 2.0f, doorH1 = 2.0f;
        drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-3.23f, 0.53125f, 3.0f)), glm::vec3(3.5f, 3.0125f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1.0f });
        drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, 0.53125f, 3.0f)), glm::vec3(3.0f, 3.0125f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1.0f });
        glDepthMask(GL_FALSE);
        drawSlidingDoor(doorPos1, doorOpen1, view, proj, program);
        glDepthMask(GL_TRUE);
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, -2)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, 2)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, -2)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 2)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 0)), glm::vec3(0.05f, 2, doorW1)),
            view, proj, program, { 0.4f,0.7f,0.9f,0.35f });

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-4.375f, 1.0f, -3.0f)), glm::vec3(1.25f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.5f, 1.0f, -3.0f)), glm::vec3(1.5f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(4.375f, 1.0f, -3.0f)), glm::vec3(1.25f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(1.5f, 1.0f, -3.0f)), glm::vec3(1.5f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.0f, 0.499f, -3.0f)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.499f, -3.0f)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(3.0f, 0.499f, -3.0f)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });


        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -0.49f, -3)), glm::vec3(10, 0.9f, 0.05f)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, -3)), glm::vec3(10, 0.9f, 0.05f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 2.4875f, 0)), glm::vec3(0.05f, 0.9f, 4.0f + doorW1)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, -0.4875f, 0)), glm::vec3(0.05f, 0.9f, 4.0f + doorW1)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 2.4875f, 0)), glm::vec3(0.05f, 0.9f, 6.0f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, -0.4875f, 0)), glm::vec3(0.05f, 0.9f, 6.0f)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, 3)), glm::vec3(10.0f, 0.9f, 0.05f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        glm::vec3 windows1[] = {
            {-3,1.5f,-2.975f},{0,1.5f,-2.975f},{3,1.5f,-2.975f}
        };
        for (int i = 0; i < 3; i++)
        {
            glm::mat4 win = glm::translate(glm::mat4(1.0f), windows1[i]);
            if (i < 3) win = glm::scale(win, glm::vec3(1.5f, 1.0f, 0.05f));
            else win = glm::scale(win, glm::vec3(0.05f, 1.0f, 1.5f));
            glDepthMask(GL_FALSE);

            drawCube(win, view, proj, program, glm::vec4(0.4f, 0.7f, 0.9f, 0.35f));
            glDepthMask(GL_TRUE);
        }
        glm::vec3 lampPos1[] = {
        {-4.9f,1.5f,-1.0f},{-4.9f,1.5f,1.0f}
        };
        for (int i = 0; i < 2; i++)
        {
            glm::mat4 lamp = glm::translate(glm::mat4(1.0f), lampPos1[i]);
            lamp = glm::scale(lamp, glm::vec3(0.1f, 0.4f, 0.05f));
            drawCube(lamp, view, proj, program, glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));
        }

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0) + glm::vec3(10, 0, 0)), glm::vec3(10, 0.05f, 6)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 3, 0) + glm::vec3(10, 0, 0)), glm::vec3(10, 0.05f, 6)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        float doorW2 = 2.0f, doorH2 = 2.0f;
        drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-3.23f, 0.53125f, 3.0f) + glm::vec3(10, 0, 0)), glm::vec3(3.5f, 3.0125f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1.0f });
        drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, 0.53125f, 3.0f) + glm::vec3(10, 0, 0)), glm::vec3(3.0f, 3.0125f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1.0f });
        glDepthMask(GL_FALSE);
        drawSlidingDoor(doorPos2, doorOpen2, view, proj, program);
        glDepthMask(GL_TRUE);
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, -2) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, 2) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });


        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, -2) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 2) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 0) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 2, doorW2)),
            view, proj, program, { 0.4f,0.7f,0.9f,0.35f });

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-4.375f, 1.0f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.25f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.5f, 1.0f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.5f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(4.375f, 1.0f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.25f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(1.5f, 1.0f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.5f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.0f, 0.499f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.499f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(3.0f, 0.499f, -3.0f) + glm::vec3(10, 0, 0)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });


        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -0.49f, -3) + glm::vec3(10, 0, 0)), glm::vec3(10, 0.9f, 0.05f)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, -3) + glm::vec3(10, 0, 0)), glm::vec3(10, 0.9f, 0.05f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 2.4875f, 0) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 0.9f, 4.0f + doorW1)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 2.4875f, 0) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 0.9f, 6.0f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, -0.4875f, 0) + glm::vec3(10, 0, 0)), glm::vec3(0.05f, 0.9f, 6.0f)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, 3) + glm::vec3(10, 0, 0)), glm::vec3(10.0f, 0.9f, 0.05f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        glm::vec3 windows2[] = {
            {-3,1.5f,-2.975f},{0,1.5f,-2.975f},{3,1.5f,-2.975f}
        };
        for (int i = 0; i < 3; i++)
        {
            glm::mat4 win = glm::translate(glm::mat4(1.0f), windows2[i] + glm::vec3(10, 0, 0));
            if (i < 3) win = glm::scale(win, glm::vec3(1.5f, 1.0f, 0.05f));
            else win = glm::scale(win, glm::vec3(0.05f, 1.0f, 1.5f));
            glDepthMask(GL_FALSE);

            drawCube(win, view, proj, program, glm::vec4(0.4f, 0.7f, 0.9f, 0.35f));
            glDepthMask(GL_TRUE);
        }
        glm::vec3 lampPos2[] = {
        {-4.9f,1.5f,-1.0f},{-4.9f,1.5f,1.0f}
        };
        for (int i = 0; i < 2; i++)
        {
            glm::mat4 lamp = glm::translate(glm::mat4(1.0f), lampPos2[i] + glm::vec3(10, 0, 0));
            lamp = glm::scale(lamp, glm::vec3(0.1f, 0.4f, 0.05f));
            drawCube(lamp, view, proj, program, glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));
        }
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0) + glm::vec3(20, 0, 0)), glm::vec3(10, 0.05f, 6)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 3, 0) + glm::vec3(20, 0, 0)), glm::vec3(10, 0.05f, 6)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        float doorW3 = 2.0f, doorH3 = 2.0f;
        drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-3.23f, 0.53125f, 3.0f) + glm::vec3(20, 0, 0)), glm::vec3(3.5f, 3.0125f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1.0f });
        drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, 0.53125f, 3.0f) + glm::vec3(20, 0, 0)), glm::vec3(3.0f, 3.0125f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1.0f });
        glDepthMask(GL_FALSE);
        drawSlidingDoor(doorPos3, doorOpen3, view, proj, program);
        glDepthMask(GL_TRUE);
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, -2) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, 2) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, 0) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 2, doorW3)),
            view, proj, program, { 0.4f,0.7f,0.9f,0.35f });

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, -2) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 2) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 2, 2)),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 0) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 2, doorW3)),
            view, proj, program, { 0.4f,0.7f,0.9f,0.35f });

        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-4.375f, 1.0f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.25f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.5f, 1.0f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.5f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(4.375f, 1.0f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.25f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(1.5f, 1.0f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.5f, 2.0f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.0f, 0.499f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.499f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(3.0f, 0.499f, -3.0f) + glm::vec3(20, 0, 0)), glm::vec3(1.5f, 1.01f, 0.05f)),
            view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });


        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -0.49f, -3) + glm::vec3(20, 0, 0)), glm::vec3(10, 0.9f, 0.05f)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, -3) + glm::vec3(20, 0, 0)), glm::vec3(10, 0.9f, 0.05f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 2.4875f, 0) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 0.9f, 4.0f + doorW1)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 2.4875f, 0) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 0.9f, 6.0f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, -0.4875f, 0) + glm::vec3(20, 0, 0)), glm::vec3(0.05f, 0.9f, 6.0f)),
            view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
        drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, 3) + glm::vec3(20, 0, 0)), glm::vec3(10.0f, 0.9f, 0.05f)),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });
        glm::vec3 windows3[] = {
            {-3,1.5f,-2.975f},{0,1.5f,-2.975f},{3,1.5f,-2.975f}
        };
        for (int i = 0; i < 3; i++)
        {
            glm::mat4 win = glm::translate(glm::mat4(1.0f), windows3[i] + glm::vec3(20, 0, 0));
            if (i < 3) win = glm::scale(win, glm::vec3(1.5f, 1.0f, 0.05f));
            else win = glm::scale(win, glm::vec3(0.05f, 1.0f, 1.5f));
            glDepthMask(GL_FALSE);

            drawCube(win, view, proj, program, glm::vec4(0.4f, 0.7f, 0.9f, 0.35f));
            glDepthMask(GL_TRUE);
        }
        glm::vec3 lampPos3[] = {
        {-4.9f,1.5f,-1.0f},{-4.9f,1.5f,1.0f}
        };
        for (int i = 0; i < 2; i++)
        {
            glm::mat4 lamp = glm::translate(glm::mat4(1.0f), lampPos3[i] + glm::vec3(20, 0, 0));
            lamp = glm::scale(lamp, glm::vec3(0.1f, 0.4f, 0.05f));
            drawCube(lamp, view, proj, program, glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));
        }
    }
