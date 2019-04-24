#ifndef TRIANGULATION_DCEL_H
#define TRIANGULATION_DCEL_H

#include <vector>
#include <map>
#include "primitives.h"
#include "Polygon.h"

class HalfEdge;
class Vertex;
class Face;

using namespace std;

class HalfEdge{
public:
    Vertex* origin;
    HalfEdge* twin;
    Face* incidentFace;
    HalfEdge* next;
    HalfEdge* previous;

    HalfEdge(Vertex*);


};

class Vertex : public Point {
    // x & y coordinate
public:
    HalfEdge* incidentEdge;
    Vertex(Point);
};

class Face {
public:
    HalfEdge* startEdge;

};

class DCEL {
    vector <Face*> faces;


public:
    //map<Point, Vertex> pointsInDCEL ;

    vector<Vertex*> points;

    DCEL(Polygon);

    void addEdge(Point, Point);

    void addEdge(Vertex*, Vertex*);

    void printDCEL();
};

#endif //TRIANGULATION_DCEL_H
