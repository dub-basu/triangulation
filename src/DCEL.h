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

    static Vertex lastReference;//!< Last reference variable used for comparisons

    Vertex* origin; //!< The incident vertex for this HalfEdge
    //Vertex* end;
    HalfEdge* twin; //!< The twin of the Half Edge
    Face* incidentFace;//!< The incident face of this HalfEdge
    HalfEdge* next;//!< Pointer to next edge
    HalfEdge* previous;//!< Pointer to previous edge

    Vertex* helper; //!< Helper vertex of the edge

    /**
     * Parameterised Cosntructor of the class
     */
    HalfEdge(Vertex*);
    /**
     * Default constructor of the class
     */
    HalfEdge();
    /**
     * Standard operator < for the class
     * @return
     */
    bool operator< (const HalfEdge& );
    /**
     * Standard operator < =for the class
     * @return
     */
    bool operator<= (const HalfEdge& );
    /**
     * Standard operator == for the class
     * @return
     */
    bool operator== (const HalfEdge& );
    /**
     * Standard operator > for the class
     * @return
     */
    bool operator> (const HalfEdge& );
    /**
     * Standard operator >= for the class
     * @return
     */
    bool operator>= (const HalfEdge& );
    /**
     * Standard operator != for the class
     * @return
     */
    bool operator!=(const HalfEdge &rt);



    // HalfEdge& operator= (const HalfEdge& );

    /**
     * Standard operator << for the class
     * @return
     */

    friend std::ostream& operator<<(std::ostream& os, const HalfEdge& halfEdge);

};
// Vertex HalfEdge::lastReference = Vertex(NAN_POINT);

enum class vertexType { REGULAR, SPLIT, MERGE, START, END };//!< Type of vertices as specified in Y-Monotone-Decomposition Algorithm
class Vertex : public Point {
    // x & y coordinate
public:
    HalfEdge* incidentEdge;//!< Incident edge for the Vertex
    /**
     * Parameterised constructor for the class.
     */
    Vertex(Point);
    /**
     * Standard operator < for the class
     * @return
     */
    bool operator< (const Vertex&);
    //bool operator<(const Vertex * rt);
    vertexType type;//!< Type of the vertex, i.e. Regular, Start, End, Split or Merge.
};

class Face {
public:
    HalfEdge* startEdge;//!< Starting edge of the face.

};

class DCEL {



public:
    //map<Point, Vertex> pointsInDCEL ;
    vector <Face*> faces;//!< List of Faces in the DCEL
    vector<Vertex*> points; //!< List of Vertices in DCEL
    /**
     * Default Constructor of DCEL class
     */
    DCEL();
    /**
     * Parameterised Constructor of the DCEL class
     */
    DCEL(Polygon);

    /**
     * Adds an edge between two points in DCEL
     */

    void addEdge(Point, Point);

    /**
     * Adds an edge between 2 vertices of DCEL
     */

    void addEdge(Vertex*, Vertex*);

    /**
     * Prints the given DCEL
     */

    void printDCEL();
};

#endif //TRIANGULATION_DCEL_H
