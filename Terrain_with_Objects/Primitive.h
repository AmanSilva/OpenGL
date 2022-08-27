#pragma once
#include<glm/glm.hpp>
#include<vector>

#define myPI 3.14159265359

class Object {
protected:
    unsigned int _id;
    glm::vec3 _pos;
    float _fps;
    bool _rotateX, _rotateY, _rotateZ;
    float _angle;
    
    float generateRandom(float minimum, float maximum);

public:
    Object();
    Object(glm::vec3 pos);
    ~Object();
    void draw(double dt=0);
    inline void rotatex() { _rotateX = true; }
    inline void rotatey() { _rotateY = true; }
    inline void rotatez() { _rotateZ = true; }
};

class Quad {
private:
    glm::vec3 _color;
    std::vector<glm::vec3> _points;

public:
    Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color);

    void draw();

};

class Cube : public Object {
private:
    float _side;

public:
    Cube();
    Cube(float side, glm::vec3 pos);

    void create(float side, glm::vec3 pos);
};

class Sphere : public Object {
private:
    float _radius;
    int _nStacks;
    int _nSectors;
    std::vector<glm::vec3> _points;
    std::vector<std::vector<unsigned int>> indices;

public:
    Sphere();
    Sphere(float radius, int nStacks, int nSectors, glm::vec3 pos);

    void create(float radius, int nStacks, int nSectors, glm::vec3 pos);
};

class Terrain : public Object {
private:
    float _limit;

public:
    Terrain();
    Terrain(float limit);

    void create(float limit);
    void draw();

};


