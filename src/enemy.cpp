#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, float l ,float b, float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->l = l;
    this->b = b;
    this->h = h;
    float s = h/2;
    speed = 0;
    this->time = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
       -l/2.0,-b/2.0,-h/2.0, // triangle 1 : begin
       -l/2.0,-b/2, h/2.0,
       -l/2.0, b/2, h/2.0, // triangle 1 : end
        l/2.0, b/2.0,-h/2.0, // triangle 2 : begin
       -l/2.0,-b/2.0,-h/2.0,
       -l/2.0, b/2.0,-h/2.0, // triangle 2 : end
        l/2.0,-b/2.0, h/2.0,
       -l/2.0,-b/2.0,-h/2.0,
        l/2.0,-b/2.0,-h/2.0,
        l/2.0, b/2.0,-h/2.0,
        l/2.0,-b/2.0,-h/2.0,
       -l/2.0,-b/2.0,-h/2.0,
       -l/2.0,-b/2.0,-h/2.0,
       -l/2.0, b/2.0, h/2.0,
       -l/2.0, b/2.0,-h/2.0,
        l/2.0,-b/2.0, h/2.0,
       -l/2.0,-b/2.0, h/2.0,
       -l/2.0,-b/2.0,-h/2.0,
       -l/2.0, b/2.0, h/2.0,
       -l/2.0,-b/2.0, h/2.0,
        l/2.0,-b/2.0, h/2.0,
        l/2.0, b/2.0, h/2.0,
        l/2.0,-b/2.0,-h/2.0,
        l/2.0, b/2.0,-h/2.0,
        l/2.0,-b/2.0,-h/2.0,
        l/2.0, b/2.0, h/2.0,
        l/2.0,-b/2.0, h/2.0,
        l/2.0, b/2.0, h/2.0,
        l/2.0, b/2.0,-h/2.0,
       -l/2.0, b/2.0,-h/2.0,
        l/2.0, b/2.0, h/2.0,
       -l/2.0, b/2.0,-h/2.0,
       -l/2.0, b/2.0, h/2.0,
        l/2.0, b/2.0, h/2.0,
       -l/2.0, b/2.0, h/2.0,
        l/2.0,-b/2.0, h/2.0,

        -s/2.0, b/2.0, -s/2.0,
        -s/2.0, b/2.0,  s/2.0,
         s/2.0, b/2.0,  s/2.0,
        -s/2.0, b/2.0, -s/2.0,
         s/2.0, b/2.0, -s/2.0,
         s/2.0, b/2.0,  s/2.0, //Base

        -s/2.0, b/2.0 ,-s/2.0,
        -s/2.0, b/2.0,  s/2.0,
         0,     b,     0,

        -s/2.0, b/2.0,  s/2.0,
         s/2.0, b/2.0,  s/2.0,
         0,     b,     0,

         s/2.0, b/2.0,  s/2.0,
         s/2.0, b/2.0, -s/2.0,
         0,     b,     0,

         s/2.0, b/2.0,   -s/2.0,
        -s/2.0, b/2.0,   -s/2.0,
         0,     b,     0

    };
     this->object = create3DObject(GL_TRIANGLES, 18*3, vertex_buffer_data, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    //glm::vec3 origin = glm::vec3(0,0,0);
    //glm::mat4 translate_to_original_pos = glm::translate(this->initial_pos);
    //glm::mat4 translate_back_from_inital_pos = glm::translate(-this->initial_pos);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 origin_move = glm::translate(origin);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 1, 0));
    //glm::mat4 new_rotate   =  translate * rotate * origin_move ;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::set_position(float dx, float dy, float dz) {
    glm::vec3 dpos(dx, dy, dz);
    this->position += dpos;
}

void Enemy::tick() {
    if(this->time > 0)
    {
        this->time--;
    }

    //this->rotation += speed;
    //this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_sphere_t Enemy::bounding_sphere() {
    float x = this->position.x, y = this->position.y, z = this->position.z, r = 1;
    bounding_sphere_t bbox = { x, y, z, r};
    return bbox;
}

bounding_box_t Enemy::bounding_box()
{
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float l = this->l, b = this->b, h = this->h;
    bounding_box_t bbox = {x,y,z,l,b,h};
    return bbox;
}

int Enemy::getLife()
{
    return this->lives;
}

int Enemy::setLife()
{
    this->lives -= 1;
}
