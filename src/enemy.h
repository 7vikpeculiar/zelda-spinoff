#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, float l, float b, float h, color_t color);
    glm::vec3 position;

    float rotation;
    float l;
    float b;
    float h;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    int time;
    double speed;
    int lives;
    int getLife();
    int setLife();

    bounding_sphere_t bounding_sphere();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
