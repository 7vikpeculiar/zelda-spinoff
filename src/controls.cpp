// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::vec3 dir;
glm::mat4 getViewMatrix(){
    return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
    return ProjectionMatrix;
}
glm::vec3 getEye()
{
    return dir;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 5, 5, 5 );
glm::vec3 lookatorigin  = glm::vec3( 0, 0, 0 );
// Initial horizontal angle : toward -Z
float horizontalAngle = 0.0f;
// Initial vertical angle : none
float verticalAngle = 1.14f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
float rotSpeed = 0.05f;
float radius =  5;

void computeMatricesFromInputs(){

    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xpos, ypos;
    //glfwGetCursorPos(window, &xpos, &ypos);

    // Reset mouse position for next frame
    //glfwSetCursorPos(window, 800/2, 800/2);

    // Compute new orientation
    //Turn Left-right
    if (glfwGetKey( window, GLFW_KEY_U ) == GLFW_PRESS){
        horizontalAngle += rotSpeed;

    }
    //Turn Up down
    if (glfwGetKey( window, GLFW_KEY_O ) == GLFW_PRESS){
        if(verticalAngle > M_PI/2.0 || verticalAngle < 0)
        {
            rotSpeed*=-1;
        }
        verticalAngle   += rotSpeed;
    }

    if (glfwGetKey( window, GLFW_KEY_I ) == GLFW_PRESS){
        radius += deltaTime * speed;
    }
    // Move backward --> Zoom Backward
    if (glfwGetKey( window, GLFW_KEY_K ) == GLFW_PRESS){
        radius -= deltaTime * speed;
    }

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
        radius*cos(verticalAngle) * sin(horizontalAngle),
        radius*sin(verticalAngle),
        radius*cos(verticalAngle) * cos(horizontalAngle)
    );
    dir = direction;
    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    // Up vector
    glm::vec3 up =  glm::vec3(0,1,0);
    //glm::cross( right, direction );

    // Move forward --> Zoom Forward
    /*// Strafe right
    if (glfwGetKey( window, GLFW_KEY_L ) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey( window, GLFW_KEY_J ) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }*/

    float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    //ProjectionMatrix = glm::ortho(-4.0, 4.0, -4.0, 4.0, 0.1f, 500.0f);

    // Camera matrix
   /* ViewMatrix       = glm::lookAt(
                                position,           // Camera is here
                                position+direction, // and looks here : at the same position, plus "direction"
                                up                  // Head is up (set to 0,-1,0 to look upside-down)
                           );*/
    ViewMatrix       = glm::lookAt(
                                direction,  // Camera is here and moving
                                lookatorigin,       // and looks here : at the same position, plus "direction"
                                up                  // Head is up (set to 0,-1,0 to look upside-down)
                           );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}



