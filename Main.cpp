#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void drawCube(glm::mat4 model, glm::mat4 view, glm::mat4 proj, GLuint program, glm::vec3 color)
{
    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(glGetUniformLocation(program, "uMVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform3f(glGetUniformLocation(program, "uColor"), color.r, color.g, color.b);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main()
{
    // ===== GLFW Init =====
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Car Showroom", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ===== Shader =====
    const char* vsSrc = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 uMVP;
        void main() { gl_Position = uMVP * vec4(aPos, 1.0); }
    )";

    const char* fsSrc = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec3 uColor;
        void main() { FragColor = vec4(uColor, 1.0); }
    )";

    GLuint program = createProgram(vsSrc, fsSrc);

    // ===== Cube Vertices =====
    float cubeVertices[] = {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,0.5f,-0.5f,  -0.5f,-0.5f,-0.5f,  0.5f,0.5f,-0.5f, -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,   0.5f,-0.5f,0.5f,   0.5f,0.5f,0.5f,   -0.5f,-0.5f,0.5f,   0.5f,0.5f,0.5f, -0.5f,0.5f,0.5f,
        -0.5f,0.5f,0.5f,   -0.5f,0.5f,-0.5f,  -0.5f,-0.5f,-0.5f,  -0.5f,-0.5f,-0.5f,  -0.5f,-0.5f,0.5f, -0.5f,0.5f,0.5f,
         0.5f,0.5f,0.5f,    0.5f,0.5f,-0.5f,   0.5f,-0.5f,-0.5f,   0.5f,-0.5f,-0.5f,   0.5f,-0.5f,0.5f,  0.5f,0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,   0.5f,-0.5f,-0.5f,   0.5f,-0.5f,0.5f,  -0.5f,-0.5f,-0.5f,   0.5f,-0.5f,0.5f, -0.5f,-0.5f,0.5f,
        -0.5f,0.5f,-0.5f,    0.5f,0.5f,-0.5f,   0.5f,0.5f,0.5f,  -0.5f,0.5f,-0.5f,   0.5f,0.5f,0.5f, -0.5f,0.5f,0.5f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float time = glfwGetTime();
        deltaTime = time - lastFrame;
        lastFrame = time;
        processInput(window);

        glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 100.0f);

        glUseProgram(program);

        // ===== Room =====
        glm::mat4 floorM = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        floorM = glm::scale(floorM, glm::vec3(10.0f, 0.05f, 6.0f));
        drawCube(floorM, view, proj, program, glm::vec3(0.6f, 0.6f, 0.6f));

        glm::mat4 ceilingM = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
        ceilingM = glm::scale(ceilingM, glm::vec3(10.0f, 0.05f, 6.0f));
        drawCube(ceilingM, view, proj, program, glm::vec3(0.6f, 0.6f, 0.6f));

        // Walls
        glm::mat4 backWall = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, -3.0f));
        backWall = glm::scale(backWall, glm::vec3(10.0f, 2.0f, 0.05f));
        drawCube(backWall, view, proj, program, glm::vec3(0.8f, 0.8f, 0.85f));
        glm::mat4 frontWall = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 3.0f));
        frontWall = glm::scale(frontWall, glm::vec3(10.0f, 2.0f, 0.05f));
        drawCube(frontWall, view, proj, program, glm::vec3(0.8f, 0.8f, 0.85f));
        glm::mat4 leftWall = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 1.0f, 0.0f));
        leftWall = glm::scale(leftWall, glm::vec3(0.05f, 2.0f, 6.0f));
        drawCube(leftWall, view, proj, program, glm::vec3(0.85f, 0.85f, 0.8f));
        glm::mat4 rightWall = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 1.0f, 0.0f));
        rightWall = glm::scale(rightWall, glm::vec3(0.05f, 2.0f, 6.0f));
        drawCube(rightWall, view, proj, program, glm::vec3(0.85f, 0.85f, 0.8f));

        // ===== Windows =====
        glm::vec3 windows[] = {
            {-3.0f, 1.5f, -2.975f}, {0.0f,1.5f,-2.975f}, {3.0f,1.5f,-2.975f}, // Back wall
            {-4.975f,1.5f,-2.0f}, {-4.975f,1.5f,2.0f}, // Left wall
            {4.975f,1.5f,-2.0f}, {4.975f,1.5f,2.0f}   // Right wall
        };

        for (int i = 0; i < 7; i++)
        {
            glm::mat4 win = glm::translate(glm::mat4(1.0f), windows[i]);
            if (i < 3) win = glm::scale(win, glm::vec3(1.5f, 1.0f, 0.05f));
            else win = glm::scale(win, glm::vec3(0.05f, 1.0f, 1.5f));
            drawCube(win, view, proj, program, glm::vec3(0.3f, 0.6f, 0.8f));

            // ===== Windows Reflection =====
          /*  glm::mat4 refl = glm::translate(glm::mat4(1.0f), glm::vec3(windows[i].x, -1.0f, windows[i].z));
            if (i < 3) refl = glm::scale(refl, glm::vec3(1.5f, -1.0f, 0.05f));
            else refl = glm::scale(refl, glm::vec3(0.05f, -1.0f, 1.5f));
            drawCube(refl, view, proj, program, glm::vec3(0.3f, 0.6f, 0.8f) * 0.4f);*/

            glm::mat4 refl = glm::translate(glm::mat4(1.0f), glm::vec3(windows[i].x, -0.98f, windows[i].z));
            if (i < 3) refl = glm::scale(refl, glm::vec3(1.5f, 0.15f, 0.05f));
            else refl = glm::scale(refl, glm::vec3(0.05f, 0.19f, 1.5f));
            drawCube(refl, view, proj, program, glm::vec3(0.3f, 0.6f, 0.8f) * 0.3f);
        }

        // ===== Lamps Between Windows =====
        glm::vec3 lampPos[] = { {-4.9f,1.5f,-1.0f}, {-4.9f,1.5f,1.0f}, {4.9f,1.5f,-1.0f}, {4.9f,1.5f,1.0f} };
        for (int i = 0; i < 4; i++)
        {
            glm::mat4 lamp = glm::translate(glm::mat4(1.0f), lampPos[i]);
            lamp = glm::scale(lamp, glm::vec3(0.1f, 0.4f, 0.05f));
            drawCube(lamp, view, proj, program, glm::vec3(1.0f, 1.0f, 0.8f));

            // Lamp Reflection
          /*  glm::mat4 refl = glm::translate(glm::mat4(1.0f), glm::vec3(lampPos[i].x, -1.0f, lampPos[i].z));
            refl = glm::scale(refl, glm::vec3(0.1f, -0.4f, 0.05f));
            drawCube(refl, view, proj, program, glm::vec3(1.0f, 1.0f, 0.8f) * 0.4f);*/

            glm::mat4 refl = glm::translate(glm::mat4(1.0f), glm::vec3(lampPos[i].x, -0.98f, lampPos[i].z));
            refl = glm::scale(refl, glm::vec3(0.1f, 0.19f, 0.05f));
            drawCube(refl, view, proj, program, glm::vec3(1.0f, 1.0f, 0.8f) * 0.3f);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
