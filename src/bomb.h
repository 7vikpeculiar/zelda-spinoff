#include "main.h"
#include "ball.h"
#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    Ball Shell;

    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed_x;
    double speed_z;
    bounding_box_t bounding_box();

};

#endif // BOMB_H
