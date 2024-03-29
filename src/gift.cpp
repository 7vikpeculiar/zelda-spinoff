#include "gift.h"
#include "main.h"

Gift::Gift(float x, float y, float z, float s, float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->s = s;
    this->h = h;
    this->rot_speed = 5;
    // A Gift has 10 faces
    GLfloat vertex_buffer_data[] = {
       -s/2.0, 0 ,-s/2.0,
       -s/2.0, 0,  s/2.0,
        0,     h,     0,

       -s/2.0, 0,  s/2.0,
        s/2.0, 0,  s/2.0,
        0,     h,     0,

        s/2.0, 0,  s/2.0,
        s/2.0, 0, -s/2.0,
        0,     h,     0,

        s/2.0, 0,   -s/2.0,
       -s/2.0, 0,   -s/2.0,
        0,     h,     0,

        -s/2.0, 0 ,-s/2.0,
        -s/2.0, 0,  s/2.0,
         0,     -h,     0,

        -s/2.0, 0,  s/2.0,
         s/2.0, 0,  s/2.0,
         0,     -h,     0,

         s/2.0, 0,  s/2.0,
         s/2.0, 0, -s/2.0,
         0,     -h,     0,

         s/2.0, 0,   -s/2.0,
        -s/2.0, 0,   -s/2.0,
         0,     -h,     0
    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Gift::tick() {
    this->rotation += this->rot_speed;

}

bounding_box_t Gift::bounding_box()
{
    float x = this->position.x, y = this->position.y, z = this->position.z;
    //float l = this->s, b = this->h, h
     float h = this->h; s = this->s;
    bounding_box_t bbox = {x,y,z,s,h,s};
    return bbox;
}
