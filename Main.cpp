#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "collision.h"
#include "door.h"
#include "rooms.h"
#include "street.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1600, 800, "Car Showroom - Double Rooms", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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

            float ambientFactor = 0.3;
            vec3 ambient = ambientFactor * vec3(uColor);
            vec3 diffuse = diff * vec3(uColor);
            vec3 specular = spec * vec3(1.0);

            vec3 result = ambient + diffuse + specular;
            FragColor = vec4(result, uColor.a);
        }
    )";

GLuint program = createProgram(vsSrc, fsSrc);

float cubeVertices[] = {
    -0.5f,-0.5f,-0.5f, 0,0,-1,  0.5f,-0.5f,-0.5f, 0,0,-1,  0.5f,0.5f,-0.5f, 0,0,-1,
    -0.5f,-0.5f,-0.5f, 0,0,-1,  0.5f,0.5f,-0.5f, 0,0,-1, -0.5f,0.5f,-0.5f, 0,0,-1,
    -0.5f,-0.5f,0.5f, 0,0,1,  0.5f,-0.5f,0.5f, 0,0,1,  0.5f,0.5f,0.5f, 0,0,1,
    -0.5f,-0.5f,0.5f, 0,0,1,  0.5f,0.5f,0.5f, 0,0,1, -0.5f,0.5f,0.5f, 0,0,1,
    -0.5f,0.5f,0.5f,-1,0,0, -0.5f,0.5f,-0.5f,-1,0,0, -0.5f,-0.5f,-0.5f,-1,0,0,
    -0.5f,-0.5f,-0.5f,-1,0,0, -0.5f,-0.5f,0.5f,-1,0,0, -0.5f,0.5f,0.5f,-1,0,0,
     0.5f,0.5f,0.5f,1,0,0, 0.5f,0.5f,-0.5f,1,0,0, 0.5f,-0.5f,-0.5f,1,0,0,
     0.5f,-0.5f,-0.5f,1,0,0, 0.5f,-0.5f,0.5f,1,0,0, 0.5f,0.5f,0.5f,1,0,0,
    -0.5f,-0.5f,-0.5f,0,-1,0, 0.5f,-0.5f,-0.5f,0,-1,0, 0.5f,-0.5f,0.5f,0,-1,0,
    -0.5f,-0.5f,-0.5f,0,-1,0, 0.5f,-0.5f,0.5f,0,-1,0, -0.5f,-0.5f,0.5f,0,-1,0,
    -0.5f,0.5f,-0.5f,0,1,0, 0.5f,0.5f,-0.5f,0,1,0, 0.5f,0.5f,0.5f,0,1,0,
    -0.5f,0.5f,-0.5f,0,1,0, 0.5f,0.5f,0.5f,0,1,0, -0.5f,0.5f,0.5f,0,1,0
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
        updateDoor(doorPos1, doorOpen1, doorOpening1);
        updateDoor(doorPos2, doorOpen2, doorOpening2);
        updateDoor(doorPos3, doorOpen3, doorOpening3);
        float time = glfwGetTime();
        deltaTime = time - lastFrame;
        lastFrame = time;
        processInput(window);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), 2.0f, 0.1f, 100.0f);

        glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program);
        glUniform3f(glGetUniformLocation(program, "lightPos"), 0.0f, 3.0f, 0.0f);
        glUniform3f(glGetUniformLocation(program, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);
                    drawRooms(program,view,proj);
                    drawStreet(program, view, proj);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
