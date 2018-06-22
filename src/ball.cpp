#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, float l ,float b, float h, color_t color) {
    this->position = this->initial_pos = glm::vec3(x, y, z);
    this->rotation = 0;
    this->l = l;
    this->b = b;
    this->h = h;
    this->t = 0;
    speed = 0;
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
        l/2.0,-b/2.0, h/2.0
    };
     this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    //glm::vec3 origin = glm::vec3(0,0,0);
    glm::mat4 translate_to_original_pos = glm::translate(this->initial_pos);
    glm::mat4 translate_back_from_inital_pos = glm::translate(-this->initial_pos);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 origin_move = glm::translate(origin);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 1, 0));
    //glm::mat4 new_rotate   =  translate * rotate * origin_move ;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * translate_back_from_inital_pos * rotate * translate_to_original_pos );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    //this->rotation += speed;
    //this->t++;
    //this->position.y = 0.000005*sin(t/100.0);
    // this->position.y -= speed;
}

