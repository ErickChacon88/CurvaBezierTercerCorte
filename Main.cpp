#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ======================================================
// CAMARA
// ======================================================

glm::vec3 cameraPos(0.0f, 3.0f, 12.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

bool cinematicMode = true;

float yaw = -90.0f;
float pitch = 0.0f;

float lastX = 640.0f;
float lastY = 360.0f;

bool firstMouse = true;
bool cPressed = false;

// ======================================================
// BEZIER
// ======================================================

glm::vec3 P0(-10.0f, 0.0f, 0.0f);
glm::vec3 P1(-5.0f, 8.0f, 10.0f);
glm::vec3 P2(5.0f, -6.0f, -10.0f);
glm::vec3 P3(10.0f, 2.0f, 0.0f);

glm::vec3 bezier(float t)
{
    float u = 1.0f - t;

    return
        u * u * u * P0 +
        3.0f * u * u * t * P1 +
        3.0f * u * t * t * P2 +
        t * t * t * P3;
}

// ======================================================
// MOUSE
// ======================================================

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!cinematicMode)
    {
        if (firstMouse)
        {
            lastX = (float)xpos;
            lastY = (float)ypos;
            firstMouse = false;
        }

        float xoffset = (float)xpos - lastX;
        float yoffset = lastY - (float)ypos;

        lastX = (float)xpos;
        lastY = (float)ypos;

        float sensitivity = 0.08f;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFront = glm::normalize(direction);
    }
}

// ======================================================
// PELOTA (ESFERA)
// ======================================================

std::vector<float> shipVertices;

void generateSphere()
{
    int stacks = 16;
    int slices = 16;
    float radius = 0.7f;

    for (int i = 0; i < stacks; i++)
    {
        float lat0 = glm::pi<float>() * (-0.5f + (float)i / stacks);
        float lat1 = glm::pi<float>() * (-0.5f + (float)(i + 1) / stacks);

        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        for (int j = 0; j < slices; j++)
        {
            float lng0 = 2 * glm::pi<float>() * (float)j / slices;
            float lng1 = 2 * glm::pi<float>() * (float)(j + 1) / slices;

            glm::vec3 p1(cos(lng0) * zr0, sin(lng0) * zr0, z0);
            glm::vec3 p2(cos(lng1) * zr0, sin(lng1) * zr0, z0);
            glm::vec3 p3(cos(lng1) * zr1, sin(lng1) * zr1, z1);
            glm::vec3 p4(cos(lng0) * zr1, sin(lng0) * zr1, z1);

            shipVertices.insert(shipVertices.end(), {
                p1.x * radius, p1.y * radius, p1.z * radius,
                p2.x * radius, p2.y * radius, p2.z * radius,
                p3.x * radius, p3.y * radius, p3.z * radius,

                p1.x * radius, p1.y * radius, p1.z * radius,
                p3.x * radius, p3.y * radius, p3.z * radius,
                p4.x * radius, p4.y * radius, p4.z * radius
                });
        }
    }
}

// ======================================================
// MAIN
// ======================================================

int main()
{
    srand((unsigned int)time(0));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(1280, 720, "SCI-FI BEZIER BALL", NULL, NULL);

    if (!window) return -1;

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL()) return -1;

    glEnable(GL_DEPTH_TEST);

    Shader shader("default.vert", "default.frag");

    generateSphere();

    VAO shipVAO;
    shipVAO.Bind();
    VBO shipVBO(shipVertices.data(), shipVertices.size() * sizeof(float));
    shipVAO.LinkVBO(shipVBO, 0);
    shipVAO.Unbind();

    std::vector<float> stars;

    for (int i = 0; i < 15000; i++)
    {
        float radiusS = 50.0f + (rand() % 1200);
        float theta = ((rand() % 3600) / 10.0f);
        float phi = ((rand() % 3600) / 10.0f);

        float x = radiusS * sin(glm::radians(phi)) * cos(glm::radians(theta));
        float y = radiusS * cos(glm::radians(phi));
        float z = radiusS * sin(glm::radians(phi)) * sin(glm::radians(theta));

        stars.push_back(x);
        stars.push_back(y);
        stars.push_back(z);
    }

    VAO starsVAO;
    starsVAO.Bind();
    VBO starsVBO(stars.data(), stars.size() * sizeof(float));
    starsVAO.LinkVBO(starsVBO, 0);
    starsVAO.Unbind();

    std::vector<float> curve;

    for (float t = 0.0f; t <= 1.0f; t += 0.0015f)
    {
        glm::vec3 p = bezier(t);
        curve.push_back(p.x);
        curve.push_back(p.y);
        curve.push_back(p.z);
    }

    VAO curveVAO;
    curveVAO.Bind();
    VBO curveVBO(curve.data(), curve.size() * sizeof(float));
    curveVAO.LinkVBO(curveVBO, 0);
    curveVAO.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cPressed)
        {
            cinematicMode = !cinematicMode;
            cPressed = true;
            firstMouse = true;
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
            cPressed = false;

        float t = fmod(glfwGetTime() * 0.03f, 1.0f);

        glm::vec3 shipPos = bezier(t);
        glm::vec3 futurePos = bezier(fmod(t + 0.01f, 1.0f));

        glm::vec3 forward = glm::normalize(futurePos - shipPos);

        if (cinematicMode)
        {
            cameraPos = shipPos - forward * 7.0f + glm::vec3(0, 2, 0);
            cameraFront = glm::normalize(shipPos - cameraPos);
        }
        else
        {
            float speed = 0.25f;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += speed * cameraFront;

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= speed * cameraFront;

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 5000.0f);

        glm::mat4 camMatrix = proj * view;

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(camMatrix));

        // ESTRELLAS
        glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), 1, 1, 1, 1);

        glm::mat4 identity = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(identity));

        starsVAO.Bind();
        glPointSize(2.0f);
        glDrawArrays(GL_POINTS, 0, stars.size() / 3);

        // CURVA
        glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), 0.0f, 0.7f, 1.0f, 1.0f);

        curveVAO.Bind();
        glLineWidth(3.0f);
        glDrawArrays(GL_LINE_STRIP, 0, curve.size() / 3);

        // PELOTA CON COLOR CROMÁTICO
        float r = (sin(glfwGetTime() * 2.0f) * 0.5f + 0.5f);
        float g = (sin(glfwGetTime() * 2.0f + 2.0f) * 0.5f + 0.5f);
        float b = (sin(glfwGetTime() * 2.0f + 4.0f) * 0.5f + 0.5f);

        glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), r, g, b, 1.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), shipPos);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        shipVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, shipVertices.size() / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}