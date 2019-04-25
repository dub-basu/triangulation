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

    static Vertex lastReference;

    Vertex* origin;
    //Vertex* end;
    HalfEdge* twin;
    Face* incidentFace;
    HalfEdge* next;
    HalfEdge* previous;

    Vertex* helper;

    HalfEdge(Vertex*);
    HalfEdge();

    bool operator< (const HalfEdge& );
    bool operator<= (const HalfEdge& );
    bool operator== (const HalfEdge& );
    bool operator> (const HalfEdge& );
    bool operator>= (const HalfEdge& );
    bool operator!=(const HalfEdge &rt);



    // HalfEdge& operator= (const HalfEdge& );

    friend std::ostream& operator<<(std::ostream& os, const HalfEdge& halfEdge);

};
// Vertex HalfEdge::lastReference = Vertex(NAN_POINT);

enum class vertexType { REGULAR, SPLIT, MERGE, START, END };
class Vertex : public Point {
    // x & y coordinate
public:
    HalfEdge* incidentEdge;
    Vertex(Point);
    bool operator< (const Vertex&);
    //bool operator<(const Vertex * rt);
    vertexType type;
};

class Face {
public:
    HalfEdge* startEdge;

};

class DCEL {



public:
    //map<Point, Vertex> pointsInDCEL ;
    vector <Face*> faces;
    vector<Vertex*> points;

    DCEL();
    DCEL(Polygon);

    void addEdge(Point, Point);

    void addEdge(Vertex*, Vertex*);

    void printDCEL();
};

#endif //TRIANGULATION_DCEL_H
