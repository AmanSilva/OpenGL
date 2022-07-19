/*
glClearColor
glGetString
keyboard callback
static variables
*/

#include <GLFW/glfw3.h>
#include<iostream>

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int main(void)
{
    

    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Background Changer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, keyboard_callback);

    std::cout << "Company: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Model: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OPENGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "-----\n\n";
    
    glClearColor(0, 1, 0, 1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
       
        glClear(GL_COLOR_BUFFER_BIT);

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

    static bool isGreen = true;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_C && action == GLFW_PRESS) {

        isGreen = !isGreen;
        if (isGreen) {
            std::cout << "Green\n";
            glClearColor(0, 1, 0, 1);
        }
        else {
            glClearColor(1, 1, 0, 1);
            std::cout << "Yellow\n";
        }

    }




}
