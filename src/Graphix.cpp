#include "Graphix.h"
#include<unistd.h>

using namespace std;

void Graphix::cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos){
    glfwPostEmptyEvent();
}

void Graphix::mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        // cout << "left button pressed" << endl;
        glfwPostEmptyEvent();
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        // cout << "left button released" << endl;
        glfwPostEmptyEvent();
    }
}

void Graphix::error_callback(int error, const char* description){
    fputs(description, stderr);
}

void Graphix::window_refresh_callback(GLFWwindow* window){
    glfwPostEmptyEvent();
}

void Graphix::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
        exit(0);
    }
    else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        pause_flag ^= true;
        cout << (pause_flag? "\n--------PAUSED--------\n" : "------UNPAUSED------\n") << endl;
    }
    else{
        glfwPostEmptyEvent();
    }
}

void Graphix::cursor_enter_callback(GLFWwindow* window, int entered){
    glfwPostEmptyEvent();
}

void Graphix::draw_dashed_line(LineSegment line, GLfloat red, GLfloat green, GLfloat blue){

    if(line.is_nan()) return;
    glPushAttrib(GL_ENABLE_BIT); 
    glLineStipple(1, 0x1111);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
        glColor3f(red, green, blue);
        glVertex2f(line.start_pt().x, line.start_pt().y);
        glVertex2f(line.end_pt().x, line.end_pt().y);
        glColor3f(DRAW_COLOR);
    glEnd();
    glPopAttrib();

}

void Graphix::render(){
    m_mutex.lock();
    usleep(ANIMATION_SPEED);
    while(pause_flag) glfwWaitEvents();
    glfwSwapBuffers(window);
    m_mutex.unlock();
}

void Graphix::draw_line(LineSegment line, GLfloat red, GLfloat green, GLfloat blue){
    if(line.is_nan()) return;
    glBegin(GL_LINES);
        glColor3f(red,green,blue);
        glVertex2f(line.start_pt().x, line.start_pt().y);
        glVertex2f(line.end_pt().x, line.end_pt().y);
        glColor3f(DRAW_COLOR);
    glEnd();
}

// void init(){

// }

void Graphix::loopie(){
    while( !glfwWindowShouldClose(window) ){
        glfwWaitEvents();
        // cout << "ggwp" << endl;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Graphix::pause_flag = true;

Graphix::Graphix(std::mutex& mtx):m_mutex(mtx){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    window = glfwCreateWindow(WIN_BREADTH, WIN_HEIGHT, WIN_NAME, NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Animation paused in the beginning
    pause_flag = true;

    // Set common callbacks
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;

    clear();
    // glClearColor(BG_COLOR, BG_ALPHA);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(DRAW_COLOR);
    glPointSize(POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(WIN_DIM_NEG_X, WIN_DIM_POS_X, WIN_DIM_NEG_Y, WIN_DIM_POS_Y, 1.f,-1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    render();

}

void Graphix::clear(){
    glClearColor(BG_COLOR, BG_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);
}

