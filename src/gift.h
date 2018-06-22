#include "main.h"

#ifndef GIFT_H
#define GIFT_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y, float z, float s, float h, color_t color);
    glm::vec3 position;
    float rotation;
    float s;
    float h;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    int type;
    float rot_speed;
    bounding_box_t bounding_box();

private:
    VAO *object;

};

#endif // GIFT_H
