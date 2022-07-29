/*
Star Creator
*/

#include <GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>
#include<vector>

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

class Star {
private:
    float _r;
    glm::vec2 _pos;
    glm::vec3 _color;
    int _n;
  
    std::vector<glm::vec2> _points;
    std::vector<int> _primes;
    
    void createPoints();
    void createPrimes();
    bool checkPrimes(int x, int y);
    
public:
    Star(glm::vec2 pos, float r, int n);
    void setColor(glm::vec3 color);
    void listPrimes();
    void draw();


};

// Circle circ(glm::vec2(0, 0), 5.f);
Star star1(glm::vec2(-5, 0), 4.f, 30);
Star star2(glm::vec2(5, 0), 4.f, 100);

int main()
{
    
   
    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Star Creator", NULL, NULL);
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

    
  //  circ.setColor(glm::vec3(0, 0, 0));
   
    double value = 0;
    double last_time = 0.0;

    double fps = 10.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        double current_time;
        double dt;
        do {
            current_time = glfwGetTime();
            dt = current_time - last_time;
        } while (dt<1.0/fps);
        
        last_time = current_time;
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
  //  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(width>=height)
        glOrtho(-10*aspect, 10*aspect, -10, 10, 1, -1);
    else
        glOrtho(-10, 10, -10/aspect, 10/aspect, 1, -1);

}

void desenha()
{ 
 //   circ.draw();
    star1.draw();
    star2.draw();
}

bool Star::checkPrimes(int x, int y)
{
    
    if (y == 0) {
        if (x == 1)
            return true;
        else
            return false;
    }
    else
        checkPrimes(y, x%y);
}

void Star::listPrimes()
{
    for (int i{ 0 }; i < _primes.size(); i++) {
        std::cout << _primes[i] << "\n";
    }
}

void Star::draw()
{
    int index = 0;
   
    static int count = 0;
    int jump = _primes[count%_primes.size()];
    count++;

    glColor3fv(&_color.r);
    
    glBegin(GL_LINE_LOOP);

    for (int i{ 0 }; i < _n; i++) {

        glVertex2fv(&_points[index].x);
        index = (index + jump) % _n;
    }
    glEnd();
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

void Star::createPoints()
{
    float maxTheta = 2.f * glm::pi<float>();
    float incr = maxTheta / _n;

    for (float theta{ 0 }; theta < maxTheta; theta = theta + incr)
    {
        float x = _pos.x + _r * cos(theta);
        float y = _pos.y + _r * sin(theta);
        _points.push_back(glm::vec2(x, y));
    }

}

void Star::createPrimes()
{
    
    for (int i{ 2 }; i <= _n / 2; i++) {
        
        if (checkPrimes(_n, i))
            _primes.push_back(i);
    }
}

Star::Star(glm::vec2 pos, float r, int n):_pos(pos), _r(r), _n(n)
{
    setColor(glm::vec3(1, 1, 0));
    createPoints();
    createPrimes();

}

void Star::setColor(glm::vec3 color)
{
    _color = color;
}
