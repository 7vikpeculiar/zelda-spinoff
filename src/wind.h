#include "main.h"
#ifndef WIND_H
#define WIND_H


class Wind {
public:
    Wind() {}
    Wind(float angle, float velocity);

    float speed ;
    float theta;
    int time;
    glm::vec3 direction;
    void set_dir();
    void tick();
 };

#endif // WIND_H
