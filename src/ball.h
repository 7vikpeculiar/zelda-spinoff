#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, float l, float b, float h, color_t color);
    glm::vec3 position;
    glm::vec3 initial_pos;
    float t;
    float rotation;
    float l;
    float b;
    float h;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
