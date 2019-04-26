#ifndef CONVEX_HULL_GRAPHIX
#define CONVEX_HULL_GRAPHIX

#define DEFAULT_COLOR 0,0,0
#define POINT_COLOR 0,0,0
#define PIVOT_COLOR 0,1,0
#define SPOKE_COLOR 0,0,0
#define EDGE_COLOR 0.9,0,0.6

#include<vector>
#include "Graphix.h"
#include "primitives.h"

/**
 * \class ConvexHullGraphix
 * \brief Class for Visualization
 */
class TriangulatorGraphix: public Graphix {
    private:
        
        std::vector<Point> input_points;
        std::vector<LineSegment> edges;

        void draw_point(Point, GLfloat red=0, GLfloat green=0, GLfloat blue=0);
        void update_scene();
        void draw_edges();
    public:
        TriangulatorGraphix(std::mutex& mtx);
        void add_edge(LineSegment);
        void add_edge(Point, Point);
        void remove_edge(LineSegment&);
        void remove_edge(Point, Point);
        void update_event(Point);
        void clear_lines();
        void remove_point(Point);
        void add_point(Point);
};

#endif