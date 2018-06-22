#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_sphere_t {
    float x;
    float y;
    float z;
    float r;
};

struct bounding_box_t {
    float x;
    float y;
    float z;
    float l;
    float b;
    float h;
};


bool detect_collision(bounding_sphere_t a, bounding_sphere_t b);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
int detect_rock_collision(bounding_sphere_t a, bounding_sphere_t b);
int detect_enemy_collision(bounding_box_t a, bounding_box_t b);
int detect_bomb_enemy_collision(bounding_box_t a,bounding_box_t b);
int detect_gift_collision(bounding_box_t a, bounding_box_t b);
int detect_barrel_collision(bounding_box_t a, bounding_box_t b);
void create_bombs();
void print_health();
//void set_catridge_rotation();
void rotate_cannon();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_SEABLUE;

extern const color_t COLOR_BOAT_MAST;
extern const color_t COLOR_BOAT_FLAG;
extern const color_t COLOR_BOAT_RUDDER;
extern const color_t COLOR_BOAT_FLOOR;

extern const color_t COLOR_STONE_GREY;

extern const color_t COLOR_BOMB_PINK;
extern const color_t COLOR_GEM_GREEN;

//extern bool noob;
#endif
