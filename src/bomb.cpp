#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->Shell = Ball(x,y,z,0.1,0.1,0.1,COLOR_BOMB_PINK);

}

void Bomb::draw(glm::mat4 VP) {
    this->Shell.draw(VP);
}

void Bomb::set_position(float dx, float dy, float dz) {
    glm::vec3 dir =  glm::vec3(dx,dy,dz);
    this->position += dir; //= glm::vec3(x, y, z);
    this->Shell.position +=dir;
}

void Bomb::tick() {
     this->set_position(speed_x,0,speed_z);
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Bomb::bounding_box()
{
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 0.1,0.1,0.1};
    return bbox;
}
