/*
Circle (classes, constructors,...)
Resizing
*/

#include <GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void desenha();

class Circle {
private:
    float _r;
    glm::vec2 _pos;
    glm::vec3 _color;

public:
    Circle(glm::vec2 pos, float r);
    void setColor(glm::vec3 color);
    void draw();
};

Circle circ(glm::vec2(0, 0), 5.f);

int main()
{
    

    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Circle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glClearColor(0, 0.15, 0.35, 1);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    float aspect = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10 * aspect, 10 * aspect, -10, 10, 1, -1);
   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
       
        glClear(GL_COLOR_BUFFER_BIT);
        desenha();

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
    
    if(width>=height)
        glOrtho(-10*aspect, 10*aspect, -10, 10, 1, -1);
    else
        glOrtho(-10, 10, -10/aspect, 10/aspect, 1, -1);

}

void desenha()
{ 
    circ.draw();
}

Circle::Circle(glm::vec2 pos, float r):_pos(pos),_r(r)
{
    setColor(glm::vec3(1.f, 1.f, 0.f));
}

void Circle::setColor(glm::vec3 color)
{
    _color = color;
}

void Circle::draw()
{
    glColor3fv(&_color.r);
    glBegin(GL_POLYGON);

    int n{ 100 };
    float maxTheta = 2.f * glm::pi<float>();
    float incr = maxTheta / n;

    for (float theta{ 0 }; theta < maxTheta; theta = theta + incr)
    {
        float x = _pos.x + _r * cos(theta);
        float y = _pos.y + _r * sin(theta);
        glVertex2f(x, y);
    }
    
    glEnd();
}
