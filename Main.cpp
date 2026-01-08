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


void drawTree(glm::vec3 pos, glm::mat4 view, glm::mat4 proj, GLuint program)
{
    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 0.65f, 0.0f)),glm::vec3(0.5f, 2.5f, 0.2f)),  
        view, proj, program, { 0.55f, 0.27f, 0.07f, 1.0f });  

    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 1.5f, 0.0f)),glm::vec3(1.1f, 0.7f, 0.9f)), 
        view, proj, program, { 0.0f, 0.6f, 0.0f, 1.0f });

    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 2.1f, 0.0f)),glm::vec3(0.9f, 0.7f, 0.8f)),
        view, proj, program, { 0.0f, 0.7f, 0.0f, 1.0f });

    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), pos + glm::vec3(0.0f, 2.7f, 0.0f)),glm::vec3(0.7f, 0.7f, 0.6f)),
        view, proj, program, { 0.0f, 0.8f, 0.0f, 1.0f });
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
        float time = glfwGetTime();
        deltaTime = time - lastFrame;
        lastFrame = time;
        processInput(window);

        glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), 2.0f, 0.1f, 100.0f); 

        glUseProgram(program);
        glUniform3f(glGetUniformLocation(program, "lightPos"), 0.0f, 3.0f, 0.0f);
        glUniform3f(glGetUniformLocation(program, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);

        auto drawRooms = [&]()
            {
             
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0) ), glm::vec3(10, 0.05f, 6)),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 3, 0) ), glm::vec3(10, 0.05f, 6)),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });         

                float doorW1 = 2.0f, doorH1 = 2.0f, t1 = 0.05f;
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.23, 1, 3) ), glm::vec3(3.5, 2, t1)),
                    view, proj, program, { 0.8f,0.8f,0.85f,1 });
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(3.5, 1, 3) ), glm::vec3(3, 2, t1)),
                    view, proj, program, { 0.8f,0.8f,0.85f,1 });
                glDepthMask(GL_FALSE);
                drawCube( glm::scale( glm::translate( glm::mat4(1), glm::vec3(0.26f, 1.0f, 3.0f)),glm::vec3(3.48f, 2.0f, t1) ),
                    view, proj, program,{ 0.4f, 0.7f, 0.9f, 0.35f } );
                glDepthMask(GL_TRUE);


                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, -2) ), glm::vec3(0.05f, 2, 2)),
                    view, proj, program, { 0.85f,0.85f,0.8f,1 });
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(5, 1, 2) ), glm::vec3(0.05f, 2, 2)),
                    view, proj, program, { 0.85f,0.85f,0.8f,1 });           

                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, -2) ), glm::vec3(0.05f, 2, 2)),
                    view, proj, program, { 0.85f,0.85f,0.8f,1 });
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 2) ), glm::vec3(0.05f, 2, 2)),
                    view, proj, program, { 0.85f,0.85f,0.8f,1 });

                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-5, 1, 0) ), glm::vec3(0.05f, 2, doorW1)),
                    view, proj, program, { 0.4f,0.7f,0.9f,0.35f });

                drawCube( glm::scale( glm::translate( glm::mat4(1),glm::vec3(-4.375f, 1.0f, -3.0f) ),glm::vec3(1.25f, 2.0f, 0.05f)  ),
                    view, proj, program,{ 0.8f, 0.8f, 0.85f, 1 } );
                drawCube(glm::scale(glm::translate( glm::mat4(1),glm::vec3(-1.5f, 1.0f, -3.0f)  ), glm::vec3(1.5f, 2.0f, 0.05f) ),
                    view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
                drawCube(glm::scale( glm::translate( glm::mat4(1),glm::vec3(4.375f, 1.0f, -3.0f)), glm::vec3(1.25f, 2.0f, 0.05f)        ),
                    view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
                drawCube(glm::scale( glm::translate(glm::mat4(1),glm::vec3(1.5f, 1.0f, -3.0f)),glm::vec3(1.5f, 2.0f, 0.05f) ),
                    view, proj, program,{ 0.8f, 0.8f, 0.85f, 1 });
                drawCube(glm::scale( glm::translate(glm::mat4(1), glm::vec3(-3.0f, 0.499f, -3.0f)),glm::vec3(1.5f, 1.01f, 0.05f)),
                    view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
                drawCube(glm::scale( glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.499f, -3.0f) ), glm::vec3(1.5f, 1.01f, 0.05f)  ),
                    view, proj, program, { 0.8f, 0.8f, 0.85f, 1 });
                drawCube( glm::scale( glm::translate( glm::mat4(1), glm::vec3(3.0f, 0.499f, -3.0f) ),glm::vec3(1.5f, 1.01f, 0.05f) ),
                    view, proj, program,{ 0.8f, 0.8f, 0.85f, 1 } );




                drawCube( glm::scale( glm::translate( glm::mat4(1), glm::vec3(0, -0.49f, -3) ), glm::vec3(10, 0.9f, 0.05f)),
                    view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });

                drawCube( glm::scale( glm::translate( glm::mat4(1), glm::vec3(0, 2.4875f, -3) ), glm::vec3(10, 0.9f, 0.05f) ),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });


                drawCube( glm::scale( glm::translate( glm::mat4(1),glm::vec3(-5, 2.4875f, 0) ),glm::vec3(0.05f, 0.9f, 4.0f + doorW1) ),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });


                drawCube( glm::scale( glm::translate( glm::mat4(1), glm::vec3(-5, -0.4875f, 0)  ),glm::vec3(0.05f, 0.9f, 4.0f + doorW1) ),
                    view,proj, program, { 0.4f, 0.7f, 0.9f, 0.35f } );


                drawCube(glm::scale( glm::translate( glm::mat4(1),glm::vec3(5, 2.4875f, 0)), glm::vec3(0.05f, 0.9f, 6.0f) ),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });

                drawCube( glm::scale(glm::translate( glm::mat4(1), glm::vec3(5, -0.4875f, 0)  ), glm::vec3(0.05f, 0.9f, 6.0f)),
                    view, proj,program,{ 0.4f, 0.7f, 0.9f, 0.35f });


                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 2.4875f, 3) ), glm::vec3(10.0f, 0.9f, 0.05f) ),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });

                    drawCube( glm::scale( glm::translate(glm::mat4(1), glm::vec3(0, -0.4875f, 3) ), glm::vec3(10.0f, 0.9f, 0.05f) ),
                    view, proj, program,{ 0.4f, 0.7f, 0.9f, 0.35f });

                glm::vec3 windows1[] = {
                    {-3,1.5f,-2.975f},{0,1.5f,-2.975f},{3,1.5f,-2.975f}
                };
                for (int i = 0; i < 3; i++)
                {
                    glm::mat4 win = glm::translate(glm::mat4(1.0f), windows1[i] );
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
                    glm::mat4 lamp = glm::translate(glm::mat4(1.0f), lampPos1[i] );
                    lamp = glm::scale(lamp, glm::vec3(0.1f, 0.4f, 0.05f));
                    drawCube(lamp, view, proj, program, glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));
                }




                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0) + glm::vec3(10, 0, 0)), glm::vec3(10, 0.05f, 6)),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 3, 0) + glm::vec3(10, 0, 0)), glm::vec3(10, 0.05f, 6)),
                    view, proj, program, { 0.6f,0.6f,0.6f,1 });

                float doorW2 = 2.0f, doorH2 = 2.0f, t2 = 0.05f;
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.23, 1, 3) + glm::vec3(10, 0, 0)), glm::vec3(3.5, 2, t2)),
                    view, proj, program, { 0.8f,0.8f,0.85f,1 });
                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(3.5, 1, 3) + glm::vec3(10, 0, 0)), glm::vec3(3, 2, t2)),
                    view, proj, program, { 0.8f,0.8f,0.85f,1 });
                glDepthMask(GL_FALSE);

                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0.26f, 1.0f, 3.0f) + glm::vec3(10, 0, 0)), glm::vec3(3.48f, 2.0f, t2)),
                    view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
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

                drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -0.4875f, 3) + glm::vec3(10, 0, 0)), glm::vec3(10.0f, 0.9f, 0.05f)),
                    view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });

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

                    float doorW3 = 2.0f, doorH3 = 2.0f, t3 = 0.05f;
                    drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.23, 1, 3) + glm::vec3(20, 0, 0)), glm::vec3(3.5, 2, t3)),
                        view, proj, program, { 0.8f,0.8f,0.85f,1 });
                    drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(3.5, 1, 3) + glm::vec3(20, 0, 0)), glm::vec3(3, 2, t3)),
                        view, proj, program, { 0.8f,0.8f,0.85f,1 });
                    glDepthMask(GL_FALSE);

                    drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0.26f, 1.0f, 3.0f) + glm::vec3(20, 0, 0)), glm::vec3(3.48f, 2.0f, t3)),
                        view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
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

                    drawCube(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -0.4875f, 3) + glm::vec3(20, 0, 0)), glm::vec3(10.0f, 0.9f, 0.05f)),
                        view, proj, program, { 0.4f, 0.7f, 0.9f, 0.35f });
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
            };

                    drawRooms();

                    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.05f, 10.0f)),glm::vec3(60.0f, 0.05f, 15.0f)),
                        view, proj, program,{ 0.15f, 0.15f, 0.15f, 1.0f });


                    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 4.5f)),glm::vec3(40.0f, 0.1f, 1.0f)),
                        view, proj, program,{ 0.6f, 0.6f, 0.6f, 1.0f });

                    drawCube(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 18.0f)),glm::vec3(40.0f, 0.1f, 1.0f)),
                        view, proj, program,{ 0.6f, 0.6f, 0.6f, 1.0f } );


                    drawCube(glm::scale( glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 3.51f)),glm::vec3(40.0f, 0.1f, 0.98f)),
                        view, proj, program,{ 0.2f, 0.6f, 0.2f, 0.7f } );

                    drawCube(glm::scale( glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 20.5f)),glm::vec3(40.0f, 0.1f, 4.0f)),
                        view, proj, program,{ 0.2f, 0.6f, 0.2f, 0.7f });

                    for (float x = -6.8f; x <= 32.0f; x += 4.6f)
                    {
                        drawTree(glm::vec3(x, -1.0f, 3.6f), view, proj, program);

                        drawTree(glm::vec3(x, -1.0f, 20.0f), view, proj, program);
                    }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
