#ifndef WINDOWCONSTANTS
#define WINDOWCONSTANTS

#define BG_COLOR 1.0, 1.0, 1.0
#define BG_ALPHA 1.0
#define DRAW_COLOR 1.0, 0.0, 0.0
#define DRAW_COLOR2 0.0, 0.0, 0.0

#define WIN_BREADTH 1000
#define WIN_HEIGHT 1000
#define WIN_POSITION_X 100
#define WIN_POSITION_Y  100
#define WIN_DIM_NEG_X -10
#define WIN_DIM_POS_X 10
#define WIN_DIM_NEG_Y -10
#define WIN_DIM_POS_Y 10

#define WIN_NAME "Graphix"
#define POINT_SIZE 8.0
#define ANIMATION_SPEED 600000

#endif

#ifndef GRAPHIX
#define GRAPHIX

#include<GLFW/glfw3.h> 
#include<mutex>
#include "primitives.h"

/**
 * \class Graphix
 * \brief Class for handling graphics using OpenGL.
 */
class Graphix{
    public:
        std::mutex& m_mutex; 
        static bool pause_flag;
        GLFWwindow* window;

        /**
         * Constructor. Creates a window instance with default parameters.
         * Ideally runs on a separate thread from the thread executing the 
         * core algorithm. 
         * Accept a reference to a mutex. Mutex is used to maintain 
         * synchronization between core algorithm execution and graphics 
         * handling functions. 
         * @param m_mutex Reference to a mutex object.
         */
        Graphix(std::mutex& mtx);

        /**
         * Utility function to draw a line segment on the window. 
         * @param line Object of LineSegment class. Holds description of 
         * line segment to be drawn.
         */        
        void draw_line(LineSegment line, GLfloat red=1, GLfloat green=0, GLfloat blue=0);

        /**
         *  Utility function to draw a dashed/stippled line segment on the window. 
         * @param line Object of LineSegment class. Holds description of 
         * line segment to be drawn.
         */        
        void draw_dashed_line(LineSegment line, GLfloat red=0, GLfloat green=0, GLfloat blue=0);

        /**
         * Runs an infinite loop that listens to various events.  
         */        
        void loopie();

        /**
         * Renders whatever is on the buffer to the window.
         */        
        void render();

        /**
         * Utility function to clear the window. 
         * @param line Object of LineSegment class. Holds description of 
         * line segment to be drawn.
         */
        void clear();
    private:
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
        static void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos);
        static void error_callback(int error, const char* description);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void window_refresh_callback(GLFWwindow* window);
        static void cursor_enter_callback(GLFWwindow* window, int entered);
};

#endif