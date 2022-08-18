#include "Primitive.h"
#include "MyColors.h"
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include<glm/gtc/type_ptr.hpp>

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

float Sphere::generateRandom(float minimum, float maximum)
{
    float n = maximum - minimum;
    float t = (float)rand() / RAND_MAX;
    return minimum + t * n;
}

Sphere::Sphere()
{
    _radius = 0.f;
    _nStacks = 0.f;
    _nSectors = 0.f;
    _id = 0;
    _pos = glm::vec3(0, 0, 0);
    _rotateX = false;
    _rotateY = false;
    _rotateZ = false;
    _fps = generateRandom(30.f, 60.f);
}

Sphere::Sphere(float radius, int nStacks, int nSectors, glm::vec3 pos)
{
    _rotateX = false;
    _rotateY = false;
    _rotateZ = false;
    _fps = generateRandom(30.f, 60.f);
    create(radius, nStacks, nSectors, pos);

}

void Sphere::create(float radius, int nStacks, int nSectors, glm::vec3 pos)
{
 //   _id = glGenLists(1);
    _radius = radius;
    _nStacks = nStacks;
    _nSectors = nSectors;
    _pos = glm::vec3(pos.x, pos.y, pos.z);

    float inittheta{0};
    float initphi{-myPI/2};
    float theta{inittheta};
    float phi{initphi};

    double deltaphi = myPI/_nStacks;
    double deltatheta = 2*myPI / _nSectors;


    for (int stack{}; stack <= _nStacks; stack++) {
        std::vector<unsigned int> points_in_stack;

        phi = initphi + stack * deltaphi;
        float y = _radius * sin(phi);
        for (int sector{}; sector < _nSectors; sector++) {
            theta = inittheta + sector * deltatheta;
            float x = _radius * cos(phi) * sin(theta);
            float z = _radius * cos(phi) * cos(theta);
            _points.push_back(glm::vec3(x, y, z));
            unsigned int index{ _points.size() - 1 };
            points_in_stack.push_back(index);
        }

        indices.push_back(points_in_stack);

    }

 //   std::cout << "Number of points: " << _points.size() << std::endl;


}

void Sphere::draw(double dt)
{
    float dtheta = _fps * dt;
    static float angle{ 0.f };
    glPushMatrix();
    glTranslatef(_pos.x, _pos.y, _pos.z);
    if (_rotateX)
        glRotatef(angle, 1.f, 0.f, 0.f);
    if (_rotateY)
        glRotatef(angle, 0.f, 1.f, 0.f);
    if (_rotateZ)
        glRotatef(angle, 0.f, 0.f, 1.f);
    angle += dtheta;

    if (angle >= 360) {
        angle = 0.f;
    }


  /*  glPointSize(3.f);
    glBegin(GL_POINTS);
    for (glm::vec3 v : _points) {
        glVertex3fv(&v.x);
    }
    glEnd(); */
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glBegin(GL_TRIANGLE_STRIP);
    for (int i{}; i < indices.size()-1; i++) {
        if (i % 3 == 0)
            glColor3fv(glm::value_ptr(FIREBRICK));
        else if (i % 3 == 1)
            glColor3fv(glm::value_ptr(GREEN));
        else
            glColor3fv(glm::value_ptr(BROWN)); 
       glBegin(GL_TRIANGLE_STRIP);
        for (int j{}; j < indices[i].size(); j++) {
            int index = indices[i][j];
            glVertex3fv(&_points[index].x);
            index = indices[i + 1][j];
            glVertex3fv(&_points[index].x);

            if (j == indices[i].size()-1) {
                int index = indices[i][0];
                glVertex3fv(&_points[index].x);
                index = indices[i + 1][0];
                glVertex3fv(&_points[index].x);
            }
        }
    }
    glEnd();

    glPopMatrix();

}

Terrain::Terrain()
{
    _id = 0;
    _limit = 0;
}

Terrain::Terrain(float limit)
{
    _id = 0;
    create(limit);
}

void Terrain::create(float limit)
{
    _id = glGenLists(1);
    _limit = limit;
    
    float y = -0.5;
    float incr = 1.f;

    glNewList(_id, GL_COMPILE);
    glColor3fv(glm::value_ptr(WHITE));
    glBegin(GL_LINES);
    for (float x{-limit}; x <= limit; x+=incr) {
        glVertex3f(x, y, limit);
        glVertex3f(x, y, -limit);
    }
    for (float z{-limit}; z <= limit; z+=incr) {
        glVertex3f(-limit, y, z);
        glVertex3f(limit, y, z);
    }
    glEnd();
    glEndList();
}

void Terrain::draw()
{
    glCallList(_id);
}
