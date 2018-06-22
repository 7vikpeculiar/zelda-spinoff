#include "main.h"
#include "timer.h"
#include "ball.h"
#include "controls.h"
#include "boat.h"
#include "rock.h"
#include "pyramid.h"
#include "enemy.h"
#include "gift.h"
#include "cylinder.h"
#include "barrel.h"
#include "bomb.h"
#include "wind.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
std::vector <Rock> rock_array;
std::vector <Enemy> nemesi;
std::vector <Gift> santa;
std::vector <Barrel> tubes;
std::vector <Bomb> catridge;

Ball ball1;
Ball floor1;
Boat boat1;
Rock rock1;
Wind soar;
Enemy enema;
Bomb swat;
Gift prey;
Cylinder silo;

int bool1;

int health = 100;
int score = 0;

int choice = 0;
int choice2 = 0;
int boss = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float ground = 0.04;

Timer t60(1.0 / 60);
Timer twind(10);
Timer twind_stop(15);
double mouse_xpos, mouse_ypos;

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void print_health()
{
    cout << health << endl;
}


void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    computeMatricesFromInputs();
    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    //glm::vec3 eye (5,0,0);
    glm::vec3 eye (0,0,0);
    //glm::vec3 eye (0,0,5);

    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, boat1.position.y, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    //int choice = 0;
    if(choice == 0){
        Matrices.view = glm::lookAt(getEye(),target ,up );
    }
    if(choice == 1)
    {
        // Boat view
        float rot = boat1.rotation;
        glm::vec3 dpos (-0.3*sin(rot),0.3 ,0.3*cos(rot));
        glm::vec3 eye = boat1.position + dpos ;
        glm::vec3 lookat  = glm::vec3(1000*sin(rot),0.2,-1000*cos(rot));
        Matrices.view = glm::lookAt(eye, lookat ,up );

    }
    else if(choice == 2){

        //Follow cam
      glm::vec3 dpos(0,10,10);
      float rot = boat1.rotation;
      glm::vec3 dpos1(-5*sin(rot),5,5*cos(rot));
      glm::vec3 eye = dpos1 +  boat1.position;
      //float rot = winston.rotation;
      glm::vec3 lookat = boat1.position ; //glm::vec3(0,0,-10);
      Matrices.view = glm::lookAt(eye, lookat ,up );
    }
    else if(choice == 3)
    {
       // Tower view
       glm::vec3 dpos(0.001,5,0);
       //float rot = winston.rotation*M_PI/180.0;
       //glm::vec3 dpos1(10*sin(-rot),0,-10*cos(-rot));
        glm::vec3 eye = dpos;
        //float rot = winston.rotation;
        glm::vec3 lookat = boat1.position ; //glm::vec3(0,0,-10);
        Matrices.view = glm::lookAt(eye, lookat ,up );
    }
    else if(choice == 4)
    {
        glm::vec3 dpos(0,10,0.0001);
        glm::vec3 eye(boat1.position.x,10,boat1.position.z+ 0.0001);
        glm::vec3 lookat = boat1.position;
        Matrices.view = glm::lookAt(eye, lookat ,up );
    }
    else if(choice == 5){
        Matrices.view = glm::lookAt(getEye(), boat1.position ,up );
    }

    if(choice2 == 0)
    {Matrices.projection = getProjectionMatrix();
    }
    else if(choice2 == 1)
    {
     // Matrices.projection = getProjectionMatrix();
        reset_screen();
    }

    //Matrices.view = Views(&boat1,1);//glm::lookAt(getEye(), target ,up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    floor1.draw(VP);
    //ball1.draw(VP);
    boat1.draw(VP);
    //rock1.draw(VP);
    for(int i=0;i<rock_array.size();i++)
    {
        rock_array[i].draw(VP);
    }
    //enema.draw(VP);
    for(int i=0;i<nemesi.size();i++)
    {
        nemesi[i].draw(VP);
    }
    for(int i=0;i<catridge.size();i++)
    {
        catridge[i].draw(VP);
    }
    for(int i=0;i<santa.size();i++)
    {
        santa[i].draw(VP);
    }
    for(int i=0;i<tubes.size();i++)
    {
        tubes[i].draw(VP);
    }
    //swat.draw(VP);
    //prey.draw(VP);
    //silo.draw(VP);
}


