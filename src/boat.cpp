#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->l = 0;
    this->b = 0;
    this->h = 0;// Useful for bounding box // DOnt delete
    this->speed = 0.1;
    this->speed_y = 0;
    this->ground = 0.04;
    this->time = 0;
    this->gravity = 0.01;
    this->radius = 0.3;
    this->Floor = Ball(0,0,0,0.5,0.2,0.5,COLOR_BOAT_FLOOR);
    this->Mast = Ball(0,0.25,0,0.04,0.5,0.04,COLOR_BOAT_MAST);
    this->Flag = Ball(0.09,0.3,0,0.2,0.4,0.05,COLOR_BOAT_FLAG);
    this->Rudder = Ball(0,0,0.3,0.15,0.18,0.3,COLOR_BOAT_RUDDER);
    this->Cannon = Ball(0,0.1,-0.2,0.1,0.2,0.3,COLOR_BLACK);

}

void Boat::draw(glm::mat4 VP) {
    //this->set_position(this->position.x,this->position.y,this->position.z);
    //glm::vec3 pos = this->position;
    /* float temp = this->rotation;
    Floor.rotation = temp;
    Rudder.rotation = temp;
    Mast.rotation = temp;
    Flag.rotation = temp;*/

    this->Floor.draw(VP);
    this->Rudder.draw(VP);
    this->Mast.draw(VP);
    this->Flag.draw(VP);
    this->Cannon.draw(VP);
}

void Boat::set_position(float dx, float dy, float dz) {
    glm::vec3 dpos = glm::vec3(dx,dy,dz);
    this->position += dpos;
    this->Floor.position += dpos ;
    this->Mast.position += dpos;
    this->Rudder.position += dpos;
    this->Flag.position += dpos;
    this->Cannon.position += dpos;
}

void Boat::set_rotation(float dm) {
    //this->position = glm::vec3(x, y, z);
    //this->Floor.set_position(this->position.x + this->Floor.position.x, this->position.y +  this->Floor.position.y,  this->position.z + this->Floor.position.z);
    //this->Flag.set_position(this->position.x + this->Flag.position.x, this->position.y +  this->Flag.position.y,  this->position.z + this->Flag.position.z);
    //this->Rudder.set_position(this->position.x + this->Rudder.position.x,  this->position.y + this->Rudder.position.y , this->position.z + this->Rudder.position.z);
    //this->Mast.set_position(this->position.x + this->Mast.position.x, this->position.y +  this->Mast.position.y,  this->position.z + this->Mast.position.z);
    //glm::vec3 dpos = glm::vec3(dx,dy,dz);
    this->rotation += dm;
    this->Floor.rotation += -dm ;
    this->Mast.rotation += -dm;
    this->Rudder.rotation += -dm;
    //this->Flag.rotation += dm;
    this->Cannon.rotation += -dm;
}

void Boat::tick() {
    if(this->speed < 0.1)
    {
        this->speed = 0.1;
    }
    else if(this->speed > 0.1)
    {
        this->speed -= 0.001;
    }

    //this->position.z += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    if(this->position.y > this->ground)
       {
            this->set_position(0,speed_y,0);
            this->speed_y -= this->gravity;
       }

       if(this->position.y < this->ground) // and not in water column
       {
           this->set_position(0, this->ground - this->position.y,0);

       }

}

bounding_sphere_t Boat::bounding_sphere() {
    float x = this->position.x, y = this->position.y, z = this->position.z, r = this->radius;
    bounding_sphere_t bbox = { x, y, z, r};
    return bbox;
}

bounding_box_t Boat::bounding_box()
{
    float x = this->position.x, y = this->position.y, z = this->position.z;
    //float l = this->l, b = this->b, h = this->h;
    bounding_box_t bbox = {x,y,z,0.5,0.5,0.5};
    return bbox;
}
