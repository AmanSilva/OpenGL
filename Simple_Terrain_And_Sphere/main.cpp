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


void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void desenha(double dt);
void init(GLFWwindow* window);



Cube cube[2];
Sphere sphere1;
Terrain terrain;




int main()
{


    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Cube", NULL, NULL);
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

    
    glfwTerminate();
    return 0;
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);




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
 //   rect.draw();
    glLoadIdentity();
    cube[0].draw(dt);
    cube[1].draw(dt);
    sphere1.draw(dt);
    terrain.draw();

    /*glTranslatef(10.f, 0.f, -35.f);
    glRotatef(20.f, 1.f, 0.f, 0.f);
    glRotatef(-20.f, 0.f, 1.f, 0.f);
    cube.draw();*/
}





void init(GLFWwindow* window) {

    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0.15, 0.35, 1);

    cube[0].create(5.f, glm::vec3(25.f, 10.f, -75.f));
    cube[0].rotatey();
    cube[0].rotatez();

    cube[1].create(5.f, glm::vec3(-25.f, 10.f, -100.f));
    cube[1].rotatex();
    cube[1].rotatey();

    sphere1.create(8.f, 100, 100, glm::vec3(0.f, 10.f, -90.f));
    sphere1.rotatex();
    sphere1.rotatey();
    sphere1.rotatez();

    terrain.create(350);


    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    double aspect = (double)w / (double)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);

    
}
