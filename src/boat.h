#include "main.h"
#include "ball.h"
#ifndef BOAT_H
#define BOAT_H


class Boat{
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float l;
    float b;
    float h;
    float radius;
    float time;

    Ball Floor;
    Ball Mast;
    Ball Flag;
    Ball Rudder;
    Ball Cannon;

    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void set_rotation(float dm);
    bounding_sphere_t bounding_sphere();
    bounding_box_t bounding_box();

    float ground;
    float gravity;

    double speed;
    double speed_y;
private:
    VAO *object;
};

#endif // BOAT_H

