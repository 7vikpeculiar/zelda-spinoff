#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float z, float h, float r) {
    this->position = this->initial_position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->r = r;
    this->h = h;
    this->speed_y = 0;
    this->speed_x = 0;
    this->speed_z = 0;

    this->Shell = Cylinder(x,0,z,h,r,COLOR_STONE_GREY);
}

void Barrel::draw(glm::mat4 VP) {
    this->Shell.draw(VP);
}

void Barrel::set_position(float dx, float dy, float dz) {
    //this->position = glm::vec3(x, y, z);
    glm::vec3 dpos = glm::vec3(dx,dy,dz);
    this->position += dpos;
    this->Shell.position += dpos;
}

void Barrel::tick() {
    //this->rotation += speed;
    this->set_position(this->speed_x,this->speed_y,this->speed_z);
    // this->position.x -= speed;
     //this->position.y += this->speed_y;
}

bounding_sphere_t Barrel::bounding_sphere()
{
    float x = this->position.x, y = this->position.y, z = this->position.z, r = this->h/3.0;
    bounding_sphere_t bbox = { x, y, z, r};
    return bbox;
}

bounding_box_t Barrel::bounding_box()
{
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float l = 2* this->r , h = 2*this->r, b = this->h;
    bounding_box_t bbox = { x, y, z, l,b,h};
    return bbox;
}



