/*
Star Creator
*/

#include<Windows.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>
#include<vector>
#include<GL/GLU.h>
#include"Primitive.h"
#include"MyColors.h"
#include "Camera.h"


void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void desenha(double dt);
void init(GLFWwindow* window);
float generateRandom(float minimum, float maximum);



Cube cube[2];
Sphere sphere1;
Terrain terrain;
const int n_objects = 301;
std::vector<Object*> objects;
Camera camera(glm::vec3(0, 0, 0));



int main()
{


    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Terrain with Objects", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    
    init(window);

    double last_time = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        double current_time = glfwGetTime();
        double dt = current_time - last_time;
        last_time = current_time;
    
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        desenha(dt);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    for (int i{ 0 }; i < n_objects; i++) {
        delete objects[i];
    }

    glfwTerminate();
    return 0;
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.forth();
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.retreat();
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.left();
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.right();




}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstTime = true;
    static double lastCursorPosX = 0.0;
    float dx;

    if (firstTime) {
        dx = 0.f;
        lastCursorPosX = xpos;
        firstTime = false;
    }

    dx = xpos - lastCursorPosX;
    lastCursorPosX = xpos;
    camera.update(0.5*dx);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{


    glViewport(0, 0, width, height);

    float aspect = (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, aspect, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);

}

void desenha(double dt)
{
    glLoadIdentity();

    camera.activate();
/*    cube[0].draw(dt);
    cube[1].draw(dt);
    sphere1.draw(dt);
    terrain.draw();*/
    objects[0]->draw();
    for (int i{1}; i < n_objects; i++) {
        objects[i]->draw(dt);
    }
}





void init(GLFWwindow* window) {

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMaximizeWindow(window);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0.15, 0.35, 1);


    objects.push_back(new Terrain(350));

    for (int i{1}; i < n_objects; i++) {
        float _rnumber = static_cast<float>(rand()) / RAND_MAX;
        if (_rnumber < 0.5) {
            objects.push_back(new Cube(generateRandom(0.5f, 5.f), glm::vec3(generateRandom(-350.f, 350.f), generateRandom(4.f, 20.f), generateRandom(-350.f, 350.f))));
            objects[i]->rotatex();
            objects[i]->rotatey();
            objects[i]->rotatez();
        }
        else {
            objects.push_back(new Sphere(generateRandom(0.5f, 5.f), 50, 50, glm::vec3(generateRandom(-350.f, 350.f), generateRandom(6.f, 20.f), generateRandom(-350.f, 350.f))));
            objects[i]->rotatex();
            objects[i]->rotatey();
            objects[i]->rotatez();
        }
    }


    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    double aspect = (double)w / (double)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);

    
}

float generateRandom(float minimum, float maximum)
{
    float n = maximum - minimum;
    float t = (float)rand() / RAND_MAX;
    return minimum + t * n;
}
