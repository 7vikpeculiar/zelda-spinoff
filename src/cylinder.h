#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y, float z, float h, float r, color_t color);
    glm::vec3 position;
    glm::vec3 initial_pos;

    float rotation;
    float h;
    float r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // CYLINDER_H

