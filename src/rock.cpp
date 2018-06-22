#include "rock.h"
#include "main.h"

Rock::Rock(float x, float z, float s, float h) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->s = s;
    this->h = h;
    this->time = 0;
    this->Rocko = Pyramid(x,-h/5.0,z,s,h,COLOR_STONE_GREY);
}

void Rock::draw(glm::mat4 VP) {
    this->Rocko.draw(VP);
}

void Rock::set_position(float dx, float dy, float dz) {
    glm::vec3 dpos(dx,dy,dz);
    this->position = dpos;
    this->Rocko.position = dpos;
}

void Rock::tick() {
    this->Rocko.position.y = 0.1*sin(4*this->time*3.1417/180.0) ;
    this->time++;
    if(this->time > 10000)
    {
        this->time = 0;
    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_sphere_t Rock::bounding_sphere()
{
    float x = this->position.x, y = this->position.y, z = this->position.z, r = this->h/3.0;
    bounding_sphere_t bbox = { x, y, z, r};
    return bbox;
}
