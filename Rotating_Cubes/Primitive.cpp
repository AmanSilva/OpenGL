#include "Primitive.h"
#include "MyColors.h"
#include<GLFW/glfw3.h>
#include<iostream>

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

float Cube::generateRandom(float minimum, float maximum)
{
    float n = maximum - minimum;
    float t = (float)rand() / RAND_MAX;
    return minimum+t*n;
}

Cube::Cube()
{
    _side = 0.f;
    _id = 0;
    _fps = 0.f;
    _pos = glm::vec3(0, 0, 0);
    _rotateX = false;
    _rotateY = false;
    _rotateZ = false;
    _fps = generateRandom(30.f, 60.f);
}

Cube::Cube(float side, glm::vec3 pos)
{
    _rotateX = false;
    _rotateY = false;
    _rotateZ = false;
    _fps = generateRandom(30.f, 60.f);
    create(side, pos);
}



Cube::~Cube()
{
    glDeleteLists(_id, 1);
}

void Cube::create(float side, glm::vec3 pos)
{
    _id = glGenLists(1);
    _side = side;
    _pos = glm::vec3(pos.x, pos.y, pos.z);

    float a = _side / 2;

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

    glNewList(_id, GL_COMPILE);
    frontface.draw();
    backface.draw();
    topface.draw();
    rightface.draw();
    leftface.draw();
    bottomface.draw();
    glEndList();
}

void Cube::draw(double dt)
{
    float dtheta = _fps * dt;
    static float angle{0.f};
    glPushMatrix();
    glTranslatef(_pos.x, _pos.y, _pos.z);
    if (_rotateX)
        glRotatef(angle, 1.f, 0.f, 0.f);
    if(_rotateY)
        glRotatef(angle, 0.f, 1.f, 0.f);
    if (_rotateZ)
        glRotatef(angle, 0.f, 0.f, 1.f);
    angle += dtheta;

    if (angle>=360) {
        angle = 0.f;
    }
    glCallList(_id);
    glPopMatrix();
}