float angle_correlate(GLFWwindow *window)
{
    glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
    float angle = -45 + 90*mouse_xpos/800.0;
    return angle;
}

void rotate_cannon(){
    float angle = angle_correlate(window);
    boat1.Cannon.rotation = -angle*M_PI/180.0;
}

void create_bombs()
{

    vector <Bomb>::iterator iterer;

    if(catridge.size()<  100)
    {

        //float x =  -5.0 + (rand()%100)*0.1;
        //float z = -5.0 +  (rand()%100)*0.1;
        iterer = catridge.begin();

        catridge.insert(iterer,Bomb(boat1.Cannon.position.x,boat1.Cannon.position.y ,boat1.Cannon.position.z));
        float a = angle_correlate(window)*M_PI/180;
        catridge[0].speed_x = 0.1*sin(a);
        catridge[0].speed_z = -0.1*cos(a);
        //boat1.Cannon.rotation = a;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int front = glfwGetKey(window, GLFW_KEY_UP);
    int back  = glfwGetKey(window, GLFW_KEY_DOWN);
    int up    = glfwGetKey(window,GLFW_KEY_SPACE);
    int mouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    mouse    = glfwGetKey(window,GLFW_KEY_F);
    int v = glfwGetKey(window,GLFW_KEY_V);
    int zero  = glfwGetKey(window, GLFW_KEY_0);
    int one  = glfwGetKey(window, GLFW_KEY_1);
    int two  = glfwGetKey(window, GLFW_KEY_2);
    int three  = glfwGetKey(window, GLFW_KEY_3);
    int four  = glfwGetKey(window, GLFW_KEY_4);
    int five  = glfwGetKey(window, GLFW_KEY_5);
    int six  = glfwGetKey(window, GLFW_KEY_6);

    float rot = boat1.rotation;
    //boat1.set_rotation(90);
    if (front) {
           // Do something
        //boat1.position[2] -= 0.1;

        boat1.set_position(boat1.speed*sin(rot),0,-boat1.speed*cos(rot));
        //cout << boat1.position.x << endl;
   }
    if(back){
           //boat1.position[2] += 0.1;
        boat1.set_position(-0.01*sin(rot),0,0.01*sin(rot));
    }
    float drot = 0.1;
    if(left)
    {
        boat1.set_rotation(-drot);
    }
    if(right)
    {
       boat1.set_rotation(drot);
    }
    if(right)
    {
        //cout << boat1.ground << endl;
        //cout << boat1.position.y << endl;
    }
    if(up && boat1.position.y == boat1.ground){

          boat1.speed_y = 0.2;
          boat1.set_position(0,0.001,0);
          //boat1.time++;
     }

   // if(mouse)
   // {
   //     create_bombs();
    //}
      // std::cout << boat1.position.z  << endl;
    boat1.set_position(soar.direction.x, 0,soar.direction.z);
    boat1.Flag.rotation = 90 -soar.theta;
    if(zero)
    {
        choice = 0;
    }
    if(one)
    {
        choice = 1;
    }
    if(two)
    {
        choice = 2;
    }
    if(three)
    {
        choice = 3;
    }
    if(four)
    {
        choice = 4;
    }
    if(five)
    {
        choice2 = 0;
    }
    if(six)
    {
        choice2 = 1;
    }

}

void tick_elements() {
    ball1.tick();
    floor1.tick();
    //camera_rotation_angle += 0;
    boat1.tick();
    for(int i = 0 ; i< catridge.size();i++)
    {
        catridge[i].tick();
    }
    //std::cout << boat1.Mast.position.z  << endl;
    prey.tick();
    for(int i = 0 ; i< santa.size();i++)
    {
        santa[i].tick();
    }
    for(int i = 0 ; i< tubes.size();i++)
    {
        tubes[i].tick();
    }
    for(int i = 0 ; i< nemesi.size();i++)
    {
        nemesi[i].tick();
    }
    for(int i = 0 ; i< rock_array.size();i++)
    {
        rock_array[i].tick();
       //rock_array[i].position.y += 1;
    }
    //cout << rock_array[0].position.y << endl;
   // boat1.ground *=  bool1 ;//0.04 + 0.02*sin(8*boat1.time*M_PI/180.0); // sinusoidal movement
    //cout  <<  ground;
    boat1.time++;
    soar.tick();
}

/*void create_rocks(vector<Rock> &looper)
{

    vector <Rock>::iterator iterer;
    for(int i=0;i<1;i++)
    {

        float x =  -5.0 + (rand()%100)*0.1;
        float z = -5.0 +  (rand()%100)*0.1;
        iterer = looper.begin();
        looper.insert(iterer,Rock(0,z,0.5,0.75));
    }
}*/

void delete_invalid_bullets(vector<Bomb>& looper)
{
    for(int i=0; i< looper.size();i++)
    {
        if((abs(looper[i].position.x - ball1.position.x) > 10) || (abs(looper[i].position.z) - ball1.position.z) > 10)
        {
            looper.erase(looper.begin() + i);
            return;

        }
    }
}

void delete_invalid_barrels(vector<Barrel>& looper)
{
    for(int i=0; i< looper.size();i++)
    {
        if((abs(looper[i].position.y - ball1.position.y) > 10))
        {
            looper.erase(looper.begin() + i);
            return;

        }
    }
}
void create_gift_barrel_pair(vector<Gift> &looper, vector<Barrel> &tube_looper)
{
    vector <Gift>::iterator iterer;
    vector <Barrel>::iterator tube_iterer;

    if(looper.size()< 4)
    {

        float x =  -20.0 + ball1.position.x + (rand()%40);
        float z = -20.0 + ball1.position.z + (rand()%40);
        //z = -2;
        iterer = looper.begin();

        tube_iterer = tube_looper.begin();
        tube_looper.insert(tube_iterer,Barrel(x,z,0.5,0.5));
        looper.insert(iterer,Gift(x,1,z,0.3,0.3,COLOR_GEM_GREEN));
      /*  float a = angle_correlate(window)*M_PI/180;
        looper[0].speed_x = 0.1*sin(a);
        looper[0].speed_z = -0.1*cos(a);*/
        //boat1.Cannon.rotation = a;
    }
}

void create_rocks(vector<Rock> &looper)
{

    vector <Rock>::iterator iterer;
    for(int i=0;i<800;i++)
    {

        float x =  -100.0 + 4*(rand()%100);
        float z = -100.0 +  4*(rand()%100);
        float h = 0.75 + (rand()%100)*0.01;
        iterer = looper.begin();
        looper.insert(iterer,Rock(x,z,0.5,h));
    }
}

void create_enemy(vector<Enemy> &looper)
{

    vector <Enemy>::iterator iterer;
    //for(int i=0;i< 5;i++)
    if(looper.size()< 2)
    {

        float x =  -7.5 +   1.2*(rand()%15);
        float z =  -7.5 +   1.2*(rand()%15);

        iterer = looper.begin();
        if(boss%4 != 3 ){

        looper.insert(iterer,Enemy(boat1.position.x + x ,0,boat1.position.z + z,0.7,0.7,0.7,COLOR_BLACK));
        looper[0].lives = 0;
        looper[0].speed = 0;
        }
        else
        {
          looper.insert(iterer,Enemy(boat1.position.x + x ,0,boat1.position.z + z,3,3,3,COLOR_RED));
           looper[0].lives = 5;
           looper[0].speed = 1;
        }
        boss++;
        //looper[0].lives = 5;
    }
}

void move_enemy(vector<Enemy>& looper)
{
    for(int i=0; i< looper.size();i++)
    {
        if(looper[i].speed!= 0)
        {
            glm::vec3 delta = boat1.position - looper[i].position ;
            looper[i].set_position(delta.x/100.0, delta.y/100.0, delta.z/100.0);
            return;

        }
    }
}

void rock_collision_movement(vector<Rock>& looper , Boat* boat_pointer)
{
    Boat winston = *boat_pointer ;
    //int end = looper.size();
    for(int i=0;i< looper.size();i++)
    {
        if(detect_rock_collision(looper[i].bounding_sphere(),winston.bounding_sphere()))
        {
            looper.erase(looper.begin() + i);
            health -= 3;
 //           cout << score;
        }
            //score.draw(VP);

            }

    *boat_pointer = winston;

    return;
}

void barrel_collision_movement(vector<Barrel>& looper , Boat* boat_pointer)
{
    Boat winston = *boat_pointer ;
    //int end = looper.size();
    for(int i=0;i< looper.size();i++)
    {
        //cout << 1;
       // bounding_box_t a = looper[0].bounding_box();
       // bounding_box_t b =  winston.bounding_box();
       if(detect_barrel_collision(looper[i].bounding_box(),winston.bounding_box()) && looper[i].speed_y >= 0)
        {
            if(looper[i].position.y < winston.position.y && winston.speed_y < 0)
            {

                looper[i].speed_y = -0.04;
                winston.speed_y = 0;
                float rot = winston.rotation;
                looper[i].speed_x = 0.02*sin(rot*M_PI/180.0);
                looper[i].speed_z = -0.02*cos(rot*M_PI/180.0);
            }
            else
            {
                float rot = winston.rotation;
                looper[i].speed_x = 0.02*sin(rot*M_PI/180.0);
                looper[i].speed_z = -0.02*cos(rot*M_PI/180.0);
                looper[i].speed_y = -0.02;
                //winston.set_position();
            }
            //looper.erase(looper.begin() + i);
            // score += 1;
            //  cout << score;
        }
            //score.draw(VP);

            }

    *boat_pointer = winston;

    return;
}

void gift_collision_movement(vector<Gift>& looper , Boat* boat_pointer,  vector<Barrel>& barrel_looper)
{
    Boat winston = *boat_pointer ;
    for(int i=0;i< looper.size();i++)
    {
        if(detect_gift_collision(looper[i].bounding_box(),winston.bounding_box()))
        {
            for(int j=0;j< barrel_looper.size();j++)
            {
                if(looper[i].position.z == barrel_looper[j].initial_position.z && (looper[i].position.z == barrel_looper[j].initial_position.z))
                {
                    barrel_looper[j].speed_y = -0.02;
                }
            }
            looper.erase(looper.begin() + i);
            health+=10;
            // cout <<1;
            //score += 1;
 //           cout << score;
        }
            //score.draw(VP);

     }

    *boat_pointer = winston;

    return;
}
//void barrel_collision_movement(vector<Enemy>& looper, Boat)

void enemy_collision_movement(vector<Enemy>& looper , Boat* boat_pointer)
{
    Boat winston = *boat_pointer ;
    //int end = looper.size();
    for(int i=0;i< looper.size();i++)
    {
        //bounding_box_t a = winston.bounding_box();
        //cout << a.x;
        if(detect_enemy_collision(looper[i].bounding_box(),winston.bounding_box()))
        {
            glm::vec3 diff =  - looper[i].position + winston.position;
            //float rot = winston.rotation;
            winston.set_position(diff.x/100.0,diff.y/100.0,diff.z/100.0);
            if(looper[i].time == 0)
            {
                health -= 10;
                looper[i].time = 1000;
            }
            //looper.erase(looper.begin() + i);
//            score += 1;
 //           cout << score;
        }
            //score.draw(VP);

            }

    *boat_pointer = winston;

    return;
}

void bomb_enemy_collision_movement(vector<Enemy>& looper , vector<Bomb>& bomb_looper)
{
    //Boat winston = *boat_pointer ;
    //int end = looper.size();

    for(int i=0;i < looper.size();i++)
    {

        for(int j= 0;j < bomb_looper.size();j++)
        {
            if(detect_bomb_enemy_collision(looper[i].bounding_box(),bomb_looper[j].bounding_box()))
            {
                //cout << looper[i].lives << endl;
                if(looper[i].lives == 0)
                {
                    looper.erase(looper.begin() + i);
                    bomb_looper.erase(bomb_looper.begin()+j);      
                    boat1.speed = 1;
                }
                else
                {
                    looper[i].setLife();
                    bomb_looper.erase(bomb_looper.begin()+j);
                }

            }

        }
    }


    return;
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ground = 0;
    ball1       = Ball(0, 0, 0, 0.3, 0.3, 0.3, COLOR_RED);
    floor1      = Ball(0,-0.45, 0, 1000, 1 ,1000, COLOR_SEABLUE);
    boat1  =     Boat(0, 0.04, 0);
    rock1 = Rock(0,0,0.7,1.2);
    soar = Wind(0,0.01);
    enema = Enemy(2,2,2,1,1,1,COLOR_BLACK);
    swat  = Bomb(2,2,2);
    prey = Gift(-1,1,-1,0.2,0.2,COLOR_GEM_GREEN);
    silo = Cylinder(2,2,2,1,0.5,COLOR_BLACK);
    create_rocks(rock_array);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            //glfwSetCursorPos(window, 800, 0);c->

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            angle_correlate(window);

            if(twind.processTick())
            {
                soar.speed = 0.02;
                soar.theta = rand()/360.0;
                soar.set_dir();
                soar.time = 100;
            }
            tick_elements();
            tick_input(window);
            draw();

    //cout << boat1.Cannon.position.z << endl;
    //cout << boat1.position.z << endl;
            create_gift_barrel_pair(santa,tubes);
            create_enemy(nemesi);
            move_enemy(nemesi);
            rock_collision_movement(rock_array,&boat1);
            enemy_collision_movement(nemesi,&boat1);
            bomb_enemy_collision_movement(nemesi,catridge);
            gift_collision_movement(santa,&boat1,tubes);
            barrel_collision_movement(tubes,&boat1);
            delete_invalid_bullets(catridge);
            delete_invalid_barrels(tubes);


        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

/*bool detect_collision(bounding_sphere_t a, bounding_sphere_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}*/

int detect_rock_collision(bounding_sphere_t a, bounding_sphere_t b)
{
    return (abs(a.x - b.x)  < (a.r + b.r)) &&
               (abs(a.y - b.y)  < (a.r + b.r)) && (abs(a.z - b.z) < (a.r + b.r));
}

int detect_enemy_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) < (a.l + b.l)/2.0) &&
           (abs(a.y - b.y)  < (a.b + b.b)/2.0) &&
           (abs(a.z - b.z) < (a.h + b.h)/2.0);
}

int detect_bomb_enemy_collision(bounding_box_t a,bounding_box_t b)
{
    return (abs(a.x - b.x) < (a.l + b.l)/2.0) &&
           (abs(a.y - b.y)  < (a.b + b.b)/2.0) &&
           (abs(a.z - b.z) < (a.h + b.h)/2.0);
}

int detect_gift_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) < (a.l + b.l)/2.0) &&
           (abs(a.y - b.y)  < (a.b + b.b)/2.0) &&
           (abs(a.z - b.z) < (a.h + b.h)/2.0);
}
int detect_barrel_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) < (a.l + b.l)/2.0) &&
           (abs(a.y - b.y)  < (a.b + b.b)/2.0) &&
           (abs(a.z - b.z) < (a.h + b.h)/2.0);
}



void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
