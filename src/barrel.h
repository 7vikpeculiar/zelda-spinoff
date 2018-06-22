#include "main.h"
#include "cylinder.h"
#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float z, float s, float h);
    glm::vec3 position;
    glm::vec3 initial_position;

    float rotation;
    float r;
    float h;
    float speed_y;
    float speed_x;
    float speed_z;

    Cylinder Shell;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;

    bounding_sphere_t bounding_sphere();
    bounding_box_t bounding_box();

};
#endif // BARREL_H
