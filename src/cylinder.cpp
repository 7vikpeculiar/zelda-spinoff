#include "cylinder.h"
#include "main.h"

Cylinder::Cylinder(float x, float y, float z, float h ,float r ,color_t color) {
    this->position = this->initial_pos = glm::vec3(x, y, z);
    this->rotation = 0;
    this->h = h;
    speed = 0;
    int sides = 361;
    int array_iter = 0, theta = 0;
    float radi = this->r = r;
    GLfloat vertex_buffer_data[13500];

    for(int count = 0; count<= sides; count++)
    {
       vertex_buffer_data[array_iter]=0.0;
       vertex_buffer_data[array_iter+1]=h/2.0;
       vertex_buffer_data[array_iter+2]=0.0;
       vertex_buffer_data[array_iter+3]=radi *cos(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+4]=h/2.0;
       vertex_buffer_data[array_iter+5]=radi *sin(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+6]=radi*cos(M_PI*(theta+1)/180.0);
       vertex_buffer_data[array_iter+7]=h/2.0;
       vertex_buffer_data[array_iter+8]=radi*sin(M_PI*(theta+1)/180.0);

       array_iter+=9;

       vertex_buffer_data[array_iter]=0.0;
       vertex_buffer_data[array_iter+1]=-h/2.0;
       vertex_buffer_data[array_iter+2]=0.0;
       vertex_buffer_data[array_iter+3]=radi *cos(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+4]=-h/2.0;
       vertex_buffer_data[array_iter+5]=radi *sin(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+6]=radi*cos(M_PI*(theta+1)/180.0);
       vertex_buffer_data[array_iter+7]=-h/2.0;
       vertex_buffer_data[array_iter+8]=radi*sin(M_PI*(theta+1)/180.0);

       array_iter+=9;

       vertex_buffer_data[array_iter]= radi *cos(M_PI*(theta/180.0));
       vertex_buffer_data[array_iter+1]=h/2.0;
       vertex_buffer_data[array_iter+2]=radi *sin(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+3]=radi *cos(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+4]=-h/2.0;
       vertex_buffer_data[array_iter+5]=radi *sin(M_PI*theta/180.0);
       vertex_buffer_data[array_iter+6]=radi*cos(M_PI*(theta+1)/180.0);
       vertex_buffer_data[array_iter+7]=-h/2.0;
       vertex_buffer_data[array_iter+8]=radi*sin(M_PI*(theta+1)/180.0);

       array_iter += 9;

       vertex_buffer_data[array_iter]  =radi*cos(M_PI*(theta+1)/180);
       vertex_buffer_data[array_iter+1]=-h/2.0;
       vertex_buffer_data[array_iter+2]=radi*sin(M_PI*(theta+1)/180);
       vertex_buffer_data[array_iter+3]=radi *cos(M_PI*theta/180);
       vertex_buffer_data[array_iter+4]=h/2.0;
       vertex_buffer_data[array_iter+5]=radi *sin(M_PI*theta/180);
       vertex_buffer_data[array_iter+6]=radi*cos(M_PI*(theta+1)/180);
       vertex_buffer_data[array_iter+7]=h/2.0;
       vertex_buffer_data[array_iter+8]=radi*sin(M_PI*(theta+1)/180);

       array_iter += 9;
       theta += 1;

    }


// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

     this->object = create3DObject(GL_TRIANGLES, 361*4*3, vertex_buffer_data, color, GL_FILL);
}

void Cylinder::draw(glm::mat4 VP) {
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

void Cylinder::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cylinder::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


