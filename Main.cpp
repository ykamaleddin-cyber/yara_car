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

void drawCube(glm::mat4 model, glm::mat4 view, glm::mat4 proj, GLuint program, glm::vec4 color)
{
    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(glGetUniformLocation(program, "uMVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(glGetUniformLocation(program, "uColor"),
        color.r, color.g, color.b, color.a);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main()
{
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
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aNormal;

        uniform mat4 uMVP;
        uniform mat4 model;

        out vec3 FragPos;
        out vec3 Normal;

        void main()
        {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * aNormal;
            gl_Position = uMVP * vec4(aPos, 1.0);
        }
    )";

    const char* fsSrc = R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 FragPos;
        in vec3 Normal;

        uniform vec3 lightPos;
        uniform vec3 viewPos;
        uniform vec4 uColor;

        void main()
        {
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);

            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

            float ambientFactor = 0.3; // السقف والأشياء تظهر واضحة
            vec3 ambient = ambientFactor * vec3(uColor);
            vec3 diffuse = diff * vec3(uColor);
            vec3 specular = spec * vec3(1.0);

            vec3 result = ambient + diffuse + specular;
            FragColor = vec4(result, uColor.a);
        }
    )";

    GLuint program = createProgram(vsSrc, fsSrc);

    // ===== Cube Vertices (positions + normals) =====
    float cubeVertices[] = {
        // positions           // normals
        -0.5f,-0.5f,-0.5f,     0,0,-1,
         0.5f,-0.5f,-0.5f,     0,0,-1,
         0.5f, 0.5f,-0.5f,     0,0,-1,
        -0.5f,-0.5f,-0.5f,     0,0,-1,
         0.5f, 0.5f,-0.5f,     0,0,-1,
        -0.5f, 0.5f,-0.5f,     0,0,-1,

        -0.5f,-0.5f,0.5f,      0,0,1,
         0.5f,-0.5f,0.5f,      0,0,1,
         0.5f, 0.5f,0.5f,      0,0,1,
        -0.5f,-0.5f,0.5f,      0,0,1,
         0.5f, 0.5f,0.5f,      0,0,1,
        -0.5f, 0.5f,0.5f,      0,0,1,

        -0.5f,0.5f,0.5f,       -1,0,0,
        -0.5f,0.5f,-0.5f,      -1,0,0,
        -0.5f,-0.5f,-0.5f,     -1,0,0,
        -0.5f,-0.5f,-0.5f,     -1,0,0,
        -0.5f,-0.5f,0.5f,      -1,0,0,
        -0.5f,0.5f,0.5f,       -1,0,0,

         0.5f,0.5f,0.5f,       1,0,0,
         0.5f,0.5f,-0.5f,      1,0,0,
         0.5f,-0.5f,-0.5f,     1,0,0,
         0.5f,-0.5f,-0.5f,     1,0,0,
         0.5f,-0.5f,0.5f,      1,0,0,
         0.5f,0.5f,0.5f,       1,0,0,

        -0.5f,-0.5f,-0.5f,     0,-1,0,
         0.5f,-0.5f,-0.5f,     0,-1,0,
         0.5f,-0.5f,0.5f,      0,-1,0,
        -0.5f,-0.5f,-0.5f,     0,-1,0,
         0.5f,-0.5f,0.5f,      0,-1,0,
        -0.5f,-0.5f,0.5f,      0,-1,0,

        -0.5f,0.5f,-0.5f,      0,1,0,
         0.5f,0.5f,-0.5f,      0,1,0,
         0.5f,0.5f,0.5f,       0,1,0,
        -0.5f,0.5f,-0.5f,      0,1,0,
         0.5f,0.5f,0.5f,       0,1,0,
        -0.5f,0.5f,0.5f,       0,1,0
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        glUniform3f(glGetUniformLocation(program, "lightPos"), 0.0f, 3.0f, 0.0f);
        glUniform3f(glGetUniformLocation(program, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);

        // ===== Room =====
        drawCube(glm::scale(glm::translate(glm::mat4(1), { 0,-1,0 }), { 10,0.05f,6 }),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), { 0,3,0 }), { 10,0.05f,6 }),
            view, proj, program, { 0.6f,0.6f,0.6f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), { 0,1,-3 }), { 10,2,0.05f }),
            view, proj, program, { 0.8f,0.8f,0.85f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), { 0,1,3 }), { 10,2,0.05f }),
            view, proj, program, { 0.8f,0.8f,0.85f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), { -5,1,0 }), { 0.05f,2,6 }),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });

        drawCube(glm::scale(glm::translate(glm::mat4(1), { 5,1,0 }), { 0.05f,2,6 }),
            view, proj, program, { 0.85f,0.85f,0.8f,1 });

        // ===== Windows =====
        glm::vec3 windows[] = {
            {-3,1.5f,-2.975f},{0,1.5f,-2.975f},{3,1.5f,-2.975f},
            {-4.975f,1.5f,-2},{-4.975f,1.5f,2},
            {4.975f,1.5f,-2},{4.975f,1.5f,2}
        };

        for (int i = 0; i < 7; i++)
        {
            glm::mat4 win = glm::translate(glm::mat4(1.0f), windows[i]);
            if (i < 3) win = glm::scale(win, glm::vec3(1.5f, 1.0f, 0.05f));
            else win = glm::scale(win, glm::vec3(0.05f, 1.0f, 1.5f));

            drawCube(win, view, proj, program, glm::vec4(0.3f, 0.6f, 0.8f, 0.4f));

            glm::mat4 refl = glm::translate(glm::mat4(1.0f), glm::vec3(windows[i].x, -0.98f, windows[i].z));
            if (i < 3) refl = glm::scale(refl, glm::vec3(1.5f, 0.18f, 0.05f));
            else refl = glm::scale(refl, glm::vec3(0.05f, 0.18f, 1.5f));

            drawCube(refl, view, proj, program, glm::vec4(0.3f, 0.6f, 0.8f, 0.18f));
        }

        // ===== Lamps =====
        glm::vec3 lampPos[] = {
            {-4.9f,1.5f,-1.0f}, {-4.9f,1.5f,1.0f},
            {4.9f,1.5f,-1.0f},  {4.9f,1.5f,1.0f}
        };

        for (int i = 0; i < 4; i++)
        {
            glm::mat4 lamp = glm::translate(glm::mat4(1.0f), lampPos[i]);
            lamp = glm::scale(lamp, glm::vec3(0.1f, 0.4f, 0.05f));
            drawCube(lamp, view, proj, program, glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));

            glm::mat4 refl = glm::translate(glm::mat4(1.0f), glm::vec3(lampPos[i].x, -0.98f, lampPos[i].z));
            refl = glm::scale(refl, glm::vec3(0.1f, 0.19f, 0.05f));
            drawCube(refl, view, proj, program, glm::vec4(1.0f, 1.0f, 0.8f, 0.3f));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
