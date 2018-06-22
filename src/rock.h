#include "main.h"
#include "pyramid.h"
#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float z, float s, float h);
    glm::vec3 position;
    float rotation;
    float s;
    float h;
    int time;
    Pyramid Rocko;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;

    bounding_sphere_t bounding_sphere();
};
#endif // ROCK_H
