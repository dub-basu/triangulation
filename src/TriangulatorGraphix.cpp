#include<algorithm>
#include "TriangulatorGraphix.h"

TriangulatorGraphix::TriangulatorGraphix(std::mutex& mtx):Graphix(mtx){
    Point start(-WIN_BREADTH / 2, WIN_HEIGHT);
    Point end(WIN_BREADTH / 2, WIN_HEIGHT);
}

void TriangulatorGraphix::update_scene(){
    clear();
    draw_edges();
}

void TriangulatorGraphix::add_edge(LineSegment ln){
    edges.push_back(ln);
    update_scene();
}

void TriangulatorGraphix::add_edge(Point pt1, Point pt2){
    LineSegment ln(pt1, pt2);
    add_edge(ln);
}

void TriangulatorGraphix::remove_edge(LineSegment& ln){
    edges.erase(std::remove(edges.begin(), edges.end(), ln), edges.end());
    update_scene();
}

void TriangulatorGraphix::remove_edge(Point pt1, Point pt2){
    LineSegment ln(pt1, pt2);
    remove_edge(ln);
}

void TriangulatorGraphix::draw_edges(){
    for(auto edge: this -> edges){
        draw_line(edge, EDGE_COLOR);
    }
}

void TriangulatorGraphix::draw_point(Point pt, GLfloat red, GLfloat green, GLfloat blue){
    glBegin(GL_POINTS);
        glColor3f(red, green, blue);  
        glVertex2f(pt.x,pt.y);
        glColor3f(DEFAULT_COLOR);
    glEnd();
}

void TriangulatorGraphix::clear_lines(){
    (this -> edges).clear();
    update_scene();
}

void TriangulatorGraphix::remove_point(Point pt){
    input_points.erase(std::remove(input_points.begin(), input_points.end(), pt), input_points.end());
    update_scene();
}

void TriangulatorGraphix::add_point(Point pt){
    input_points.push_back(pt);
    update_scene();
}