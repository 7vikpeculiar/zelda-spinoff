#include "wind.h"
#include <GLFW/glfw3.h>

Wind::Wind(float angle, float velocity) {
    this->theta = angle;
    this->speed = velocity;
    this->direction = glm::vec3(velocity*sin(angle),0,velocity*cos(angle));
    this->time = 100;
}

void Wind::set_dir()
{
    this->direction = glm::vec3(this->speed*sin(this->theta),0,this->speed*cos(this->theta));
}

void Wind::tick()
{
    if(this->time > 0)
    {
        this->time--;
    }
    if(this->time == 0)
    {
        this->speed = 0;
        this->set_dir();
    }
}
