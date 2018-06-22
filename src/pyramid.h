#include "main.h"

#ifndef PYRAMID_H
#define PYRAMID_H


class Pyramid {
public:
    Pyramid() {}
    Pyramid(float x, float y, float z, float s, float h, color_t color);
    glm::vec3 position;
    float rotation;
    float s;
    float h;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // PYRAMID_H
