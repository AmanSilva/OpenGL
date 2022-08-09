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
#include"MyColors.h"

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void desenha();
void desenhaCubo(unsigned int id, float side);
void init(GLFWwindow* window);

class Quad {
private:
    glm::vec3 _color;
    std::vector<glm::vec3> _points;

public:
    Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color);
    void draw();

};

Quad rect(
    glm::vec3(-5, 5, 0), 
    glm::vec3(-5, -5, 0), 
    glm::vec3(5, -5, 0), 
    glm::vec3(5, 5, 0), 
    YELLOW 
);

unsigned int cubeID;



int main()
{


    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Cube", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    
    init(window);

   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
    
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        desenha();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteLists(cubeID, 1);
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

void desenha()
{
 //   rect.draw();
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-10.f, 0.f, -35.f);
    glRotatef(20.f, 1.f, 0.f, 0.f);
    glRotatef(-20.f, 0.f, 1.f, 0.f);
    glScalef(1.f, 0.25, 1.f);
    glCallList(cubeID);
    glPopMatrix();

    glTranslatef(10.f, 0.f, -35.f);
    glRotatef(20.f, 1.f, 0.f, 0.f);
    glRotatef(-20.f, 0.f, 1.f, 0.f);
    glCallList(cubeID);
}

void desenhaCubo(unsigned int id, float side) {
    float a = side / 2;

    //Front Face Vertices
    glm::vec3 p1(-a, a, a);
    glm::vec3 p2(-a, -a, a);
    glm::vec3 p3(a, -a, a);
    glm::vec3 p4(a, a, a);

    //Back Face Vertices
    glm::vec3 p5(a, a, -a);
    glm::vec3 p6(a, -a, -a);
    glm::vec3 p7(-a, -a, -a);
    glm::vec3 p8(-a, a, -a);



    Quad frontface(p1, p2, p3, p4, YELLOW);
    Quad backface(p5, p6, p7, p8, RED);
    Quad topface(p1, p4, p5, p8, FIREBRICK);
    Quad rightface(p4, p3, p6, p5, GREEN);
    Quad leftface(p1, p8, p7, p2, NAVAJOWHITE);
    Quad bottomface(p2, p7, p6, p3, GREY);

    glNewList(id, GL_COMPILE);
    frontface.draw();
    backface.draw();
    topface.draw();
    rightface.draw();
    leftface.draw();
    bottomface.draw();
    glEndList();
}

Quad::Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color)
{
    _points.push_back(p1);
    _points.push_back(p2);
    _points.push_back(p3);
    _points.push_back(p4);
    _color = color;
}

void Quad::draw()
{
    glColor3fv(&_color.r);
    glBegin(GL_QUADS);
    for (int i{}; i < _points.size(); i++) {
        glVertex3fv(&_points[i].x);
    }
    glEnd();
}

void init(GLFWwindow* window) {

    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0.15, 0.35, 1);

    cubeID = glGenLists(1);
    desenhaCubo(cubeID, 5.f);


    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    double aspect = (double)w / (double)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);

    
}
